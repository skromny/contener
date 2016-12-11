
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

	this->hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, BUF_SIZE, (LPCWSTR)"FILEMEM");

	this->pBuffer = MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		MAP_SIZE);
}

FileDesc::~FileDesc() 
{

}

LPVOID FileDesc::GetBuffer()
{
	return this->pBuffer;
}