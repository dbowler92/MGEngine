#include "Engine.h"

#include <assert.h>
#include <string> //TODO: Custom string wrapper...

#include <Debugging/Log/DebugLog.h>

#include <Core/ApplicationDelegate/IApplicationDelegate.h>
#include <Graphics/LowLevelGraphics/LowLevelGraphics.h>

int FEngine::Run(void* AppInstance, void* CmdLine,
	const char* AppTitle, IApplicationDelegate* AppDelegate)
{
	//Ensure we have an app delegate and cahce reference to it. 
	assert(AppDelegate != nullptr);
	CachedAppDelegate = AppDelegate;

	//Cache Platform performance before starting the engine.
	//
	//TODO: RAM, GPU's, monitors, more info on the CPUs (eg: Cache size + count, etc)
	assert(SystemInfo.InitSystemInfo());
	
	//Log system info
	FEngine::Get().LogSystemInfo();

	//
	//TODO: Ini file reading - so we know the engine 
	//settings before initing the engine. Eg: screen size
	//for the window and backbuffer(s)
	// 
	uint32_t InitialScreenSizeWidth = 960;  //TODO: From ini
	uint32_t InitialScreenSizeHeight = 540; //TODO: From ini

	//1) Pre engine init
	assert(AppDelegate->OnPreEngineInit());

	//2) Init OS / platform
	assert(Platform.InitPlatform(AppInstance, CmdLine, AppTitle, 
		InitialScreenSizeWidth, InitialScreenSizeHeight));
	
	//3) Init engine (eg: subsystems, static data etc)   
	FEngine::Get().InitEngine(AppInstance, CmdLine, AppTitle,
		InitialScreenSizeWidth, InitialScreenSizeHeight);

	//4) Post engine init. 
	assert(Platform.OnPostEngineInit());
	assert(AppDelegate->OnPostEngineInit());

	//5) Enter game loop
	assert(FEngine::Get().EnterMainGameLoop());
	
	//6) Shutdown app and engine.
	assert(AppDelegate->OnShutdown());
	assert(FEngine::Get().ShutdownEngine());

	return 0;
}

bool FEngine::InitEngine(void* AppInstance, void* CmdLine,
	const char* AppTitle, uint32_t InitialWindowWidth, uint32_t InitialWindowHeight)
{
	//Init graphics 
	assert(FLowLevelGraphics::Get().Start(&Platform));
	
	return true;
}

bool FEngine::ShutdownEngine()
{
	//Shutdown app
	assert(Platform.OnShutdown());

	//And engine
	assert(FLowLevelGraphics::Get().Shutdown());

	return true;
}

void FEngine::ShutdownNextTick()
{
	bShouldShutdownNextTick = true;
}

bool FEngine::EnterMainGameLoop()
{
	while(!bShouldShutdownNextTick)
	{
		//Tick platform
		Platform.OnPlatformTick();

		//Events

		//Update

		//Render (TODO: Render frame n-1)

		//
		//TEMP
		//
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			ShutdownNextTick();
		}
	}

	return true;
}

const FGraphicsSystemInfo& FEngine::GetGraphicsSystemInfo()
{
	return FLowLevelGraphics::Get().GetGraphicsSystemInfo();
}

void FEngine::LogSystemInfo()
{
	FDebugLog::PrintInfoMessage("*****************System Info*****************");

	std::string Str; //TODO: Replace std::string
	
	//CPU count (logical + physical)
	Str = "Physical CPU Core Count: " + std::to_string(SystemInfo.GetPhysicalCPUCoreCount());
	FDebugLog::PrintInfoMessage(Str.c_str());

	Str = "Logical CPU Core Count: " + std::to_string(SystemInfo.GetLogicalCPUCoreCount());
	FDebugLog::PrintInfoMessage(Str.c_str());

	//RAM	
	Str = "Installed System RAM (Bytes): " + std::to_string(SystemInfo.GetSystemRAMInBytes()) + " (MB): " + std::to_string(SystemInfo.GetSystemRAMInMB());
	FDebugLog::PrintInfoMessage(Str.c_str());
}