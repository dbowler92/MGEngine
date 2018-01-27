//SandboxMain.cpp
//Created 22/07/16
//Created By Daniel Bowler
//
//Entry point for the sandbox project

#pragma once

#include <Core/CoreInclude.h>
#include <Core/Engine/Engine.h>

#include <Config/AppConfig.h>
#include <ApplicationDelegate/SandboxAppDelegate.h> //Our app delegate

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#include <crtdbg.h>

INT WINAPI wWinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, LPWSTR LpCmdLine, int CmdShow)    
{
	//Set up simple checks for memory leaks in windows.  
#ifdef CONFIGURATION_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	FSandboxAppDelegate AppDelegate;
	return FEngine::Start((void*)HInstance, (void*)LpCmdLine, "Sandbox", &AppDelegate);
}                
#endif 