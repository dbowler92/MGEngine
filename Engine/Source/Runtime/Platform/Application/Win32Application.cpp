#include "Win32Application.h"

const LPCWSTR WndClassName = L"DX12Demo";

FWin32Application::FWin32Application()
	: CachedAppHandle(0)
{}

FWin32Application::~FWin32Application()
{}

FWin32Application* FWin32Application::GetInstance()
{
	static FWin32Application Instance;
	return &Instance;
}

LRESULT FWin32Application::WndProc(HWND Hwnd, UINT Msg, WPARAM WParam, LPARAM LParam)
{
	switch (Msg)
	{
		case WM_CHAR:
		{
			if (WParam == VK_ESCAPE)
			{
				//Post the quit message. 
				PostQuitMessage(0);
				return 0;
			}
		}
	}
	return DefWindowProc(Hwnd, Msg, WParam, LParam);
}

void FWin32Application::InitApplication(HINSTANCE HInstance, const uint32 WindowWidth, const uint32 WindowHeight, LPCWSTR MainWindowTitle)
{
	CachedAppHandle = HInstance;
	
	assert(InitWin32());
	assert(CreateWin32Window(WindowWidth, WindowHeight, MainWindowTitle));

	//Show main window
	MainAppWindow.Show();
}

bool FWin32Application::InitWin32()
{
	WNDCLASS WC;
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc = FWin32Application::WndProc;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.hInstance = CachedAppHandle;
	WC.hIcon = LoadIcon(0, IDI_APPLICATION);
	WC.hCursor = LoadCursor(0, IDC_ARROW);
	WC.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	WC.lpszMenuName = 0;
	WC.lpszClassName = WndClassName;

	if (!RegisterClass(&WC))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	return true;
}

bool FWin32Application::CreateWin32Window(uint32 Width, uint32 Height, LPCWSTR WindowTitle)
{
	assert(Width != 0 && Height != 0 && WindowTitle != nullptr);
	assert(MainAppWindow.IsCreated() == false);

	//TODO: Multiple unique windows. 
	assert(MainAppWindow.Create(CachedAppHandle, WndClassName, Width, Height, WindowTitle));

	return true;
}

void FWin32Application::ShutdownApplication()
{
	//Destroy window(s)
	MainAppWindow.Destroy();
}

void FWin32Application::TickApplication(float Delta)
{
	MSG Msg = { 0 };

	//OutputDebugString(std::to_wstring(Delta).c_str());
	//OutputDebugString(L"\n");

	//If there windows messages, then process them
	while (PeekMessage(&Msg, NULL, NULL, NULL, PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}
