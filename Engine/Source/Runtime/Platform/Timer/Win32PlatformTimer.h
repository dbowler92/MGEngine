/**
 * Win32 high performance general purpose timer. TotalTime() and DeltaTime()
 * return time in seconds. 
 */

#pragma once

#include "Core/CoreInclude.h"

class FWin32PlatformTimer
{
public:
	FWin32PlatformTimer();
	~FWin32PlatformTimer();

	float TotalTime() const;
	float DeltaTime() const;

	void Reset();
	void Start();
	void Stop();
	void Tick();
	
private:
	double mSecondsPerCount;
	double mDeltaTime;

	int64 mBaseTime;
	int64 mPausedTime;
	int64 mStopTime;
	int64 mPrevTime;
	int64 mCurrTime;

	bool mStopped;

private:
	FWin32PlatformTimer(FWin32PlatformTimer& Other) {};
	FWin32PlatformTimer& operator=(FWin32PlatformTimer& Other) {};
};