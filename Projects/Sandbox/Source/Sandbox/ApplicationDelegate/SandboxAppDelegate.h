//SandboxAppDelegate.h
//Created 13/01/18
//Created By Daniel Bowler
//
//App delegate for this app - Essentially, the way the engine
//communicates with the app

#pragma once

#include <Runtime/Core/ApplicationDelegate/IApplicationDelegate.h>

class FSandboxAppDelegate : public IApplicationDelegate
{
public:
	/*
	 * Destructor
	 */
	~FSandboxAppDelegate() {};

	/*
	 * IApplicationDelegate interface
	 */ 
	bool OnPreEngineInit() override;
	bool OnPostEngineInit() override;
	bool OnShutdown() override;

};
