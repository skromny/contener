
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <string>
#include <vector>

#include "FileDesc.h"

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

vector<FileDesc> SetUtils::LoadFiles(LPCWSTR path, LPCWSTR name)
{
	HANDLE hFind;
	WIN32_FIND_DATA data;
	TCHAR szDir[MAX_PATH];
	vector<FileDesc> result;

	StringCchCopy(szDir, MAX_PATH, path);
	StringCchCat(szDir, MAX_PATH, TEXT("\\"));
	StringCchCat(szDir, MAX_PATH, name);
	
	StringCchCat(szDir, MAX_PATH, TEXT("*.mnc"));
	hFind = FindFirstFile(szDir, &data);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do {

			_tprintf(TEXT("  %s  \n"), data.cFileName);
			
			TCHAR szFullName[MAX_PATH];
			concatStrings(path, data.cFileName, TEXT("\\"), szFullName);
			result.push_back(FileDesc(szFullName));

		} while (FindNextFile(hFind, &data));
	
		FindClose(hFind);

	}

	return result;
}

