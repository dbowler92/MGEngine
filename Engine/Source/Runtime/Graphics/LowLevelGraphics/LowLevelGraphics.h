//FLowLevelGraphics.h
//Created 11/02/18
//Created By Daniel Bowler
//
//Low level graphics subsystem - Enumerates all devices / outputs, inits D3D/Vulkan/etc, 
//setups command queues, memory management systems, swapchain etc

#pragma once

#include <Core/CoreInclude.h>

#include <Graphics/GraphicsAPIStartup/GraphicsAPIStartup.h>
#include <Graphics/GraphicsSystemInfo/GraphicsSystemInfo.h>

class FLowLevelGraphics
{
	HIDE_CONSTRUCTOR_DESTRUCTOR(FLowLevelGraphics);
	HIDE_COPY_ASSIGNMENT(FLowLevelGraphics);

	//FEngine calls Start() and Shutdown()
	friend class FEngine;

public:
	/*
	 * Gets the shared singleton instance
	 */
	inline static FLowLevelGraphics& Get()
	{
		static FLowLevelGraphics Instance;
		return Instance;
	}

	/*
	 * Returns the graphics system info - List of physical devices and a list of the
	 * attached output adapters (eg: monitors)
	 */
	const FGraphicsSystemInfo& GetGraphicsSystemInfo() { return GraphicsSystemInfo; };

private:
	/*
	 * Start the subsystem - Called by FEngine
	 */
	bool Start(class FPlatform* PlatformApp);

	/*
	 * Shutdown the subsystem - Called by FEngine
	 */
	bool Shutdown();

private:
	/*
	 * Debug logs the physical devices and the attached output adapters to the console
	 * after they have been cached (FGraphicsSystemInfo)
	 */
	void LogPhysicalDevices(bool bLogOutputDevices);

private:
	/*
	 * Graphics API startup - Handles API specific startup before we go ahead and 
	 * init the FLowLevelGraphics subsystem. 
	 */ 
	FGraphicsAPIStartup GraphicsAPIStartup;

	/*
	 * Enumerates the system and caches the installed physical devices. Also, will 
	 * cache data on each output adapter (eg: a monitor)
	 */
	FGraphicsSystemInfo GraphicsSystemInfo;
};