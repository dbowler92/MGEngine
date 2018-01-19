//DebugLog.h
//Created 16/04/17
//Created By Daniel Bowler
//
//Helper class which will be used to output debug info to the console, output window
//or log file (added as and when needed) - should be platform independent
  
#pragma once

#include <Core/CoreInclude.h>

//Assert if required
#include <assert.h>

class FDebugLog
{
	MAKE_STATICS_CLASS_ONLY(FDebugLog);

public:
	//To VS output window
	static void PrintMessage(const char* Msg);
	static void PrintInfoMessage(const char* Msg);
	static void PrintWarningMessage(const char* Msg);
	static void PrintErrorMessage(const char* Msg);

private:
	//Internal functions
	//
	//Tests string to see if it ends in '\n'
	static bool DoesStringEndInNewLine(char* Msg);
};