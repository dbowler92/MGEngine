#pragma once

#include <Core/CoreInclude.h>

#ifdef GRAPHICS_API_D3D12
#include "D3D12/D3D12GraphicsAPIStartup.h"

GENERATE_PLATFORM_AGNOSTIC_CLASS(FGraphicsAPIStartup, FD3D12GraphicsAPIStartup)
#endif 