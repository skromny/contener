
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

wchar_t* SetUtils::ConvertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void SetUtils::ConcatStrings(LPCWSTR s1, LPCWSTR s2, LPCWSTR sep, TCHAR *to) {

	StringCchCopy(to, MAX_PATH, s1);
	StringCchCat(to, MAX_PATH, sep);
	StringCchCat(to, MAX_PATH, s2);

}

FileDesc* SetUtils::LoadHeader(LPCWSTR path, LPCWSTR name)
{
	HANDLE hFind;
	WIN32_FIND_DATA data;
	TCHAR szDir[MAX_PATH];

	StringCchCopy(szDir, MAX_PATH, path);
	StringCchCat(szDir, MAX_PATH, TEXT("\\"));
	StringCchCat(szDir, MAX_PATH, name);

	StringCchCat(szDir, MAX_PATH, TEXT(".mnh"));
	hFind = FindFirstFile(szDir, &data);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);

		TCHAR szFullName[MAX_PATH];
		ConcatStrings(path, data.cFileName, TEXT("\\"), szFullName);

		return new FileDesc(szFullName, true);
	}
	else
	{
		TCHAR szFullName[MAX_PATH];
		swprintf_s(szFullName, TEXT("%s\\%s.mnh"), path, name);
		HANDLE file = CreateFile(szFullName,    // name of the file
			GENERIC_WRITE, // open for writing
			0,             // sharing mode, none in this case
			0,             // use default security descriptor
			CREATE_ALWAYS, // overwrite if exists
			FILE_ATTRIBUTE_NORMAL,
			0);

		if (file != INVALID_HANDLE_VALUE)
		{
			CloseHandle(file);

			return new FileDesc(szFullName, true);
		}
	}
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
			ConcatStrings(path, data.cFileName, TEXT("\\"), szFullName);
			result.push_back(FileDesc(szFullName));

		} while (FindNextFile(hFind, &data));

		FindClose(hFind);

	}
	else
	{
		TCHAR szFullName[MAX_PATH];
		for (int i = 0; i < 8; i++)
		{
			swprintf_s(szFullName, TEXT("%s\\%s%02d.mnc"), path, name, i + 1);
			HANDLE file = CreateFile(szFullName,    // name of the file
				GENERIC_WRITE, // open for writing
				0,             // sharing mode, none in this case
				0,             // use default security descriptor
				CREATE_ALWAYS, // overwrite if exists
				FILE_ATTRIBUTE_NORMAL,
				0);

			if (file != INVALID_HANDLE_VALUE)
			{
				CloseHandle(file);

				result.push_back(FileDesc(szFullName));
			}
		}
	}

	return result;
}

DWORD SetUtils::GetPageSize()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	return sysInfo.dwPageSize;
}

DWORD SetUtils::GetGranularity()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	return sysInfo.dwAllocationGranularity;
}




