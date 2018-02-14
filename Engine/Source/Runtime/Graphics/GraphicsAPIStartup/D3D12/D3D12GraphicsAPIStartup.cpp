#include "D3D12GraphicsAPIStartup.h"

#include <Graphics/DXGIWrapper/DXGIWrapper.h>

bool FD3D12GraphicsAPIStartup::Start()
{
	//Init DXGI Factory
	return FDXGIWrapper::Get().GetDXGIFactory() != nullptr ? true : false;
}

bool FD3D12GraphicsAPIStartup::OnShutdown()
{
	//Release DXGIFactory if it still exists.
	FDXGIWrapper::Get().ReleaseDXGIFactory();
	
	//Done
	return true;
}