#include "D3D12GraphicsSystemInfo.h"

#include <Debugging/Log/DebugLog.h>

#include <Graphics/DXGIFactoryWrapper/DXGIFactoryWrapper.h>
#include <Graphics/XPGL/PhysicalDevice/PhysicalDevice.h>

FD3D12GraphicsSystemInfo::~FD3D12GraphicsSystemInfo()
{
	ClearCachedData();
}

bool FD3D12GraphicsSystemInfo::EnumerateAndCachePhysicalDevices()
{
	//Clear old data
	ClearCachedData();

	//Get DXGIFactory
#if IDXGI_FACTORY_VERSION == 4
	IDXGIFactory4* DXGIFactory = nullptr;
#endif

	DXGIFactory = FDXGIFactoryWrapper::Get().GetDXGIFactory();
	assert(DXGIFactory != nullptr);

#if IDXGI_FACTORY_VERSION == 4
	//Number of Physical Devices
	IDXGIAdapter1* Adapter = nullptr;
	while(DXGIFactory->EnumAdapters1(PhysicalDeviceCount, &Adapter) != DXGI_ERROR_NOT_FOUND)
	{
		++PhysicalDeviceCount;

		//EnumAdapters() will increase reference count
		Adapter->Release();
		Adapter = nullptr;
	}
#endif

	assert(PhysicalDeviceCount >= 0);

	//For each physical device, cache some info on it. 
	PhysicalDevicesArray = MGE_NEW FPhysicalDevice[PhysicalDeviceCount];
	assert(PhysicalDevicesArray != nullptr);

	for (unsigned i = 0; i < PhysicalDeviceCount; i++)
	{
		assert(PhysicalDevicesArray[i].InitPhysicalDevice(i));
	}

	//Done
	return true;
}

void FD3D12GraphicsSystemInfo::ClearCachedData()
{
	PhysicalDeviceCount = 0;
	if (PhysicalDevicesArray != nullptr)
	{
		delete[] PhysicalDevicesArray;
		PhysicalDevicesArray = nullptr;
	}
}