//Window.h
//Created 12/01/18
//Created by Daniel Bowler
//
//OS Window.

#pragma once

#include <Core/CoreInclude.h>

#ifdef PLATFORM_WIN32
#include "Win32/Win32Window.h" 

GENERATE_PLATFORM_AGNOSTIC_CLASS(FWindow, FWin32Window) 
#endif 