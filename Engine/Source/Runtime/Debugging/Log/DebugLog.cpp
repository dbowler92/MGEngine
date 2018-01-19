#include "DebugLog.h"

#ifdef PLATFORM_WIN32
#include <Windows.h>
#endif

void FDebugLog::PrintMessage(const char* Msg)
{
#ifdef PLATFORM_WIN32
	OutputDebugStringA(Msg);
#endif
}

void FDebugLog::PrintInfoMessage(const char* Msg)
{
#ifdef PLATFORM_WIN32
	OutputDebugStringA("Debug Info: ");
	OutputDebugStringA(Msg);

	if (!DoesStringEndInNewLine(const_cast<char*>(Msg)))
		OutputDebugStringA("\n");

#endif
}

void FDebugLog::PrintWarningMessage(const char* Msg)
{
#ifdef PLATFORM_WIN32 
	OutputDebugStringA("Debug Warning: ");
	OutputDebugStringA(Msg);

	if (!DoesStringEndInNewLine(const_cast<char*>(Msg)))
		OutputDebugStringA("\n");
#endif

#if ENGINE_CONFIG_STOP_EXECUTION_ON_WARNING_MSG
	PrintInfoMessage("DebugLog: Halting execution on warning...\n");
	while (1) {};
#endif
}

void FDebugLog::PrintErrorMessage(const char* Msg)
{
#ifdef PLATFORM_WIN32 
	OutputDebugStringA("Debug Error: ");
	OutputDebugStringA(Msg);

	if (!DoesStringEndInNewLine(const_cast<char*>(Msg)))
		OutputDebugStringA("\n");
#endif

#if ENGINE_CONFIG_STOP_EXECUTION_ON_ERROR_MSG
	PrintInfoMessage("DebugLog: Halting execution on error...\n");
	while (1) {};
#endif
}

//
//Internal
//
bool FDebugLog::DoesStringEndInNewLine(char* Msg)
{
	char* C = &Msg[0];
	char LastChar = '\0';
	while (*C != '\0')
	{
		//Store last char for future reference. 
		LastChar = *C;

		//Next char
		C++;
	}

	if (LastChar == '\n')
		return true;
	else
		return false;
}