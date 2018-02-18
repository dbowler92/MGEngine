#include "LowLevelGraphics.h"

#include <string>

#include <Debugging/Log/DebugLog.h>
#include <HAL/Platform/Platform.h>

#include <Graphics/XPGL/PhysicalDevice/PhysicalDevice.h>
#include <Graphics/XPGL/AdapterOutput/AdapterOutput.h>

bool FLowLevelGraphics::Start(FPlatform* PlatformApp)
{
	FDebugLog::PrintInfoMessage("**********Starting LowLevelGraphics**********");

	assert(PlatformApp != nullptr); 

	//API Startup - Eg: Vulkan loader or initing DXGI factory
	assert(GraphicsAPIStartup.Start());

	//Enumerate physical devices and log them
	assert(GraphicsSystemInfo.EnumerateAndCachePhysicalDevices());
	LogPhysicalDevices(true);

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

void FLowLevelGraphics::LogPhysicalDevices(bool bLogOutputDevices)
{
	unsigned PhysicalDeviceCount = GraphicsSystemInfo.GetPhysicalDeviceCount();
	FPhysicalDevice* PhysicalDevices = GraphicsSystemInfo.GetPhysicalDevices();

	if (PhysicalDeviceCount > 0 && PhysicalDevices != nullptr)
	{
		FDebugLog::PrintInfoMessage("Enumerating Attached Physical Devices...");
		
		for (unsigned i = 0; i < PhysicalDeviceCount; i++)
		{
			std::string ds = "Physical Device ";
			ds += std::to_string(i);
			ds += ": ";
			ds += PhysicalDevices[i].GetPhysicalDeviceName();
			ds += " - Dedicated memory (Bytes): ";
			ds += std::to_string(PhysicalDevices[i].GetDeviceDedicatedVideoMemoryInBytes());
			ds += " | System memory (Bytes): ";
			ds += std::to_string(PhysicalDevices[i].GetDeviceDedicatedSystemMemoryInBytes());
			
			FDebugLog::PrintInfoMessage(ds.c_str());

			if (bLogOutputDevices)
			{
				if (PhysicalDevices[i].GetAdapterOutputCount() > 0)
				{
					FAdapterOutput* AdapterOutputs = PhysicalDevices[i].GetAdapterOutputs();
					for (unsigned j = 0; j < PhysicalDevices[i].GetAdapterOutputCount(); j++)
					{
						std::string os = "Adapter Output Device: ";
						os += std::to_string(j);
						os += ": ";
						os += AdapterOutputs[j].GetOutputDeviceName();

						FDebugLog::PrintInfoMessage(os.c_str());
					}
				}
			}
		}
	}
}