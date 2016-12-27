#pragma once

#include <windows.h>
#include <time.h>

class __declspec(dllexport) CacheItem
{
public:
	
	CacheItem();
	CacheItem(LPVOID data);
	~CacheItem();

	LPVOID GetData();
	LONG GetLastTouch();

	void SetData(LPVOID data);

private:
	DWORD lastTouch;

	LPVOID pData;
};

