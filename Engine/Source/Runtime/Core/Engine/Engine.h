//Engine.h
//Created 13/01/18
//Created By Daniel Bowler
//
//Called within the application main function, this setsup and runs
//the engine / game - This defines a platform and API agnostic
//engine startup order.

#pragma once

#include <Core/CoreInclude.h>
#include <HAL/Platform/Platform.h>

#include <HAL/SystemInfo/SystemInfo.h>
#include <Graphics/GraphicsSystemInfo/GraphicsSystemInfo.h>

class FEngine
{
	HIDE_CONSTRUCTOR_DESTRUCTOR(FEngine);
	HIDE_COPY_ASSIGNMENT(FEngine);

public:
	/*
	 * Gets the shared singleton instance
	 */
	inline static FEngine& Get()
	{
		static FEngine Instance;
		return Instance;
	}

	/*
	* Begins the engine, enters the main game loop and then handles shutdown
	* once we break from the main game loop - TODO: Remove void* here
	*/
	int Run(void* AppInstance, void* CmdLine,
		const char* AppTitle, class IApplicationDelegate* AppDelegate);

	/*
	 * Shutdown the engine next tick - Can be called from game projects
	 */
	void ShutdownNextTick();

	/*
	* Gets the system info - eg: CPU count and graphics info (physical devices, output adapters etc)
	*/
	const FSystemInfo& GetSystemInfo() { return SystemInfo; };
	const FGraphicsSystemInfo& GetGraphicsSystemInfo();

	/*
	* Gets the cached application specific app delegate
	*/
	IApplicationDelegate* GetCachedAppDelegate() { return CachedAppDelegate; };

	/*
	 * Gets the platform application class - Win32, IOS, etc
	 */
	FPlatform* GetPlatformAbstraction() { return &Platform; };
	
private:
	/*
	* Internally, inits the engine - platform agnostic ordering.
	*/
	bool InitEngine(void* AppInstance, void* CmdLine,
		const char* AppTitle, uint32_t InitialWindowWidth, uint32_t InitialWindowHeight);

	/*
	* Main game loop
	*/
	bool EnterMainGameLoop();

	/*
	* Shutdown engine
	*/
	bool ShutdownEngine();

private:
	/*
	 * Logs the system info once we have it
	 */
	void LogSystemInfo();

private:
	/*
	* System info - eg: CPU count and the like
	*/
	FSystemInfo SystemInfo;

	/*
	* Cache a reference to the game/app delegate
	*/
	class IApplicationDelegate* CachedAppDelegate = nullptr;

	/*
	* Platform application
	*/
	FPlatform Platform;

private:
	/*
	 * Is app due to shutdown next tick?
	 */
	bool bShouldShutdownNextTick = false;
};