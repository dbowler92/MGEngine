/**
 * App delegate class - Each individual project using the engine lib 
 * will create one of these and pass it to the engine. It will be informed
 * of engine events at runtime. 
 */
#pragma once

#include "Core/CoreInclude.h"

class IAppDelegate
{
public:
	virtual ~IAppDelegate() = 0 {};

	/**
	 * Main engine startup / shutdown events
	 */
	virtual bool OnPostEngineInit() = 0;
	virtual bool OnPreEngineShutdown() = 0;

	/**
	 * Called during engine startup, returns a pointer to the 
	 * initial active scene to load
	 */
	//virtual IScene* GetInitialScene() = 0;
	
};