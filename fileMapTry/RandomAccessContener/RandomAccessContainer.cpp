// RandomAccessContainer.cpp : Defines the exported functions for the DLL application.
//

/*
	Context - klasa zawierajaca sety (definicje plików)
	kontekst zawiera mape setow
	
	set to definicja opsujaca plik i zawierajca w sobie wszystko co potrzebne do mapowania go w pamiêæ

*/

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include "SetUtils.h"
#include "rac.h"

__declspec(dllexport) int __cdecl vtab_CountProc(char *_NAME)
{
	wprintf(L"vtab_CountProc\n");
	Context& c = CONTEXTS[0];

	Set<TinyRow15Cols>& set = c.get<TinyRow15Cols>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));

	return set.Count();
}

__declspec(dllexport) char* __cdecl vtab_GetColValue(char *_NAME, int ColNr, int RowKey)
{
	wprintf(L"vtab_GetColValue\n");

	Context& c = CONTEXTS[0];

	Set<TinyRow15Cols>& set = c.get<TinyRow15Cols>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));

	return set[RowKey].column[ColNr];
}

__declspec(dllexport) void __cdecl vtab_WriteColValue(char *_NAME, char *value, int ColNr, int RowKey)
{
	wprintf(L"vtab_WriteColValue\n");
	Context& c = CONTEXTS[0];

	Set<TinyRow15Cols>& set = c.get<TinyRow15Cols>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));
	strcpy_s(set[RowKey].column[ColNr], value);
}

__declspec(dllexport) char* __cdecl vtab_GetSortedValue(char *_NAME, int ColNr, int Pos, int &Key)
{
	wprintf(L"vtab_GetSortedValue\n");

	return NULL;
}
