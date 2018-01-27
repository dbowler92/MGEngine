//CorePlatform.h
//Created 12/01/18
//Created By Daniel Bowler
//
//Platform includes

#pragma once

#ifdef _PLATFORM_WINDOWS
#define PLATFORM_WINDOWS

//Win64?
#ifdef ARCHITECTURE_64BIT
#define PLATFORM_WIN64
#define PLATFORM_WINDOWS_64BIT
#endif

#include <Config/WindowsConfig.h>
#endif
