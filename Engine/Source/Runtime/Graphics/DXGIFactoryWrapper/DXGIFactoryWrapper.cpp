#include "DXGIFactoryWrapper.h"

#include <assert.h>

#include <Debugging/Log/DebugLog.h>

FDXGIFactoryWrapper::~FDXGIFactoryWrapper()
{
	ReleaseDXGIFactory();
}

void FDXGIFactoryWrapper::ReleaseDXGIFactory()
{
	if (DXGIFactory)
	{
		DXGIFactory->Release();
		DXGIFactory = nullptr;
	}
}

#if IDXGI_FACTORY_VERSION == 4
IDXGIFactory4* FDXGIFactoryWrapper::GetDXGIFactory()
{
	if (DXGIFactory == nullptr)
	{
		//Need to create it
#if defined(CONFIGURATION_DEBUG) || defined(CONFIGURATION_DEVELOPMENT)
		bool bDebuggingDXGI = true;
#else
		bool bDebuggingDXGI = false;
#endif

		assert(CreateDXGIFactory(bDebuggingDXGI));
	}

	return DXGIFactory;
}

bool FDXGIFactoryWrapper::CreateDXGIFactory(bool bEnableDXGIDebugging)
{
	//DXGI Version
	FDebugLog::PrintInfoMessage("Creating new IDXGIFactory - Version: 1.4");

	//IDXGIFactory version 4
	UINT Flags = 0;

	if (bEnableDXGIDebugging)
	{   
		Flags = DXGI_CREATE_FACTORY_DEBUG;
	}

	HRESULT Hr = CreateDXGIFactory2(Flags, IID_PPV_ARGS(&DXGIFactory));
	if (FAILED(Hr))
	{
		FDebugLog::PrintErrorMessage("IDXGIFactory4* FDXGIWrapper::CreateDXGIFactory() Failed!");

		ReleaseDXGIFactory();

		return false;
	}

	return true;
}
#endif //IDXGI_FACTORY_VERSION == 4