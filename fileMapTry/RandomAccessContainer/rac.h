#pragma once

#include "Context.h"

using namespace std;

extern vector<Context> CONTEXTS;


__declspec(dllexport) int __cdecl vtab_CountProc(char *_NAME);
__declspec(dllexport) char* __cdecl vtab_GetColValue(char *_NAME, int ColNr, int RowKey);
__declspec(dllexport) void __cdecl vtab_WriteColValue(char *_NAME, char *value, int ColNr, int RowKey);

__declspec(dllexport) void __cdecl vtab_Set4KRow(char *_NAME, char* value, int RowKey);
__declspec(dllexport) void __cdecl vtab_Set8KRow(char *_NAME, char* value, int RowKey);

__declspec(dllexport) char* __cdecl vtab_Get4KRow(char *_NAME, int RowKey);
__declspec(dllexport) char* __cdecl vtab_Get8KRow(char *_NAME, int RowKey);


//w przygotowaniu
__declspec(dllexport) char* __cdecl vtab_GetSortedValue(char *_NAME, int ColNr, int Pos, int &Key);
__declspec(dllexport) char* __cdecl vtab_GetEqualPosListProc(char *_NAME, int ColNr, char *_EqualStr);



