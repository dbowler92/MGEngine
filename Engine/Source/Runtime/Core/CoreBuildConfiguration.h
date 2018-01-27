//CoreBuildConfiguration.h
//Created 27/01/18
//Created By Daniel Bowler
// 
//Build settings

#pragma once

//Set via Project->Properties
#ifdef _CONFIGURATION_DEBUG
#define CONFIGURATION_DEBUG
#endif
#ifdef _CONFIGURATION_DEVELOPMENT
#define CONFIGURATION_DEVELOPMENT
#endif
#ifdef _CONFIGURATION_RELEASE
#define CONFIGURATION_RELEASE
#endif