#include "SandboxAppDelegate.h"

FSandboxAppDelegate::FSandboxAppDelegate()
{}

FSandboxAppDelegate::~FSandboxAppDelegate() 
{}

bool FSandboxAppDelegate::OnPostEngineInit()
{
	return true;
}

bool FSandboxAppDelegate::OnPreEngineShutdown()
{
	return true;
}