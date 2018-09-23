/**
 * Defines the engine startup procedure, main game loop and shutdown procedure. 
 */

#pragma once

#include "Core/CoreInclude.h"
#include "Platform/Timer/Win32PlatformTimer.h"

class IAppDelegate;

struct FEngineStartupParams
{
	FEngineStartupParams()
		: AppDelegate(nullptr)
		, DefaultMainWindowTitle(nullptr)
		, DefaultWindowWidth(800)
		, DefaultWindowHeight(600)
		, AppHandle(nullptr)
		, PrevAppHandle(nullptr)
		, CmdLine(nullptr)
		, CmdShow(nullptr)
	{}

	IAppDelegate* AppDelegate;

	void* DefaultMainWindowTitle;
	uint32 DefaultWindowWidth;
	uint32 DefaultWindowHeight;

	void* AppHandle;
	void* PrevAppHandle;
	void* CmdLine;
	void* CmdShow;
};

class FCoreEngine
{
public:
	static FCoreEngine* GetInstance();

	int32 RunEngine(const FEngineStartupParams& EngineStartupParams);

public:
	void ShutdownNextTick();

private:
	IAppDelegate* CachedAppDelegate;
	
	FWin32PlatformTimer MainLoopTimer;
	
	bool bShouldShutdownNextTick;

private:
	FCoreEngine();
	~FCoreEngine();
	FCoreEngine(FCoreEngine& Other);
	FCoreEngine& operator=(FCoreEngine& Other);

	void InitEngine(const FEngineStartupParams& EngineStartupParams);
	void ShutdownEngine();
	int32 EnterMainGameLoop();
};