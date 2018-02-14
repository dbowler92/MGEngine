//Platform.h
//Created 23/07/16
//Created by Daniel Bowler
//
//Represents each platform. 

#pragma once

#include <Core/CoreInclude.h>

#ifdef PLATFORM_WINDOWS
#include "Win32/Win32Platform.h"

GENERATE_PLATFORM_AGNOSTIC_CLASS(FPlatform, FWin32Platform)
#endif 