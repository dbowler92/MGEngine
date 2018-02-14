#include "Win32SystemInfo.h"

#include <assert.h>
#include <malloc.h> // Should use platform independent malloc when it's done...

// Helper function to count set bits in the processor mask.
DWORD CountSetBits(ULONG_PTR bitMask)
{
	DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
	DWORD bitSetCount = 0;
	ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
	DWORD i;

	for (i = 0; i <= LSHIFT; ++i)
	{
		bitSetCount += ((bitMask & bitTest) ? 1 : 0);
		bitTest /= 2;
	}

	return bitSetCount;
}

bool FWin32SystemInfo::InitSystemInfo()
{
	PhysicalCPUCount = 0;
	LogicalCPUCount = 0;

	typedef BOOL(WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);
	
	//CPU state.
	LPFN_GLPI glpi = (LPFN_GLPI)GetProcAddress(GetModuleHandle(TEXT("kernel32")),
		"GetLogicalProcessorInformation");
	assert(glpi != nullptr);
		
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION CPUInfoBuffer = nullptr;
	DWORD CPUInfoBufferLength = 0;

	//Size of the buffer we need to malloc...
	DWORD Result = glpi(CPUInfoBuffer, &CPUInfoBufferLength);

	//If failed - we may need to alloc the buffer
	if (Result == FALSE)
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			CPUInfoBuffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(CPUInfoBufferLength);
			if (CPUInfoBuffer == nullptr)
			{
				//TODO: Print a message of some sort...
				return false;
			}
			else
			{
				//Get info again.
				Result = glpi(CPUInfoBuffer, &CPUInfoBufferLength);
				if (Result == FALSE)
				{
					//TODO: Print a message of some sort...
					free(CPUInfoBuffer);
					return false;
				}

				//Get the number of cores... TODO: Other useful info should be cached!
				PSYSTEM_LOGICAL_PROCESSOR_INFORMATION Ptr = CPUInfoBuffer;
				DWORD ByteOffset = 0;

				while (ByteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= CPUInfoBufferLength)
				{
					switch (Ptr->Relationship)
					{
						case RelationProcessorCore:
						{
							PhysicalCPUCount++;

							//A hyperthreaded core supplies more than one logical processor
							LogicalCPUCount += CountSetBits(Ptr->ProcessorMask);
							break;
						}
					}

					ByteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
					Ptr++;
				}
			}
		}
		else
		{
			//TODO: Print a message of some sort...
			return false;
		}
	}

	if(CPUInfoBuffer != nullptr)
	{
		free(CPUInfoBuffer);
	}

	//RAM
	ULONGLONG RamKB = 0;
	if (GetPhysicallyInstalledSystemMemory(&RamKB) == FALSE)
	{
		//TODO: Print a message of some sort...
		return false;
	}

	InstalledRAMInKB = (uint64_t)RamKB;

	InstalledRAMInBytes = InstalledRAMInKB * 1024;
	InstalledRAMInMB = InstalledRAMInKB / 1024;
	InstalledRAMInGB = InstalledRAMInMB / 1024;

	return true;
}