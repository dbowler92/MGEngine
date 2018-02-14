//D3D12Config.h
//Created 10/01/18
//Created By Daniel Bowler
//
//D3D12 settings

#pragma once

//Define the graphics API we are using
#define _GRAPHICS_D3D12

//Libs
#pragma comment(lib, "dxgi.lib")

#ifdef CONFIGURATION_DEBUG
//...
#endif

//
//DXGI
//
//IDXGIFactory version: 0 - 4 inclusive.
#define IDXGI_FACTORY_VERSION 4