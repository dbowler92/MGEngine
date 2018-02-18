//DXGIFactoryWrapper.h
//Created 11/02/18
//Created By Daniel Bowler
// 
//Manages an IDXGIFactory*. This is created when you first call GetDXGIFactory() and is cached
//until you call ReleaseDXGIFactory() (Or at engine shutdown). After releasing the factory, another
//will be created when you can GetDXGIFactory() again.
// 
//IDXGIFactory* version will be defined in D3D12Config.h

#pragma once

#include <Core/CoreInclude.h>

//DXGI header
#if IDXGI_FACTORY_VERSION == 4
#include <dxgi1_4.h>
#elif IDXGI_FACTORY_VERSION == 5
#include <dxgi1_5.h>
#elif IDXGI_FACTORY_VERSION == 6
#include <dxgi1_6.h>
#endif

class FDXGIFactoryWrapper
{
	HIDE_CONSTRUCTOR(FDXGIFactoryWrapper);
	HIDE_COPY_ASSIGNMENT(FDXGIFactoryWrapper);

public:
	/*
	 * Get the singleton instance
	 */
	inline static FDXGIFactoryWrapper& Get()
	{
		static FDXGIFactoryWrapper Instance;
		return Instance;
	}

	/*
	 * Gets the DXGI Version
	 */
	UINT8 GetDXGIVersion() { return (UINT8)IDXGI_FACTORY_VERSION; };

	/*
	 * Gets the cached IDXGIFactory* object - we use this, in D3D, to create the swapchain
	 * and enumerate devices + output devices (eg: Monitors). If this is called when DXGIFactory
	 * is nullptr, we will init a new DXGIFactory object. 
	 */
#if IDXGI_FACTORY_VERSION == 4
	IDXGIFactory4* GetDXGIFactory();
#endif 

	/*
	 * Releases the cached DXGIFactory instance
	 */
	void ReleaseDXGIFactory();

private:
	/*
	 * Destructor - Will cleanup the DXGI factory for us
	 */
	~FDXGIFactoryWrapper();

	/*
	 * Cached IDXGIFactory
	 */
#if IDXGI_FACTORY_VERSION == 4
	IDXGIFactory4* DXGIFactory = nullptr;
	bool CreateDXGIFactory(bool bEnableDXGIDebugging);
#endif
};