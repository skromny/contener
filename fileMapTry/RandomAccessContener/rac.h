#pragma once

#include "Context.h"

using namespace std;

extern vector<Context> CONTEXTS;


__declspec(dllexport) int __cdecl vtab_CountProc(char *_NAME);
__declspec(dllexport) char* __cdecl vtab_GetColValue(char *_NAME, int ColNr, int RowKey);
__declspec(dllexport) void __cdecl vtab_WriteColValue(char *_NAME, char *value, int ColNr, int RowKey);
__declspec(dllexport) char* __cdecl vtab_GetSortedValue(char *_NAME, int ColNr, int Pos, int &Key);




