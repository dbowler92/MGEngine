//DXGIWrapper.h
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
#endif

class FDXGIWrapper
{
	HIDE_CONSTRUCTOR(FDXGIWrapper); 
	HIDE_COPY_ASSIGNMENT(FDXGIWrapper);

public:
	/*
	 * Get the singleton instance
	 */
	inline static FDXGIWrapper& Get()
	{
		static FDXGIWrapper Instance;
		return Instance;
	}

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
	~FDXGIWrapper();

	/*
	 * Cached IDXGIFactory
	 */
#if IDXGI_FACTORY_VERSION == 4
	IDXGIFactory4* DXGIFactory = nullptr;
	bool CreateDXGIFactory4(bool bEnableDXGIDebugging);
#endif
};