//IGraphicsSystemInfo.h
//Created 13/02/18
//Created By Daniel Bowler
// 
//Interface class for API specific implementations. Will be used to enumerate
//the physical devices in the system and the output adapters (Eg: Monitors) attached
//to the system

#pragma once

#include <Core/CoreInclude.h>

class FPhysicalDevice;

class IGraphicsSystemInfo
{
public:
	/**
	 * Get the number of physical devices attached to this system
	 */
	virtual unsigned GetPhysicalDeviceCount() = 0;

	/**
	 * Gets a pointer to an array of physical devices
	 */
	virtual FPhysicalDevice* GetPhysicalDevices() = 0;

private:
	/**
	 * Enumerates physical devices + caches the output devices attached to
	 * said physical device at engine startup
	 */
	virtual bool EnumerateAndCachePhysicalDevices() = 0;

	/**
	 * Called during engine shutdown - clear any cached data
	 */
	virtual void ClearCachedData() = 0;

protected:
	/**
	 * Hide constructors - only FLowLevelGraphics should create an instance of this.
	 */
	IGraphicsSystemInfo() {};
	IGraphicsSystemInfo(IGraphicsSystemInfo& other);
	IGraphicsSystemInfo& operator=(IGraphicsSystemInfo& other);

	/**
	 * Virtual destructor - hidden
	 */
	virtual ~IGraphicsSystemInfo() = 0 {};
};
