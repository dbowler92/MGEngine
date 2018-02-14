//IGraphicsSystemInfo.h
//Created 13/02/18
//Created By Daniel Bowler
// 
//Interface class for API specific implementations. Will be used to enumerate
//the physical devices in the system and the output adapters (Eg: Monitors) attached
//to the system

#pragma once

#include <Core/CoreInclude.h>

class IGraphicsSystemInfo
{
public:
	/*
	 * TODO: Get the physical devices attached to this system
	 */

	/*
	 * TODO: Get the output adapters attached to this system
	 */

protected:
	/*
	* Enumerates physical devices
	*/
	virtual bool EnumerateAndCachePhysicalDevices() = 0;

	/*
	* Enumerates output adapters - eg: monitors attached to this system
	*/
	virtual bool EnumerateAndCacheOutputAdapters() = 0;

	/*
	* Called during engine shutdown - clear any cached data
	*/
	virtual void ClearCachedData() = 0;

protected:
	/*
	* Hide constructors - only FLowLevelGraphics should create an instance of this.
	*/
	IGraphicsSystemInfo() {};
	IGraphicsSystemInfo(IGraphicsSystemInfo& other);
	IGraphicsSystemInfo& operator=(IGraphicsSystemInfo& other);

	/*
	* Virtual destructor - hidden
	*/
	virtual ~IGraphicsSystemInfo() = 0 {};
};
