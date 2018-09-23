/**
 * Represents a single OS created window we will be rendering in to.
 */

#pragma once

#include "Core/CoreInclude.h"

class FWin32Window
{
public:
	FWin32Window();
	~FWin32Window();

	bool Create(HINSTANCE HInstance, LPCWSTR ClassName, const uint32 Width, const uint32 Height, LPCWSTR WindowTitle);
	void Destroy();
	void Show();

public: 
	bool IsCreated() { return bCreated; };

	uint32 GetWindowWidth() const { return WindowWidth; };
	uint32 GetWindowHeight() const { return WindowHeight; };

private:
	HWND WindowHandle;

	uint32 WindowWidth;
	uint32 WindowHeight;

	bool bCreated;

private:
	FWin32Window(FWin32Window& Other) {};
	FWin32Window& operator=(FWin32Window& Other) {};
};