#pragma once

typedef int vtab_CountProc(char*);
typedef char* vtab_GetExtRowProc(char*, char*, char*, int);

typedef int pm_TestProc(int count);

extern "C"
{
	__declspec(dllexport) void RegisterReadHandler(vtab_GetExtRowProc);
	__declspec(dllexport) void RegisterCountHandler(vtab_CountProc);

	__declspec(dllexport) void RegisterTestHandler(pm_TestProc);
	__declspec(dllexport) int Run1TestXTimes(int);
	__declspec(dllexport) int RunXTestsOnce(int);
}

vtab_CountProc* CountHandler;
vtab_GetExtRowProc* ReadHandler;
pm_TestProc* TestProcX;


