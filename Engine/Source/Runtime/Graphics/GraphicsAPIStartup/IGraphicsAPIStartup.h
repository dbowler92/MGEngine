//IGraphicsAPIStartup.h
//Created 13/02/18
//Created By Daniel Bowler
// 
//Interface for API specific startup - Called at the top of FLowLevelGraphics::Start()

#pragma once

#include <Core/CoreInclude.h>

class IGraphicsAPIStartup
{
protected:
	/*
	* Virtual Destructor
	*/
	virtual ~IGraphicsAPIStartup() = 0 {};

	/*
	 * Startup function - Called at the top of FLowLevelGraphics::Start()
	 */
	virtual bool Start() = 0;

	/*
	 * Called when the engine is shutdown. Again, by FLowLevelGraphics::Shutdown()
	 */
	virtual bool OnShutdown() = 0;
};