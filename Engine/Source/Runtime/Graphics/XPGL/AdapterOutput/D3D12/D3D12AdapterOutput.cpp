#include "D3D12AdapterOutput.h"

#include <Debugging/Log/DebugLog.h>

#include <Graphics/XPGL/PhysicalDevice/PhysicalDevice.h>

FD3D12AdapterOutput::~FD3D12AdapterOutput()
{
	if (DXGIOutput != nullptr)
	{
		DXGIOutput->Release();
		DXGIOutput = nullptr;
	}
}

bool FD3D12AdapterOutput::InitAdapterOutput(unsigned OutputIndex, IPhysicalDevice* PhysicalDevice)
{
	//Safe to case
	FD3D12PhysicalDevice* D3D12PhysicalDevice = (FD3D12PhysicalDevice*)PhysicalDevice;
	assert(D3D12PhysicalDevice != nullptr);

	//Cache output device index
	OutputDeviceIndex = OutputIndex;

#if IDXGI_FACTORY_VERSION == 4
	//Get the IDXGIAdapter*
	IDXGIAdapter1* DXGIAdapter = nullptr;
#endif

	DXGIAdapter = D3D12PhysicalDevice->GetDXGIAdapter();
	assert(DXGIAdapter != nullptr);

#if IDXGI_FACTORY_VERSION == 4
	HRESULT HR = DXGIAdapter->EnumOutputs(OutputIndex, &DXGIOutput);
	if (FAILED(HR))
	{
		FDebugLog::PrintErrorMessage("FD3D12AdapterOutput::InitAdapterOutput() - EnumOutputs() Failed");
		return false;
	}

	assert(DXGIOutput);

	//Cache desc
	DXGIOutput->GetDesc(&DXGIOutputDesc);
#endif

	//Convert device name from WCHAR to char
	size_t NumCharsConverted;
	wcstombs_s(&NumCharsConverted, &OutputDeviceName[0], sizeof(char) * 32, DXGIOutputDesc.DeviceName, sizeof(char) * 32);

	return true;
} 