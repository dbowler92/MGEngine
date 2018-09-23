/** 
 * Win32 application inc message loop. Creates and manages the 
 * OS window(s)
 */

#pragma once

#include "Core/CoreInclude.h"
#include "Platform/Window/Win32Window.h"

class FWin32Application
{
public:
	static FWin32Application* GetInstance();

	void InitApplication(HINSTANCE HInstance, const uint32 WindowWidth, const uint32 WindowHeight, LPCWSTR MainWindowTitle);
	void ShutdownApplication();
	void TickApplication(float Delta);

public:
	FWin32Window& GetMainWindow() { return MainAppWindow; };

private:
	HINSTANCE CachedAppHandle;

	FWin32Window MainAppWindow;

private:
	FWin32Application();
	~FWin32Application();
	FWin32Application(FWin32Application& Other) {};
	FWin32Application& operator=(FWin32Application& Other) {};

	static LRESULT WndProc(HWND Hwnd, UINT Msg, WPARAM WParam, LPARAM LParam);

	bool InitWin32();
	bool CreateWin32Window(uint32 Width, uint32 Height, LPCWSTR WindowTitle); //TODO: Multiple unique windows. 
};