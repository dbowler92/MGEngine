//Win32Platform.h
//Created 15/14/17
//Created By Daniel Bowler
//
//Win32 implementation of the base application class

#pragma once

#include <Windows.h>

#include <HAL/Platform/IPlatform.h>
#include <HAL/PlatformWindow/PlatformWindow.h>
#include <HAL/PlatformTimer/PlatformTimer.h>
#include <Debugging/Log/DebugLog.h>

class FWin32Platform : public IPlatform
{
	HIDE_COPY_ASSIGNMENT(FWin32Platform)
public:
	/*
	 * Constructor and destructor
	 */
	FWin32Platform() {};
	virtual ~FWin32Platform() = 0 {};

	/*
	* Win32 message pump - this is public as we need a global function
	* to call in to this applications specific version - TODO: Look in to
	* making this static instead (and private) since the engine + games
	* will only have one application class created during the entire life
	* of the application.
	*/
	LRESULT WndProc(HWND Hwnd, UINT Msg, WPARAM WParam, LPARAM LParam);

	/*
	 * IApplication interface
   *
	 * Inits Win32 - Creates the window, setup the message pump etc.
	 */
	bool InitPlatform(void* AppHandle, void* CmdLine,
		const char* AppTitle, uint32_t InitialWindowWidth, uint32_t InitialWindowHeight) override;

	/*
	* Called after the engine is inited - we will do platform specific
	* engine init here.
	*/
	bool OnPostEngineInit() override;

	/*
	* Platform Tick - called at top of the game loop
	*/
	void OnPlatformTick() override;

	/*
	* Called once the engine is shutting down.
	*/
	bool OnShutdown() override;

	/*
	* Gets the Win32 os window that we create in InitPlatform().
	*/
	IPlatformWindow* GetWindow() override { return &OSWindow; };

private:
	/*
	 * Inits the Win32 window, message pump etc
	 */
	bool InitWin32App(const char* AppTitle);

	/*
	 *  Resize event - eg: when the user drags the window to resize it. Called from
	 *  within the Win32 message pump
	 */
	bool OnResize();

	/*
	 * TODO: Output Frame times and the like to the win32 window
	 */ 
	void CalculateFrameRateStats();

private:
	FPlatformWindow OSWindow;

	bool AppPaused = false;
	bool Minimized = false;
	bool Maximized = false;
	bool Resizing = false;

	FPlatformTimer MainGameLoopTimer; //TODO: Move to FEngine

	uint32_t WindowWidth;  //Window width && height -> Updated during WM_SIZE event
	uint32_t WindowHeight; //When user stops dragging, we can then resize the render targets
};