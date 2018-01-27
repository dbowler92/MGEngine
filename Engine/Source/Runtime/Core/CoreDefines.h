//CoreDefines.h
//Created 12/01/18
//Created By Daniel Bowler
//
//Defines and macros used within the engine / games

#pragma once

//Work out defines now that we have more info
//
//Set via via <Platform>Config.h
#ifdef _GRAPHICS_D3D12
#define GRAPHICS_D3D12
#define GRAPHICS_API_D3D12

#ifdef PLATFORM_WINDOWS
#define GRAPHICS_API_WINDOWS_D3D12
#define GRAPHICS_WINDOWS_D3D12
#endif

#endif

#ifdef _GRAPHICS_VULKAN
#define GRAPHICS_VULKAN
#define GRAPHICS_API_VULKAN

#ifdef PLATFORM_WINDOWS
#define GRAPHICS_WINDOWS_VULKAN
#define GRAPHICS_API_WINDOWS_VULKAN
#endif

#endif