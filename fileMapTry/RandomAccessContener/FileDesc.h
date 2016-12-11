#pragma once

#include "stdafx.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

#define BUF_SIZE 0x80000000
#define MAP_SIZE 0x80000000

class __declspec(dllexport) FileDesc
{
private:
	HANDLE hFile;
	HANDLE hMapFile;

	LPVOID pBuffer;

public:
	FileDesc(LPCWSTR path);

	virtual ~FileDesc();

	LPVOID GetBuffer();
};

