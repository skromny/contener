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

		//for (vector<FileDesc>::iterator it = files.begin(); it != files.end(); ++it)
		//	pBuffers.push_back((T*)(*it).GetBuffer());

		maxCount = BUF_SIZE / sizeof(T);
	}
	virtual ~Set() {
	}

	T& operator[] (const int index)
	{
		int i = index / maxCount;

		T* buffer = (T*)files[i];

		return buffer[index % maxCount];
	}

private:
	TCHAR name[MAX_PATH];
	TCHAR path[MAX_PATH];

	int maxCount;

	vector<FileDesc> files;
	//vector<T*> pBuffers;
};

