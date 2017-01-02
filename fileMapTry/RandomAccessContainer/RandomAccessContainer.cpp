// RandomAccessContainer.cpp : Defines the exported functions for the DLL application.
//

/*
	Context - klasa zawierajaca sety (definicje plików)
	W windows jest to jeden konkretny folder
	kontekst zawiera mape setow 
	
	set to definicja opsujaca zbior danych oraz pliki przechowujace te dane...
	zawiera w sobie wszystko co potrzebne do mapowania plików  go w pamiêæ

*/

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include "SetUtils.h"
#include "rac.h"

#include "QuickSort.h"

extern "C"
{
	vector<Context> CONTEXTS;

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

	__declspec(dllexport) void __cdecl vtab_Set4KRow(char *_NAME, char* value, int RowKey)
	{
		wprintf(L"vtab_Set4KRow\n");
		Context& c = CONTEXTS[0];

		Set<RawData4K>& set = c.get<RawData4K>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));
		memcpy_s(&set[RowKey], sizeof(RawData4K), value, sizeof(RawData4K));
	}

	__declspec(dllexport) void __cdecl vtab_Set8KRow(char *_NAME, char* value, int RowKey)
	{
		wprintf(L"vtab_Set4KRow\n");
		Context& c = CONTEXTS[0];

		Set<RawData8K>& set = c.get<RawData8K>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));
		memcpy_s(&set[RowKey], sizeof(RawData8K), value, sizeof(RawData4K));
	}

	__declspec(dllexport) char* __cdecl vtab_Get4KRow(char *_NAME, int RowKey)
	{
		//wprintf(L"vtab_Get4KRow\n");

		Context& c = CONTEXTS[0];

		Set<RawData4K>& set = c.get<RawData4K>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));

		return (char*)&set[RowKey];
	}

	__declspec(dllexport) char* __cdecl vtab_Get8KRow(char *_NAME, int RowKey)
	{
		wprintf(L"vtab_Get8KRow\n");

		Context& c = CONTEXTS[0];

		Set<RawData8K>& set = c.get<RawData8K>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));

		return (char*)&set[RowKey];
	}

	__declspec(dllexport) void __cdecl vtab_WriteColValue(char *_NAME, char *value, int ColNr, int RowKey)
	{
		//wprintf(L"vtab_WriteColValue\n");
		Context& c = CONTEXTS[0];


		//Za³ozenie ¿e kazdy wiersz jest zdefiniowany w strukturze TinyRow15Cols
		Set<TinyRow15Cols>& set = c.get<TinyRow15Cols>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));
		strcpy_s(set[RowKey].column[ColNr], value);
	}

	__declspec(dllexport) char* __cdecl vtab_GetSortedValue(char *_NAME, int ColNr, int Pos, int &Key)
	{
		wprintf(L"vtab_GetSortedValue\n");
		Context& c = CONTEXTS[0];

		Set<TinyRow15Cols>& set = c.get<TinyRow15Cols>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));
		
		TinyRow15Cols& r = QuickSort::DoSort<TinyRow15Cols>(set, ColNr, Pos, Key);

		return r.column[ColNr];
	}

	__declspec(dllexport) char* __cdecl vtab_GetEqualPosListProc(char *_NAME, int ColNr, char *_EqualStr)
	{
		wprintf(L"vtab_GetEqualPosListProc\n");
		Context& c = CONTEXTS[0];

		Set<TinyRow15Cols>& set = c.get<TinyRow15Cols>(SetUtils::ConvertCharArrayToLPCWSTR(_NAME));

		return QuickSort::Find<TinyRow15Cols>(set, ColNr, _EqualStr);
	}
}
