#pragma once

#include "FileDesc.h"
#include <string>
#include <vector>

using namespace std;

template<class T>
class __declspec(dllexport) Set
{
public:

	Set(LPCWSTR path, LPCWSTR name) {
		StringCchCopy(this->path, MAX_PATH, path);
		StringCchCopy(this->name, MAX_PATH, name);
		
		files = SetUtils::LoadFiles(path, name);

		//137447
		maxCount = BUF_SIZE / sizeof(T);
	}
	virtual ~Set() {
	}

	T& operator[] (const int index)
	{
		return GetItem(index);
	}

	inline T& GetItem(const int index)
	{
		T* buffer = (T*)files[index / maxCount].GetBuffer();

		return buffer[index % maxCount];
	}

	void SetItem(const int index, T& item)
	{
		T* buffer = (T*)files[index / maxCount].GetBuffer();

		memcpy(buffer[index % maxCount], item, sizeof(T));
	}

private:
	TCHAR name[MAX_PATH];
	TCHAR path[MAX_PATH];

	int maxCount;

	vector<FileDesc> files;
};

