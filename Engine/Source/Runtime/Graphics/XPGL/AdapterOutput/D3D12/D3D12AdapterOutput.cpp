#include "D3D12AdapterOutput.h"

#include <Debugging/Log/DebugLog.h>

#include <Graphics/XPGL/PhysicalDevice/PhysicalDevice.h>

FD3D12AdapterOutput::~FD3D12AdapterOutput()
{

}

bool FD3D12AdapterOutput::InitAdapterOutput(unsigned OutputIndex, FPhysicalDevice* PhysicalDevice)
{
	assert(PhysicalDevice != nullptr);

#if IDXGI_FACTORY_VERSION == 4
	//Get the IDXGIAdapter*
	IDXGIAdapter1* DXGIAdapter = nullptr;
#endif

	DXGIAdapter = PhysicalDevice->GetDXGIAdapter();
	assert(DXGIAdapter != nullptr);

#if IDXGI_FACTORY_VERSION == 4

#endif

	return true;
} 