//Win32.h
//Created 18/04/17
//Created By Daniel Bowler
//
//Some config stuff for Win32 - removes it from EngineConfig.h which, it seems, may
//get too big for its own good!

#pragma once

//Win32 includes
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

//Win32 lean and mean!
#define WIN32_LEAN_AND_MEAN

//C-String representing the API being used
#define OS_PLATFORM_API_STRING "Win32"