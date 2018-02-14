//IPlatformTimer.h
//Created 04/02/18
//Created By Daniel Bowler
//
//Base class for platform timers. 

#pragma once

#include <Core/CoreInclude.h>

class IPlatformTimer
{
public:
	virtual ~IPlatformTimer() = 0 {};

	virtual float TotalTime() const = 0;  // in seconds
	virtual float DeltaTime()const = 0;   // in seconds

	virtual void Reset() = 0; 
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Tick() = 0;
};