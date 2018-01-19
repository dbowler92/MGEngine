//Win32Window.h
//Created 19/04/17
//Created By Daniel Bowler
//
//Represents an Win32 OS window
//
//TODO: Move some of the code from Win32App over to here (Eg: The window creation & 
//registration code). 

#pragma once

#include <HAL/Window/IWindow.h>

//Windows
#include <Windows.h>

class FWin32Window : public IWindow
{
public:
	FWin32Window() {};
	virtual ~FWin32Window() {};

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