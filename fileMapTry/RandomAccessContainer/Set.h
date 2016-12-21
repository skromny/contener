#pragma once

#include "FileDesc.h"
#include "StdRowDefs.h"
//#include "QuickSort.h"
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
		
		pBuffer = NULL;

		files = SetUtils::LoadFiles(path, name);

		pHeader = files[0].GetHeader();
		
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

		if ((this->index >= 0) && (this->index != idx)) 
		{
			files[this->index].ReleaseBuffer();
			pBuffer = NULL;
		}

		if (pBuffer == NULL)
		{
			pBuffer = (T*)files[index / maxCount].GetBuffer();
			this->index = idx;
		}
		
		if(pHeader->count < index + 1)
			pHeader->count = index + 1;

		if(pHeader->last < index)
			pHeader->last = index;

		if (pHeader->first > index)
			pHeader->first = index;

		return pBuffer[index % maxCount];
	}

	void SetItem(const int index, T& item)
	{
		int idx = index / maxCount;

		if ((this->index >= 0) && (this->index != idx))
		{
			for (int i = 0; i < files.size(); i++)
				files[i].ReleaseBuffer();

			pBuffer = NULL;
		}

		if (pBuffer == NULL)
		{
			pBuffer = (T*)files[index / maxCount].GetBuffer();
			this->index = idx;
		}


		if (pHeader->count < index + 1)
			pHeader->count = index + 1;

		if (pHeader->last < index)
			pHeader->last = index;

		if (pHeader->first > index)
			pHeader->first = index;

		memcpy(pBuffer[index % maxCount], item, sizeof(T));
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

	Header *pHeader;
	T* pBuffer;
};

