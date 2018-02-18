//IAdapterOutput.h
//Created 17/02/18
//Created By Daniel Bowler
// 
//Represents an output attached to a FPhysicalDevice - Eg: A monitor

#pragma once

#include <Core/CoreInclude.h>

class IPhysicalDevice;

class IAdapterOutput
{
public:
	/**
	 * Gets the name of the output device
	 */
	virtual const char* GetOutputDeviceName() = 0;

	/**
	 * TODO: Ask this AdapterOutput, for a given format (Will need to have a platform
	 * independent way of handling formats - a map? Which maps from platform independent
	 * format (Eg: MGE_FORMAT_RGBA8_UNORM) to API specifc (Eg: DXGI_FORMAT_R8G8B8A8_UNORM) - via a macro)
	 * what the resolution is, refresh rate, etc
	 * 
	 * Maybe even cache this info at init time...
	 */

protected:
	/**
	 * Virtual Destructor - Hidden.
	 */
	virtual ~IAdapterOutput() = 0 {};

private:
	/**
	 * Called by <Platform>PhysicalDevice - inits a single adapter output (eg monitor). Caches
	 * useful info - eg: resolution etc. 
	 */
	virtual bool InitAdapterOutput(unsigned OutputIndex, IPhysicalDevice* PhysicalDevice) = 0;
};