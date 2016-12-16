
#pragma once

#include "stdafx.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <vector>
#include <string>

#include "FileDesc.h"

using namespace std;

class __declspec(dllexport) SetUtils
{
public:
	SetUtils();
	virtual ~SetUtils();

	static wchar_t *ConvertCharArrayToLPCWSTR(const char* charArray);

	static void ConcatStrings(LPCWSTR s1, LPCWSTR s2, LPCWSTR sep, TCHAR *to);
	
	static vector<FileDesc> LoadFiles(LPCWSTR path, LPCWSTR name);
};

