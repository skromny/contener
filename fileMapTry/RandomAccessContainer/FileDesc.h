#pragma once

#include "stdafx.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include "StdRowDefs.h"

#define BUF_SIZE 0x80000000
#define MAP_SIZE 0x08000000
#define BUF_CAPS 0x10

class __declspec(dllexport) FileDesc
{
private:

	HANDLE hFile;
	HANDLE hMapFile;

public:
	FileDesc(LPCWSTR path);
	FileDesc(LPCWSTR path, bool header);
	virtual ~FileDesc();

	DWORD granularity;

	Header* GetHeader();
	LPVOID GetBuffer(DWORD offset);
	static void ReleaseBuffer(LPVOID pBuffer);
};

