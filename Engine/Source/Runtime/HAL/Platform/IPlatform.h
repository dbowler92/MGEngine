//IPlatform.h
//Created 12/01/18
//Created By Daniel Bowler
//
//Interface class for each platform specific Application class
//to inherit from. In turn, a game specific Application class
//will inherit from the platform agnostic Application (See: Application.h)

#pragma once

#include <Core/CoreInclude.h>

class IPlatform
{
public:
	/*
	 * Virtual Destructor
	 */
	virtual ~IPlatform() = 0 {};

	/*
	* Inits the OS related stuff - eg: Creates the window, message pump, etc
	*/
	virtual bool InitPlatform(void* AppHandle, void* CmdLine,
		const char* AppTitle, uint32_t InitialWindowWidth, uint32_t InitialWindowHeight) = 0;

	/*
	* Called after the engine has been inited - We do platform specific
	* engine init here
	*/
	virtual bool OnPostEngineInit() = 0;

	/*
	* Called each frame before the main game loop is executed - Do
	* platform specific work
	*/
	virtual void OnPlatformTick() = 0;

	/*
	* Called during engine shutdown
	*/
	virtual bool OnShutdown() = 0;

	/*
	* Gets the OS window that the platform specific implementation will create and manage.
	*/
	virtual class IPlatformWindow* GetWindow() = 0;
};