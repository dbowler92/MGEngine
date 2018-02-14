//Win32PlatformTimer.h
//Created 26/07/16
//Created By Daniel Bowler
//
//Platform timer for Windows.

#pragma once

#include <HAL/PlatformTimer/IPlatformTimer.h>

class FWin32PlatformTimer : public IPlatformTimer
{
public:
	FWin32PlatformTimer();
	virtual ~FWin32PlatformTimer() = 0 {};

	float TotalTime() const override;  // in seconds
	float DeltaTime() const override; // in seconds

	void Reset() override; // Call before message loop.
	void Start() override; // Call when unpaused.
	void Stop()  override;  // Call when paused.
	void Tick()  override;  // Call every frame.

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};