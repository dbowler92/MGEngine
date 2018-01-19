#include "Engine.h"

#include <assert.h>

#include <Core/ApplicationDelegate/IApplicationDelegate.h>

IApplicationDelegate* FEngine::CachedAppDelegate = nullptr;
FApplication FEngine::PlatformApplication;

int FEngine::Start(void* AppInstance, void* CmdLine,
	const char* AppTitle, IApplicationDelegate* AppDelegate)
{
	//Ensure we have an app delegate and cahce reference to it. 
	assert(AppDelegate != nullptr);
	CachedAppDelegate = AppDelegate;

	//1) Pre engine init
	assert(AppDelegate->OnPreEngineInit());

	//2) Init OS / platform
	assert(PlatformApplication.InitPlatform(AppInstance, CmdLine, AppTitle, 960, 540));
	
	//3) Init engine (eg: subsystems, static data etc)
	FEngine::InitEngine(AppInstance, CmdLine, AppTitle, AppDelegate);

	//4) Post engine init. 
	assert(PlatformApplication.OnPostEngineInit());
	assert(AppDelegate->OnPostEngineInit());

	//5) Enter game loop
	assert(FEngine::EnterMainGameLoop());
	
	//6) Shutdown app and engine.
	assert(AppDelegate->OnShutdown());
	assert(FEngine::ShutdownEngine());

	return 0;
}

bool FEngine::InitEngine(void* AppInstance, void* CmdLine,
	const char* AppTitle, class IApplicationDelegate* AppDelegate)
{

	return true;
}

bool FEngine::EnterMainGameLoop()
{
	//while(true)
	{
		//Tick platform application
		PlatformApplication.OnPreMainGameLoopTick();

		//Update

		//Render

	}

	return true;
}

bool FEngine::ShutdownEngine()
{
	//Shutdown app
	assert(PlatformApplication.OnShutdown());

	//And engine
	//
	
	return true;
}