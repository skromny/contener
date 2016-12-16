#pragma once

typedef int vtab_CountProc(char*);
typedef char* vtab_GetExtRowProc(char*, char*, char*, int);

extern "C"
{
	__declspec(dllexport) void RegisterCountHandler(vtab_CountProc);
	__declspec(dllexport) void RegisterInfoFunc(vtab_GetExtRowProc);
}

vtab_CountProc* CountHandler;
vtab_GetExtRowProc* ReadHandler;



