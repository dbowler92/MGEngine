//SandboxMain.cpp
//Created 22/07/16
//Created By Daniel Bowler
//
//Entry point for the sandbox project

#pragma once

#include <Engine/Core/CoreInclude.h>
#include <Engine/Core/Engine/Engine.h>

#include <Sandbox/AppConfig/AppConfig.h>
#include <Sandbox/ApplicationDelegate/SandboxAppDelegate.h> //Our app delegate

#ifdef PLATFORM_WIN32
#include <Windows.h>
#include <crtdbg.h>

void ShowConsoleW32()
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);

	*stdout = *hf_out;
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
}

INT WINAPI wWinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, LPWSTR LpCmdLine, int CmdShow)    
{
	//Set up simple checks for memory leaks in windows.  
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	FSandboxAppDelegate AppDelegate;
	return FEngine::Start((void*)HInstance, (void*)LpCmdLine, "Sandbox", &AppDelegate);
}                
#endif 