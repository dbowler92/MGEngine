#include "SandboxAppDelegate.h"

#include <Debugging/Log/DebugLog.h>

bool FSandboxAppDelegate::OnPreEngineInit()
{
	return true;
}

bool FSandboxAppDelegate::OnPostEngineInit()
{
	return true;
}

bool FSandboxAppDelegate::OnShutdown()
{
	return true;
}