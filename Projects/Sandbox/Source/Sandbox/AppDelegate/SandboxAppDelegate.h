#pragma once

#include "Runtime/Core/CoreInclude.h"
#include "Runtime/Core/AppDelegate/IAppDelegate.h"

class FSandboxAppDelegate : public IAppDelegate
{
public:
	FSandboxAppDelegate();
	~FSandboxAppDelegate();

	bool OnPostEngineInit() override;
	bool OnPreEngineShutdown() override;
};
