
#include "FileDesc.h"

FileDesc::FileDesc(LPCWSTR path)
{
	this->hFile = CreateFile(path
		, GENERIC_READ | GENERIC_WRITE
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_ALWAYS
		, FILE_ATTRIBUTE_NORMAL
		, NULL
	);

	this->hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, BUF_SIZE, NULL);
	this->pHeader = NULL;
	
	this->pBuffer = NULL;
}

FileDesc::~FileDesc() 
{

}

Header* FileDesc::GetHeader()
{
	if (this->pHeader == NULL) 
	{
		this->pHeader = (Header*)MapViewOfFile(hMapFile, // handle to map object
			FILE_MAP_ALL_ACCESS,  // read/write permission
			0,
			0,
			sizeof(Header));
		DWORD error = GetLastError();
	}

	return this->pHeader;
}

LPVOID FileDesc::GetBuffer()
{
	if (this->pBuffer == NULL)
	{
		this->pBuffer = MapViewOfFile(hMapFile, // handle to map object
			FILE_MAP_ALL_ACCESS,  // read/write permission
			0,
			0,
			MAP_SIZE);
		DWORD error = GetLastError();

		this->pData = ((char*)this->pBuffer) + sizeof(Header);
	}

	return this->pData;
}

void FileDesc::ReleaseBuffer()
{
	UnmapViewOfFile(this->pBuffer);
	this->pBuffer = NULL;
	this->pData = NULL;
}

