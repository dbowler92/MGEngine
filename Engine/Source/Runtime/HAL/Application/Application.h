//Application.h
//Created 23/07/16
//Created by Daniel Bowler
//
//Application layer of the engine. Each game that uses this engine
//should define a game specific class that inherits from this
//base application class & implement the virtual functions.

#pragma once

#include <Core/CoreInclude.h>

#ifdef PLATFORM_WIN32
#include "Win32/Win32Application.h"

GENERATE_PLATFORM_AGNOSTIC_CLASS(FApplication, FWin32Application)
#endif 