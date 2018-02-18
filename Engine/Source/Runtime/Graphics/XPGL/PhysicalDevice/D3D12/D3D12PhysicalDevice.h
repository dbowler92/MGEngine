//D3D12PhysicalDevice.h
//Created 17/02/18
//Created By Daniel Bowler
// 
//Represents an IDXGIAdapter - Physically installed device capable of doing work with D3D12

#pragma once

#include <Graphics/XPGL/PhysicalDevice/IPhysicalDevice.h>

//DXGI header
#if IDXGI_FACTORY_VERSION == 4
#include <dxgi1_4.h>
#elif IDXGI_FACTORY_VERSION == 5
#include <dxgi1_5.h>
#elif IDXGI_FACTORY_VERSION == 6
#include <dxgi1_6.h>
#endif

class FD3D12GraphicsSystemInfo;

class FD3D12PhysicalDevice : public IPhysicalDevice
{
	//FD3D12GraphicsSystemInfo will init and destroy each physical device. 
	friend FD3D12GraphicsSystemInfo;

public:
	/**
	 * Refreshes the cached list of adapter outputs
	 */
	bool RefreshCachedAdapterOutputs() override;

public:
	/**
	 * Returns the (physical) device index
	 */
	uint32 GetPhysicalDeviceIndex() override { return PhysicalDeviceIndex; };

	/**
	 * Returns the adapter name
	 */
	const char* GetPhysicalDeviceName() override;

	/**
	* Returns the amount of dedicated video memory this physical device has in bytes (VRAM if a GPU)
	*/
	uint64 GetDeviceDedicatedVideoMemoryInBytes() override;

	/**
	* Returns the amount of dedicated system memory this physical device has in bytes
	*/
	uint64 GetDeviceDedicatedSystemMemoryInBytes() override;

	/**
	 * Returns the number of output devices attached to this physical device
	 */
	unsigned GetAdapterOutputCount() override { return CachedOutputAdaptersCount; };

	/**
	 * Returns a pointer to the Output devices attached to this physical device
	 */
	FAdapterOutput* GetAdapterOutputs() override { return CachedAdapterOutputsArray; };

public:
	/**
	 * D3D12 getters
	 */
#if IDXGI_FACTORY_VERSION == 4
	IDXGIAdapter1* GetDXGIAdapter() {return DXGIAdapter; };
	DXGI_ADAPTER_DESC1* GetAdapterDesc() { return &DXGIAdapterDesc; };
#endif

protected:
	/**
	 * Virtual Destructor - hidden
	 */
	virtual ~FD3D12PhysicalDevice() = 0;

private:
	/**
	 * Called by FGraphicsSystemInfo - during engine startup.
	 *
	 * Init's the PhysicalDevice given an adapter index. Each API will be able to
	 * tell us the number of adapters installed and able to be used
	 *
	 * Also, should cache the adapter outputs during engine startup
	 */
	virtual bool InitPhysicalDevice(unsigned AdapterIndex) override;

private:
	/**
	 * Cleansup our cached adapter outputs array
	 */
	void CleanupCachedAdapterOutputs();

private:
#if IDXGI_FACTORY_VERSION == 4
	/**
	 * DXGI Adapter - We will have to release this before the app closes
   */
	IDXGIAdapter1* DXGIAdapter = nullptr;

	/**
 	 * DXGI Description - Contains a lot of info on this physical device
	 */
	DXGI_ADAPTER_DESC1 DXGIAdapterDesc;
#endif

	/**
	 * Physical device index
	 */
	uint32 PhysicalDeviceIndex = 0xffffffff;

	/**
	 * Adapter name - Eg: NVIDIA GTX 970. TODO: Don't really want to be storing this
	 * buffer twice (it already exists, in WCHAR form, in DXGI_ADAPTER_DESC1.Description...
	 * 
	 * Need own string class and/or platform independent WCHAR
	 */
	char PhysicalDeviceName[128];

	/**
 	 * Cached adapter outputs attached to this device
	 */
	unsigned CachedOutputAdaptersCount = 0;
	FAdapterOutput* CachedAdapterOutputsArray = nullptr;
}; 