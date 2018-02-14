//ISystemInfo.h
//Created 04/02/18
//Created By Daniel Bowler
//
//System info class will contain info on the users system - 
//Eg: CPU count, etc

#pragma once

#include <Core/CoreInclude.h>

#ifdef PLATFORM_WINDOWS
#include "Win32/Win32SystemInfo.h" 

GENERATE_PLATFORM_AGNOSTIC_CLASS(FSystemInfo, FWin32SystemInfo)
#endif 