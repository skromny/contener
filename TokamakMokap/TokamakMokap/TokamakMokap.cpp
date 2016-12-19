// TokamakMokap.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <iostream>
#include "TokamakMokap.h"

extern "C"
{
	__declspec(dllexport) void RegisterReadHandler(vtab_GetExtRowProc handler)
	{
		ReadHandler = handler;
	}

	__declspec(dllexport) void RegisterCountHandler(vtab_CountProc handler)
	{
		CountHandler = handler;
	}

	__declspec(dllexport) void RegisterTestHandler(pm_TestProc handler)
	{
		TestProcX = handler;
	}

	__declspec(dllexport) int Run1TestXTimes(int count)
	{
		return TestProcX(count);
	}

	__declspec(dllexport) int RunXTestsOnce(int count)
	{
		int sum = 0;
		for (int i = 0; i < count; i++) {
			if (TestProcX(1) == 0)
				sum += 1;
			else
				sum -= 1;
		}

		return sum;
	}

}



