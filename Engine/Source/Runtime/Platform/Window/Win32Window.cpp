#include "Win32Window.h"

FWin32Window::FWin32Window()
	: WindowHandle(0)
	, WindowWidth(0)
	, WindowHeight(0)
	, bCreated(false)
{}

FWin32Window::~FWin32Window()
{}

bool FWin32Window::Create(HINSTANCE HInstance, LPCWSTR ClassName, const uint32 Width, const uint32 Height, LPCWSTR WindowTitle)
{
	assert(bCreated == false);

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, (LONG)Width, (LONG)Height };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int32 ClientWidth = R.right - R.left;
	int32 ClientHeight = R.bottom - R.top;

	WindowHandle = CreateWindow(ClassName, WindowTitle,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		ClientWidth, ClientHeight, 0, 0, HInstance, 0);

	assert(WindowHandle);

	bCreated = true;
	WindowWidth = ClientWidth;
	WindowHeight = ClientHeight;

	return true;
}

void FWin32Window::Destroy()
{
	assert(bCreated == true);

	DestroyWindow(WindowHandle);

	WindowHandle = 0;
	bCreated = false;
}

void FWin32Window::Show()
{
	assert(bCreated == true);
	
	ShowWindow(WindowHandle, SW_SHOW);
	UpdateWindow(WindowHandle);
}
