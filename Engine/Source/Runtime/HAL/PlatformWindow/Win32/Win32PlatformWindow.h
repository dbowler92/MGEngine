//Win32PlatformWindow.h
//Created 19/04/17
//Created By Daniel Bowler
//
//Represents an Win32 OS window

#pragma once

#include <HAL/PlatformWindow/IPlatformWindow.h>

//Windows
#include <Windows.h>

class FWin32PlatformWindow : public IPlatformWindow
{
public:
	FWin32PlatformWindow() {};
	virtual ~FWin32PlatformWindow() = 0 {};

	/*
	* IWindow interface
	*/
	void UpdateWindowWidth(unsigned W) override { WindowWidth = W; };
	void UpdateWindowHeight(unsigned H) override { WindowHeight = H; };

	unsigned GetWindowWidth() override { return WindowWidth; };
	unsigned GetWindowHeight() override { return WindowHeight; };

	/*
	* Win32
	*/
	void SetWin32AppInstance(HINSTANCE Handle) { AppInstanceHandle = Handle; };
	void SetWin32AppMainWindowHandle(HWND Handle) { AppMainWindowHandle = Handle; };

	HINSTANCE GetAppInstanceHandle() { return AppInstanceHandle; };
	HWND      GetAppMainWindowHandle() { return AppMainWindowHandle; };

private:
	//Win32 assigned handles
	HINSTANCE AppInstanceHandle;							  //App instance handle
	HWND AppMainWindowHandle;								    //Window handle	

protected:
	//Window size
	unsigned WindowWidth;
	unsigned WindowHeight;
};