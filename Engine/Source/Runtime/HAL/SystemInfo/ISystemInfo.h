//ISystemInfo.h
//Created 04/02/18
//Created By Daniel Bowler
//
//System info class will contain info on the users system - 
//Eg: CPU count, etc

#pragma once

#include <Core/CoreInclude.h>

class ISystemInfo
{
public:
	/*
	 * Gets the physical CPU core count (Not including hyperthreading)
	 */
	virtual uint32_t GetPhysicalCPUCoreCount() = 0;

	/*
	* Gets the logical CPU core count (Does including hyperthreading)
	*/
	virtual uint32_t GetLogicalCPUCoreCount() = 0;

	/*
	 * Hyperthreading (If Logical > Physical CPUs)?
	 */
	virtual bool IsHyperthreadedCPU() = 0;

	/*
	 * Gets the installed amount of RAM
	 */
	virtual uint64_t GetSystemRAMInBytes() = 0;
	virtual uint64_t GetSystemRAMInKB() = 0;
	virtual uint64_t GetSystemRAMInMB() = 0;
	virtual uint64_t GetSystemRAMInGB() = 0;

protected:
	/*
	* Hide constructors - only FEngine should create an instance of this.
	*/
	ISystemInfo() {};
	ISystemInfo(ISystemInfo& other);
	ISystemInfo& operator=(ISystemInfo& other);

	/*
	 * Virtual destructor - hidden
	 */
	virtual ~ISystemInfo() = 0 {};

	/*
	 *  Called during engine startup by FEngine
	 */
	virtual bool InitSystemInfo() = 0;

};
