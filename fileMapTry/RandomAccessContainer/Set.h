#pragma once

#include "FileDesc.h"
#include "StdRowDefs.h"
#include "QuickSort.h"
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
		maxCount = (BUF_SIZE - sizeof(Header)) / sizeof(T);
	}
	virtual ~Set() {
	}

	T& operator[] (const int index)
	{
		return GetItem(index);
	}

	inline T& GetItem(const int index)
	{
		int idx = index / maxCount;

		if ((this->index > 0) && (this->index != idx)) 
		{
			files[this->index].ReleaseBuffer();
		}

		Header *header = files[0].GetHeader();
		T* buffer = (T*)files[index / maxCount].GetBuffer();

		this->index = idx;
		
		if(header->count < index + 1)
			header->count = index + 1;

		if(header->last < index)
			header->last = index;

		if (header->first > index)
			header->first = index;

		return buffer[index % maxCount];
	}

	void SetItem(const int index, T& item)
	{
		if ((this->index > 0) && (this->index != idx))
		{
			files[this->index].ReleaseBuffer();
		}

		Header *header = files[0].GetHeader();
		T* buffer = (T*)files[index / maxCount].GetBuffer();

		if (header->count < index + 1)
			header->count = index + 1;

		if (header->last < index)
			header->last = index;

		if (header->first > index)
			header->first = index;

		memcpy(buffer[index % maxCount], item, sizeof(T));
	}

	int Count()
	{
		Header *header = files[0].GetHeader();
		return header->count;
	}

	void Sort() {
		
	}

private:
	TCHAR name[MAX_PATH];
	TCHAR path[MAX_PATH];

	int maxCount;

	vector<FileDesc> files;
	int index = -1;
};

