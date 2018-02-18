//IGraphicsSystemInfo.h
//Created 13/02/18
//Created By Daniel Bowler
// 
//Uses DXGI to enumerate physical devices and output devices for this
//users system

#pragma once

#include <Graphics/GraphicsSystemInfo/IGraphicsSystemInfo.h>

class FD3D12GraphicsSystemInfo : public IGraphicsSystemInfo
{
	//FLowLevelGraphics will call the EnumerateAndCache* functions & the clear cached
	//data function at appropriate times.
	friend class FLowLevelGraphics;

public:
	/**
	 * Get the number of physical devices attached to this system
	 */
	unsigned GetPhysicalDeviceCount() override { return PhysicalDeviceCount; };

	/**
	 * Gets a pointer to an array of physical devices
	 */
	FPhysicalDevice* GetPhysicalDevices() override { return PhysicalDevicesArray; };

protected:
	/**
	 * Virtual destructor - hidden
	 */
	virtual ~FD3D12GraphicsSystemInfo() = 0;

private:
	/**
	 * Enumerates physical devices + caches the output devices attached to
	 * said physical device at engine startup
	 */
	bool EnumerateAndCachePhysicalDevices() override;

	/**
	* Called during engine shutdown - clear any cached data
	*/
	void ClearCachedData() override;

private:
	/**
	 * The physical devices attached to this system compatable with D3D12
	 */
	unsigned PhysicalDeviceCount = 0;
	FPhysicalDevice* PhysicalDevicesArray = nullptr;
};