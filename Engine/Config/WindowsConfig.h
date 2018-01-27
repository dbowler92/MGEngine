//WindowsConfig.h
//Created 18/04/17
//Created By Daniel Bowler
//
//Some config stuff for Windows

#pragma once

//Win32 includes
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

//Win32 lean and mean!
#define WIN32_LEAN_AND_MEAN

//C-String representing the API being used
#define OS_PLATFORM_API_STRING "Windows"

//Graphics API to use? D3D12 or Vulkan.
#define _GRAPHICS_API_ID _D3D12_API_ID
//#define _GRAPHICS_API_ID _VULKAN_API_ID

//Include specific graphics API config
#if _GRAPHICS_API_ID == _D3D12_API_ID
#include <Config/D3D12Config.h>
#elif _GRAPHICS_API_ID == _VULKAN_API_ID
#include <Config/VulkanConfig.h>
#endif

//Undefines 
#undef _GRAPHICS_API_ID