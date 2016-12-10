#pragma once

#include "stdafx.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

class __declspec(dllexport) FileDesc
{
private:

public:
	FileDesc(LPCWSTR path);
	~FileDesc();
};

