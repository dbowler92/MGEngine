//PlatformWindow.h
//Created 12/01/18
//Created by Daniel Bowler
//
//OS Window.

#pragma once

#include <Core/CoreInclude.h>

#ifdef PLATFORM_WINDOWS
#include "Win32/Win32PlatformWindow.h" 

GENERATE_PLATFORM_AGNOSTIC_CLASS(FPlatformWindow, FWin32PlatformWindow) 
#endif 