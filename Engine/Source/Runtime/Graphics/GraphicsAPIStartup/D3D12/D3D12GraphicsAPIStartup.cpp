#include "D3D12GraphicsAPIStartup.h"

#include <Debugging/Log/DebugLog.h>

#include <Graphics/DXGIFactoryWrapper/DXGIFactoryWrapper.h>

bool FD3D12GraphicsAPIStartup::Start()
{
	//Print something to the console
	FDebugLog::PrintInfoMessage("Graphics API: D3D12");

	//Init DXGI Factory
	return FDXGIFactoryWrapper::Get().GetDXGIFactory() != nullptr ? true : false;
}

bool FD3D12GraphicsAPIStartup::OnShutdown()
{
	//Release DXGIFactory if it still exists.
	FDXGIFactoryWrapper::Get().ReleaseDXGIFactory();

	//Done
	return true;
}