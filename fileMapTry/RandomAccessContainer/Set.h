#pragma once

#include "FileDesc.h"
#include "StdRowDefs.h"
#include "Cache.h"
#include <string>
#include <vector>

using namespace std;

template<class T>
class __declspec(dllexport) Set
{
public:

	Set(LPCWSTR path, LPCWSTR name) 
	{
		StringCchCopy(this->path, MAX_PATH, path);
		StringCchCopy(this->name, MAX_PATH, name);
	
		header = SetUtils::LoadHeader(path, name);
		pHeader = header->GetHeader();

		files = SetUtils::LoadFiles(path, name);
		
		bufferCapacity = MAP_SIZE / sizeof(T);
		
		int tmp = BUF_SIZE / sizeof(T);
		tmp /= bufferCapacity;

		fileCapacity = tmp * bufferCapacity;

	}

	virtual ~Set() 
	{
		delete header;
	}

	T& operator[] (const int index)
	{
		return GetItem(index);
	}

	inline T& GetItem(const int index)
	{
		int fidx = index / fileCapacity;
		
		//index w pliku;
		int tidx = index % fileCapacity;

		//index bufora w secie (co cache)
		int bidx = index / bufferCapacity;
		
		//index bufora w pliku
		int bfidx = tidx / bufferCapacity;

		int didx = index % bufferCapacity;

		if(index == 139664)
			printf_s("--------------------------");

		LPVOID toRelease;
		T *pBuffer = (T*)buffers.GetBuffer(bidx, toRelease);

		if (toRelease != NULL) 
		{
			++rcount;
			FileDesc::ReleaseBuffer(toRelease);
			printf_s("buffer released: %d,   left: %d\n", rcount, buffers.Size());
		}
			
		if (pBuffer == NULL)
		{
			pBuffer = (T*)files[fidx].GetBuffer(bfidx);
			buffers.Add(bidx, pBuffer);
			printf_s("buffer cached: %d\n", buffers.Size());
		}

		if (pHeader->count < index + 1)
			pHeader->count = index + 1;

		if (pHeader->last < index)
			pHeader->last = index;

		if (pHeader->first > index)
			pHeader->first = index;

		return pBuffer[didx];
	}

	int Count()
	{
		return pHeader->count;
	}

private:
	TCHAR name[MAX_PATH];
	TCHAR path[MAX_PATH];

	SYSTEM_INFO sysInfo;

	int granularity;
	int bufferCapacity;
	int fileCapacity;

	FileDesc *header;
	vector<FileDesc> files;

	int rcount = 0;

	Header *pHeader;

	Cache buffers = Cache(4);
};

