#pragma once

#include <Core/CoreInclude.h>

#ifdef GRAPHICS_API_D3D12
#include "D3D12/D3D12PhysicalDevice.h"

GENERATE_PLATFORM_AGNOSTIC_CLASS(FPhysicalDevice, FD3D12PhysicalDevice);
#endif 