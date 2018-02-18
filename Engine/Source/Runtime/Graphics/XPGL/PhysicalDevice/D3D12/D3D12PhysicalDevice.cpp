#include "D3D12PhysicalDevice.h"

#include <Debugging/Log/DebugLog.h>

#include <Graphics/DXGIFactoryWrapper/DXGIFactoryWrapper.h>
#include <Graphics/XPGL/AdapterOutput/AdapterOutput.h>

FD3D12PhysicalDevice::~FD3D12PhysicalDevice()
{
	CleanupCachedAdapterOutputs();

	if (DXGIAdapter)
	{
		DXGIAdapter->Release();
		DXGIAdapter = nullptr;
	}
}

bool FD3D12PhysicalDevice::InitPhysicalDevice(unsigned AdapterIndex)
{
	//Ensure not reiniting...
	assert(DXGIAdapter == nullptr);

	//Get DXGIFactory
#if IDXGI_FACTORY_VERSION == 4
	IDXGIFactory4* DXGIFactory = nullptr;
#endif

	DXGIFactory = FDXGIFactoryWrapper::Get().GetDXGIFactory();
	assert(DXGIFactory != nullptr);

#if IDXGI_FACTORY_VERSION == 4
	HRESULT HR = DXGIFactory->EnumAdapters1(AdapterIndex, &DXGIAdapter);
	if (FAILED(HR))
	{
		FDebugLog::PrintErrorMessage("FD3D12PhysicalDevice::InitPhysicalDevice(): EnumAdapters1() failed\n");
		return false;
	}

	assert(DXGIAdapter);

	//Cache desc
	DXGIAdapter->GetDesc1(&DXGIAdapterDesc);
#endif

	//Cache adapter outputs at init time
	assert(RefreshCachedAdapterOutputs());

	//Convert from WChar to char for adapter/device name
	size_t NumCharsConverted;
	wcstombs_s(&NumCharsConverted, &PhysicalDeviceName[0], sizeof(char) * 128, DXGIAdapterDesc.Description, sizeof(char) * 128);

	return true;
}

bool FD3D12PhysicalDevice::RefreshCachedAdapterOutputs()
{
	//Cleanup
	CleanupCachedAdapterOutputs();

	if (DXGIAdapter != nullptr)
	{
		//Recache
		//
		//Count:
		IDXGIOutput* Output = nullptr;
		while (DXGIAdapter->EnumOutputs(CachedOutputAdaptersCount, &Output) != DXGI_ERROR_NOT_FOUND)
		{
			++CachedOutputAdaptersCount;

			//EnumOutputs() will increase internal reference count
			Output->Release();
			Output = nullptr;
		}

		if (CachedOutputAdaptersCount > 0)
		{
			CachedAdapterOutputsArray = MGE_NEW FAdapterOutput[CachedOutputAdaptersCount];
			assert(CachedAdapterOutputsArray != nullptr);

			for (unsigned i = 0; i < CachedOutputAdaptersCount; i++)
			{
				CachedAdapterOutputsArray[i].InitAdapterOutput(i, (FPhysicalDevice*)this);
			}
		}
	}

	return true;
}

const char* FD3D12PhysicalDevice::GetPhysicalDeviceName()
{
	if (DXGIAdapter)
	{
		return &PhysicalDeviceName[0];
	}
	else
	{
		return nullptr;
	}
}

uint64 FD3D12PhysicalDevice::GetDeviceDedicatedVideoMemoryInBytes()
{
	if (DXGIAdapter)
	{
		return (uint64)DXGIAdapterDesc.DedicatedVideoMemory;
	}
	else
	{
		return 0;
	}
}

uint64 FD3D12PhysicalDevice::GetDeviceDedicatedSystemMemoryInBytes()
{
	if (DXGIAdapter)
	{
		return (uint64)DXGIAdapterDesc.DedicatedSystemMemory;
	}
	else
	{
		return 0;
	}
}

void FD3D12PhysicalDevice::CleanupCachedAdapterOutputs()
{
	if (CachedAdapterOutputsArray != nullptr)
	{
		delete[] CachedAdapterOutputsArray;
		CachedAdapterOutputsArray = nullptr;
	}
	CachedOutputAdaptersCount = 0;
}