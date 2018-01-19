#include "Win32Application.h"

#include <sstream>

#include <Core/Engine/Engine.h>

LRESULT CALLBACK GlobalWndProc(HWND Hwnd, UINT Msg, WPARAM WParam, LPARAM LParam)
{
	//Call Win32Application::WndProc
	FApplication* Win32App = FEngine::GetPlatformApplication();
	if (Win32App)
	{
		return Win32App->WndProc(Hwnd, Msg, WParam, LParam);
	}
	else
	{
		return DefWindowProc(Hwnd, Msg, WParam, LParam);
	}
}

LRESULT FWin32Application::WndProc(HWND Hwnd, UINT Msg, WPARAM WParam, LPARAM LParam)
{
	//Send message to ATB. if ATB doesn't handle it, we will do so
	switch (Msg)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		if (LOWORD(WParam) == WA_INACTIVE)
		{
			AppPaused = true;
			MainGameLoopTimer.Stop();
		}
		else
		{
			AppPaused = false;
			MainGameLoopTimer.Start();
		}
		return 0;

		// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
	{
		//Update size of window
		WindowWidth = LOWORD(LParam);
		WindowHeight = HIWORD(LParam);

		if (WParam == SIZE_MINIMIZED)
		{
			AppPaused = true;
			Minimized = true;
			Maximized = false;
		}
		else if (WParam == SIZE_MAXIMIZED)
		{
			AppPaused = false;
			Minimized = false;
			Maximized = true;
			assert(OnResize() == true);
		}
		else if (WParam == SIZE_RESTORED)
		{
			// Restoring from minimized state?
			if (Minimized)
			{
				AppPaused = false;
				Minimized = false;
				assert(OnResize() == true);
			}
			// Restoring from maximized state?
			else if (Maximized)
			{
				AppPaused = false;
				Maximized = false;
				assert(OnResize() == true);
			}
			else if (Resizing)
			{
				// If user is dragging the resize bars, we do not resize 
				// the buffers here because as the user continuously 
				// drags the resize bars, a stream of WM_SIZE messages are
				// sent to the window, and it would be pointless (and slow)
				// to resize for each WM_SIZE message received from dragging
				// the resize bars.  So instead, we reset after the user is 
				// done resizing the window and releases the resize bars, which 
				// sends a WM_EXITSIZEMOVE message.
			}
			else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
			{
				assert(OnResize() == true);
			}
		}
		return 0;
	}
	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		AppPaused = true;
		Resizing = true;
		MainGameLoopTimer.Stop();
		return 0;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
		// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		AppPaused = false;
		Resizing = false;
		MainGameLoopTimer.Start();
		assert(OnResize() == true);
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)LParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)LParam)->ptMinTrackSize.y = 200;
		return 0;

	case WM_CHAR:
		//Quit the application using the Escape Key - Will be taken
		//out in release build. 
		if (WParam == VK_ESCAPE)
		{
			//Post the quit message. 
			PostQuitMessage(0);
			return 0;
		}
	}//End switch(msg) {...}

	return DefWindowProc(Hwnd, Msg, WParam, LParam);
}

bool FWin32Application::InitPlatform(void* AppHandle, void* CmdLine,
	const char* AppTitle, uint32_t InitialWindowWidth, uint32_t InitialWindowHeight)
{
	//Window
	OSWindow.SetWin32AppInstance((HINSTANCE)AppHandle);
	OSWindow.UpdateWindowWidth((unsigned)InitialWindowWidth);
	OSWindow.UpdateWindowHeight((unsigned)InitialWindowHeight);

	//Init Win32
	assert(InitWin32App(AppTitle));

	return true;
}

bool FWin32Application::OnPostEngineInit()
{
	return true;
}

bool FWin32Application::OnShutdown()
{
	return true;
}

bool FWin32Application::InitWin32App(const char* AppTitle)
{
	WNDCLASS WC;
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc = GlobalWndProc;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.hInstance = OSWindow.GetAppInstanceHandle();
	WC.hIcon = LoadIcon(0, IDI_APPLICATION);
	WC.hCursor = LoadCursor(0, IDC_ARROW);
	WC.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	WC.lpszMenuName = 0;
	WC.lpszClassName = L"WndClassName";

	if (!RegisterClass(&WC))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	// Will be the same values as the initial values specified in the two int consts
	// in the header file. 
	RECT R = { 0, 0, (LONG)OSWindow.GetWindowWidth(), (LONG)OSWindow.GetWindowHeight()};
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int Width = R.right - R.left;
	int Height = R.bottom - R.top;

	//Windows app name from char to TCHAR
	std::string Str(AppTitle);
	TCHAR *WindowsAppTitle = MGE_NEW TCHAR[Str.size() + 1];
	WindowsAppTitle[Str.size()] = 0;
	for (int i = 0; i < (int)Str.size(); ++i)
	{
		WindowsAppTitle[i] = Str[i];
	}
	//Create the window.
	HWND mainWnd = CreateWindow(L"WndClassName", WindowsAppTitle,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		Width, Height, 0, 0, OSWindow.GetAppInstanceHandle(), 0);

	if (!mainWnd)
	{
		delete[] WindowsAppTitle;
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	//Update with new handle. 
	OSWindow.SetWin32AppMainWindowHandle(mainWnd);

	//Display window.
	ShowWindow(mainWnd, SW_SHOW);
	UpdateWindow(mainWnd);

	//Cleanup
	delete[] WindowsAppTitle;

	//Done
	return true;
}

bool FWin32Application::OnResize()
{
	//Is the current window size the same as the new one? If so, skip resizing 
	//since its not needed (this occurs if the user drags the screen around, for example)
	if (OSWindow.GetWindowWidth() == WindowWidth && OSWindow.GetWindowHeight() == WindowHeight)
	{
		return true; //Didn't need to resize anything. However, this isnt an error. 
	}

	//Update OS window size with new info
	OSWindow.UpdateWindowWidth((unsigned)WindowWidth);
	OSWindow.UpdateWindowHeight((unsigned)WindowHeight);

	//Done
	return true;
}

void FWin32Application::OnPreMainGameLoopTick()
{
	MSG Msg = { 0 };
	MainGameLoopTimer.Reset();

	//If there windows messages, then process them
	while(PeekMessage(&Msg, NULL, NULL, NULL, PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void FWin32Application::CalculateFrameRateStats()
{
	/*
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((MainGameLoopTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		//API + Platform
		std::string platformString = OS_PLATFORM_API_STRING;
		std::string graphicsAPIString = RENDERING_PLATFORM_API_STRING;

		//Current scene title
		std::string currentSceneTitle = "Scene Title TODO";

		//Window size?
		std::string windowSizeStr = "Window Size: <";
		windowSizeStr += std::to_string(OSWindow.GetWindowWidth());
		windowSizeStr += ", ";
		windowSizeStr += std::to_string(OSWindow.GetWindowHeight());
		windowSizeStr += ">";

		std::wostringstream outs;
		outs.precision(8);
		outs << L"<" << platformString.c_str() << L", " << graphicsAPIString.c_str() << L"> "
			<< windowSizeStr.c_str() << L" "
			<< (GetGameTitle()) << L"    "
			<< (currentSceneTitle.c_str()) << L"    "
			<< L"Frame Time (ms): " << mspf << L" "
			<< L"(FPS: " << fps << L")";
		SetWindowText(OSWindow.GetAppMainWindowHandle(), outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
	*/
}