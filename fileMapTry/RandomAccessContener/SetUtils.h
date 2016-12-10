
#pragma once

#include "stdafx.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <string>

using namespace std;

class __declspec(dllexport) SetUtils
{
public:
	SetUtils();
	virtual ~SetUtils();

	static void concatStrings(LPCWSTR s1, LPCWSTR s2, LPCWSTR sep, TCHAR *to);
	
	void LoadFiles(LPCWSTR path);
};

