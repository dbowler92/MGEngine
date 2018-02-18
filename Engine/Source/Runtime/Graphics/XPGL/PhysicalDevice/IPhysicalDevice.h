//IPhysicalDevice.h
//Created 17/02/18
//Created By Daniel Bowler
// 
//Represents a single adapter / device attached to the system capable of doing work in D3D12 or Vulkan

#pragma once

#include <Core/CoreInclude.h>

class FAdapterOutput;

class IPhysicalDevice
{
public:
	/**
	 * Refreshes the cached list of adapter outputs - these could change whilst the game is running. Therefore, it's
	 * best to call this before getting the list of outputs. 
	 */
	virtual bool RefreshCachedAdapterOutputs() = 0;

public:
	/**
	 * Returns the (physical) device index
	 */
	virtual uint32 GetPhysicalDeviceIndex() = 0;

	/**
	* Returns the adapter name - Nullptr if error of some sort.
	*/
	virtual const char* GetPhysicalDeviceName() = 0;

	/**
	 * Returns the amount of dedicated video memory this physical device has in bytes (VRAM if a GPU)
	 */
	virtual uint64 GetDeviceDedicatedVideoMemoryInBytes() = 0;

	/**
	 * Returns the amount of dedicated system memory this physical device has in bytes
	 */
	virtual uint64 GetDeviceDedicatedSystemMemoryInBytes() = 0;

	/**
	 * Returns the number of output devices attached to this physical device
	 */
	virtual unsigned GetAdapterOutputCount() = 0;

	/**
	 * Returns a pointer to the Output devices attached to this physical device
	 */
	virtual FAdapterOutput* GetAdapterOutputs() = 0;

protected:
	/**
	 * Virtual Destructor - Hidden. 
	 */
	virtual ~IPhysicalDevice() = 0 {};

private:
	/**
	 * Called by FGraphicsSystemInfo - during engine startup.
	 *
	 * Init's the PhysicalDevice given an adapter index. Each API will be able to
	 * tell us the number of adapters installed and able to be used
	 * 
	 * Also, should cache the adapter outputs during engine startup
	 */
	virtual bool InitPhysicalDevice(unsigned AdapterIndex) = 0;
};