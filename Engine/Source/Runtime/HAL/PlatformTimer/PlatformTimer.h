//PlatformTimer.h
//Created 04/02/18
//Created by Daniel Bowler
//
//Platform timer.

#pragma once

#include <Core/CoreInclude.h>

#ifdef PLATFORM_WINDOWS
#include "Win32/Win32PlatformTimer.h" 

GENERATE_PLATFORM_AGNOSTIC_CLASS(FPlatformTimer, FWin32PlatformTimer)
#endif 