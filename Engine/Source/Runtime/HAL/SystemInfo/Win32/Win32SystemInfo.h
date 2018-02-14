//Win32SystemInfo.h
//Created 04/02/18
//Created By Daniel Bowler
//
//System info class for windows will contain info on the users system - 
//Eg: CPU count, etc.
//
//On windows, we can't assume anything. Thus, we need to poll this info from
//the OS. 

#pragma once

#include <HAL/SystemInfo/ISystemInfo.h>

#include <Windows.h>

class FWin32SystemInfo : public ISystemInfo
{
	//FEngine inits and manages this
	friend class FEngine;

public:
	/*
	* Gets the physical CPU core count (Not including hyperthreading)
	*/
	virtual uint32_t GetPhysicalCPUCoreCount() override { return PhysicalCPUCount; };

	/*
	* Gets the logical CPU core count (Does including hyperthreading)
	*/
	virtual uint32_t GetLogicalCPUCoreCount() override { return LogicalCPUCount; };

	/*
	* Hyperthreading?
	*/
	bool IsHyperthreadedCPU() override { return LogicalCPUCount > PhysicalCPUCount; };

	/*
	* Gets the installed amount of RAM
	*/
	virtual uint64_t GetSystemRAMInBytes() override { return InstalledRAMInBytes; };
	virtual uint64_t GetSystemRAMInKB() override { return InstalledRAMInKB; };
	virtual uint64_t GetSystemRAMInMB() override { return InstalledRAMInMB; };
	virtual uint64_t GetSystemRAMInGB() override { return InstalledRAMInGB; };
	
protected:
	/*
	* Virtual destructor - hidden
	*/
	virtual ~FWin32SystemInfo() = 0 {};

	/*
	*  Called during engine startup by FEngine
	*/
	bool InitSystemInfo() override;

private:
	/*
	 * Physical and logical CPU count
	 */
	uint32_t PhysicalCPUCount = 0;
	uint32_t LogicalCPUCount = 0;

	/*
	 * System RAM installed
	 */
	uint64_t InstalledRAMInBytes = 0;
	uint64_t InstalledRAMInKB = 0;
	uint64_t InstalledRAMInMB = 0;
	uint64_t InstalledRAMInGB = 0;
};