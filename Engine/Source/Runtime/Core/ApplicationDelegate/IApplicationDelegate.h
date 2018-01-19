//IApplicationDelegate.h
//Created 13/01/18
//Created By Daniel Bowler
//
//Like iOS, each game/app will create an app delegate. Essentially, the
//way the engine communicates with the game. 

#pragma once

#include <Core/CoreInclude.h>

class IApplicationDelegate
{
public:
	/*
	* Virtual destructor
	*/
	virtual ~IApplicationDelegate() = 0 {};

	/*
	* Function called during startup (See MGEngineStartup). Called before
	* the engine is inited.
	*/
	virtual bool OnPreEngineInit() = 0;

	/*
	* Function called during startup (See MGEngineStartup). Called after
	* the engine is inited.
	*/
	virtual bool OnPostEngineInit() = 0;

	/*
	* Function called during shutdown - called before the engine is shutdown
	*/
	virtual bool OnShutdown() = 0;
};