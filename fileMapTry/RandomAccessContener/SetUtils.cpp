
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include "SetUtils.h"

using namespace std;

SetUtils::SetUtils()
{
}


SetUtils::~SetUtils()
{
}

void SetUtils::concatStrings(LPCWSTR s1, LPCWSTR s2, LPCWSTR sep, TCHAR *to) {

	StringCchCopy(to, MAX_PATH, s1);
	StringCchCat(to, MAX_PATH, sep);
	StringCchCat(to, MAX_PATH, s2);
}

void SetUtils::LoadFiles(LPCWSTR path) {
	HANDLE hFind;
	WIN32_FIND_DATA data;
	TCHAR szDir[MAX_PATH];

	StringCchCopy(szDir, MAX_PATH, path);
	StringCchCat(szDir, MAX_PATH, TEXT("\\"));

	//int len;
	//int slength = (int)key.length() + 1;
	//len = MultiByteToWideChar(CP_ACP, 0, key.c_str(), slength, 0, 0);
	//wchar_t* buf = new wchar_t[len];
	//MultiByteToWideChar(CP_ACP, 0, key.c_str(), slength, buf, len);
	//std::wstring r(buf);
	//delete[] buf;

	//StringCchCat(szDir, MAX_PATH, name);
	
	StringCchCat(szDir, MAX_PATH, TEXT("*.mnc"));
	hFind = FindFirstFile(szDir, &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			//printf("%s\n", data.cFileName);
			_tprintf(TEXT("  %s  \n"), data.cFileName);
			
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
}

