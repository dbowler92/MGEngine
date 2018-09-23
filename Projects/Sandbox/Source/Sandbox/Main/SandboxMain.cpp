#pragma once

#include "Runtime/Core/CoreEngine.h"

#include "Runtime/Core/CoreInclude.h"
#include "Sandbox/AppDelegate/SandboxAppDelegate.h"


INT WINAPI wWinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, LPWSTR LpCmdLine, int CmdShow)
{
	//Set up simple checks for memory leaks in windows.  
#if defined(CONFIGURATION_DEBUG) || defined(CONFIGURATION_DEVELOPMENT)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	static FSandboxAppDelegate AppDelegate;
	static LPCWSTR Win32AppMainWindowTitle = L"DX12 Sandbox";

	static FEngineStartupParams EngineParams;
	EngineParams.AppDelegate = (IAppDelegate*)&AppDelegate;
	EngineParams.DefaultMainWindowTitle = (void*)&Win32AppMainWindowTitle;
	EngineParams.DefaultWindowWidth = 800;
	EngineParams.DefaultWindowHeight = 600;
	EngineParams.AppHandle = (void*)&HInstance;
	EngineParams.PrevAppHandle = (void*)&HPrevInstance;
	EngineParams.CmdLine = (void*)&LpCmdLine;
	EngineParams.CmdShow = (void*)&CmdShow;

	//Call in to the engine.
	FCoreEngine* Engine = FCoreEngine::GetInstance();
	int32 ReturnValue = Engine->RunEngine(EngineParams);

	//Done
	return ReturnValue;
}
