// RandomAccessContener.cpp : Defines the exported functions for the DLL application.
//

/*
	Context - klasa zawierajaca sety (definicje plików)
	kontekst zawiera mape setow
	
	set to definicja opsujaca plik i zawierajca w sobie wszystko co potrzebne do mapowania go w pamiêæ

*/

#include "stdafx.h"

#include <cstdio>
#include "rac.h"

__declspec(dllexport) void __cdecl Function1(void) 
{
	Context c = CONTEXTS[0];
	wprintf(L"function1");
}

__declspec(dllexport) void __cdecl Function2(void)
{
	wprintf(L"function2");
}
