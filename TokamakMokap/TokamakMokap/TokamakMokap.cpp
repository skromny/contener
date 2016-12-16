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

		char* result = ReadHandler("customers", ";", "674", 0);
	}

	__declspec(dllexport) void RegisterCountHandler(vtab_CountProc handler)
	{
		CountHandler = handler;
		
		int result = CountHandler("customers");
	}
}



