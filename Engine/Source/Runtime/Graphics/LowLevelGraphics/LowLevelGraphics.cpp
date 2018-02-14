#include "LowLevelGraphics.h"

#include <Debugging/Log/DebugLog.h>
#include <HAL/Platform/Platform.h>

bool FLowLevelGraphics::Start(FPlatform* PlatformApp)
{
	FDebugLog::PrintInfoMessage("**********Starting LowLevelGraphics**********");

	assert(PlatformApp != nullptr); 

	//API Startup - Eg: Vulkan loader or initing DXGI factory
	assert(GraphicsAPIStartup.Start());

	//Enumerate physical devices and log them
	assert(GraphicsSystemInfo.EnumerateAndCachePhysicalDevices());
	LogPhysicalDevices();

	//Enumerate output devices (Eg: Monitors) and log them
	assert(GraphicsSystemInfo.EnumerateAndCacheOutputAdapters());
	LogAttachedOutputAdapters();
	
	//Swapchain creation (TODO: May not actually be required depending on application)?

	//Logical Device(s)

	//TODO: Other things. Eg: Queues, Memory management, task managers etc.
	
	//Done
	return true;
}

bool FLowLevelGraphics::Shutdown()
{
	FDebugLog::PrintInfoMessage("**********Shutdown LowLevelGraphics**********");

	//Shutdown in reverse order

	GraphicsSystemInfo.ClearCachedData();
	assert(GraphicsAPIStartup.OnShutdown());

	//Done
	return true;
}

void FLowLevelGraphics::LogPhysicalDevices()
{

}

void FLowLevelGraphics::LogAttachedOutputAdapters()
{
	
}
