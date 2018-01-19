//Engine.h
//Created 13/01/18
//Created By Daniel Bowler
//
//Called within the application main function, this setsup and runs
//the engine / game - This defines a platform and API agnostic
//engine startup order.

#pragma once

#include <Core/CoreInclude.h>
#include <HAL/Application/Application.h>

class FEngine
{
	MAKE_STATICS_CLASS_ONLY(FEngine);

public:
	/*
	* Begins the engine, enters the main game loop and then handles shutdown
	* once we break from the main game loop - TODO: Remove void* here
	*/
	static int Start(void* AppInstance, void* CmdLine,
		const char* AppTitle, class IApplicationDelegate* AppDelegate);

	/*
	* Gets the cached application specific app delegate
	*/
	static IApplicationDelegate* GetAppDelegate() { return CachedAppDelegate; };

	/*
	 * Gets the platform application class - Win32, IOS, etc
	 */
	static FApplication* GetPlatformApplication() { return &PlatformApplication; };


private:
	/*
	* Internally, inits the engine - platform agnostic ordering.
	*/
	static bool InitEngine(void* AppInstance, void* CmdLine,
		const char* AppTitle, class IApplicationDelegate* AppDelegate);

	/*
	* Main game loop
	*/
	static bool EnterMainGameLoop();

	/*
	* Shutdown engine
	*/
	static bool ShutdownEngine();

private:
	/*
	* Cache a reference to the game/app delegate
	*/
	static class IApplicationDelegate* CachedAppDelegate;

	/*
	* Platform application
	*/
	static FApplication PlatformApplication;
};