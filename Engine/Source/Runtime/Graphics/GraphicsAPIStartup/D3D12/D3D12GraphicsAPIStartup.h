//D3D12GraphicsAPIStartup.h
//Created 13/02/18
//Created By Daniel Bowler
// 
//Inits DXGIFactory

#pragma once

#include <Graphics/GraphicsAPIStartup/IGraphicsAPIStartup.h>

class FD3D12GraphicsAPIStartup : public IGraphicsAPIStartup
{
	friend class FLowLevelGraphics;

protected:
	/*
	* Virtual Destructor
	*/
	virtual ~FD3D12GraphicsAPIStartup() = 0 {};

	/*
	* Startup function - Called at the top of FLowLevelGraphics::Start()
	*/
	bool Start() override;

	/*
	* Called when the engine is shutdown. Again, by FLowLevelGraphics::Shutdown()
	*/
	bool OnShutdown() override;

};