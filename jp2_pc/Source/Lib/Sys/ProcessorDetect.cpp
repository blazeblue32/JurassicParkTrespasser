/***********************************************************************************************
 *
 * Copyright © DreamWorks Interactive. 1996
 *
 * Contents:
 * Application side of the processor detection system.
 *
 * Bugs:
 *
 * To do:
 * Have some method of locating the DLL if it is no where we expected it to be.
 *
 ***********************************************************************************************
 *
 * $Log:: /JP2_PC/Source/Lib/Sys/ProcessorDetect.cpp                                           $
 * 
 * 3     7/09/98 1:11a Pkeet
 * Added the 'u4GetCPUSpeed' function.
 * 
 * 2     7/08/97 5:16p Rwyatt
 * Now loads the DLL from the current Dir
 * 
 * 1     7/08/97 4:47p Rwyatt
 * Class wrapper for the processor detection DLL
 * 
 **********************************************************************************************/


//*********************************************************************************************
//
#include "Common.hpp"
#include "Lib/W95/WinInclude.hpp"
#include "ProcessorDetect.hpp"



//*********************************************************************************************
// Class Implementation
//*********************************************************************************************

//*********************************************************************************************
// Constructor loads the DLL, does the stuff and then unloads it. We do not keep the DLL
// around until the destructor is called. This is because the DLL only returns a 100 byte
// struture which can be copied into some local storage.
//
// If the DLL proves to be a problem then meybe we could move the DLL code into this class
// but that would mean keeping it around for the whole game which is pointless.
//
//**********************************************************************************************
// Completely bypass the processor.dll and cpu check entirely
//
//
CCPUDetect::CCPUDetect()
{
	memset(&cpuCPUInfo, 0, sizeof(cpuCPUInfo));

	bLoaded = true;

	// Pretend we detected a modern PentiumPro-compatible CPU.
	cpuCPUInfo.cpufamProcessorFamily = (ECPUFamily)6;

	cpuCPUInfo.u4CPUFlags =
		CPU_CPUID |
		CPU_MMX |
		CPU_PENTIUM |
		CPU_PENTIUMPRO;

	// Arbitrary modern CPU speed.
	cpuCPUInfo.u4CPUSpeed = 3000;
}



//*********************************************************************************************
//
CCPUDetect::~CCPUDetect()
{
	// do nothing at the moment
}


//*********************************************************************************************
uint32 u4GetCPUSpeed()
{
	CCPUDetect det;

	// If the cpu is not reliably detected, return 0.
	if (!det.bLoaded)
		return 0;

	// Return the detected speed.
	return det.cpuCPUInfo.u4CPUSpeed;
}
