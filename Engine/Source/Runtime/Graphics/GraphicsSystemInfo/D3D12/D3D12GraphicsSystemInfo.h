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
	bool EnumerateAndCachePhysicalDevices() override;

	/*
	* Enumerates output adapters - eg: monitors attached to this system
	*/
	bool EnumerateAndCacheOutputAdapters() override;

	/*
	* Called during engine shutdown - clear any cached data
	*/
	void ClearCachedData() override;

protected:
	/*
	* Virtual destructor - hidden
	*/
	virtual ~FD3D12GraphicsSystemInfo() = 0 {};

};