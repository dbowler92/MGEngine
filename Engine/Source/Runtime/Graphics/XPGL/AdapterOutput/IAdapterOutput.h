//IAdapterOutput.h
//Created 17/02/18
//Created By Daniel Bowler
// 
//Represents an output attached to a FPhysicalDevice - Eg: A monitor

#pragma once

#include <Core/CoreInclude.h>

class FPhysicalDevice;

class IAdapterOutput
{
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
	virtual bool InitAdapterOutput(unsigned OutputIndex, FPhysicalDevice* PhysicalDevice) = 0;
};