#pragma once

#include "stdafx.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include "StdRowDefs.h"

#define BUF_SIZE 0x20000000
#define MAP_SIZE 0x20000000

class __declspec(dllexport) FileDesc
{
private:
	HANDLE hFile;
	HANDLE hMapFile;

	Header* pHeader;
	LPVOID pBuffer;
	LPVOID pData;

public:
	FileDesc(LPCWSTR path);

	virtual ~FileDesc();

	Header* GetHeader();
	LPVOID GetBuffer();
	void ReleaseBuffer();
};

