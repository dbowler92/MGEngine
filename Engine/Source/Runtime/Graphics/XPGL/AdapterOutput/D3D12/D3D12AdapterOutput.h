//D3D12AdapterOutput.h
//Created 17/02/18
//Created By Daniel Bowler
// 
//Represents an output attached to a FPhysicalDevice - Eg: A monitor. D3D12: Uses DXGI to obtain
//this data

#pragma once

#include <Graphics/XPGL/AdapterOutput/IAdapterOutput.h>

//DXGI header
#if IDXGI_FACTORY_VERSION == 4
#include <dxgi1_4.h>
#elif IDXGI_FACTORY_VERSION == 5
#include <dxgi1_5.h>
#elif IDXGI_FACTORY_VERSION == 6
#include <dxgi1_6.h>
#endif

class FD3D12PhysicalDevice;

class FD3D12AdapterOutput : public IAdapterOutput
{
	//FD3D12PhysicalDevice class will init us
	friend FD3D12PhysicalDevice;

public:
	/**
	 * Gets the name of the output device
	 */
	const char* GetOutputDeviceName() override { return OutputDeviceName; };

	/**
	* TODO: Ask this AdapterOutput, for a given format (Will need to have a platform
	* independent way of handling formats - a map? Which maps from platform independent
	* format (Eg: MGE_FORMAT_RGBA8_UNORM) to API specifc (Eg: DXGI_FORMAT_R8G8B8A8_UNORM) - via a macro)
	* what the resolution is, refresh rate, etc
	* 
	* Maybe even cache this info at init time...
	*/

public:
	/**
	 * D3D12 getters
	 */
#if IDXGI_FACTORY_VERSION == 4
	IDXGIOutput* GetDXGIOutput() { return DXGIOutput; };
	DXGI_OUTPUT_DESC* GetOutputDesc() { return &DXGIOutputDesc; };
#endif

protected:
	/**
	 * Virtual Destructor - Hidden.
   */
	virtual ~FD3D12AdapterOutput() = 0;
	 
private:
	/**
 	 * Called by <Platform>PhysicalDevice - inits a single adapter output (eg monitor). Caches
	 * useful info - eg: resolution etc.
	 */
	bool InitAdapterOutput(unsigned OutputIndex, IPhysicalDevice* PhysicalDevice) override;

private:
#if IDXGI_FACTORY_VERSION == 4
	/**
	 * DXGI Output - We will have to release this before the app closes
	 */
	IDXGIOutput* DXGIOutput = nullptr;

	/**
	 * Caches some useful info for us regarding this Output
	 */
	DXGI_OUTPUT_DESC DXGIOutputDesc;
#endif

	/**
	 * Output device index
	 */
	uint32 OutputDeviceIndex = 0xffffffff;

	/**
	 * Output device name. TODO: Don't really want to be storing this
	 * buffer twice (it already exists, in WCHAR form, in DXGI_ADAPTER_DESC1.Description...
	 *
	 * Need own string class and/or platform independent WCHAR
	 */
	char OutputDeviceName[32];
};
