
#include "FileDesc.h"

FileDesc::FileDesc(LPCWSTR path) : FileDesc(path, false) { }

FileDesc::FileDesc(LPCWSTR path, bool header)
{
	this->hFile = CreateFile(path
		, GENERIC_READ | GENERIC_WRITE
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_ALWAYS
		, FILE_ATTRIBUTE_NORMAL
		, NULL
	);

	this->hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, (header ? sizeof(Header) : BUF_SIZE), NULL);
}

FileDesc::~FileDesc() 
{

}

//Header* FileDesc::GetHeader()
//{
//	if (this->pHeader == NULL) 
//	{
//		this->pHeader = (Header*)MapViewOfFile(hMapFile, // handle to map object
//			FILE_MAP_ALL_ACCESS,  // read/write permission
//			0,
//			0,
//			sizeof(Header));
//		DWORD error = GetLastError();
//	}
//
//	return this->pHeader;
//}

Header* FileDesc::GetHeader()
{
	return (Header*)MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		sizeof(Header));
}

//LPVOID FileDesc::GetBuffer(DWORD offset)
//{
//	DWORD lo = offset & sysInfo.dwAllocationGranularity;
//
//	if (this->pBuffer == NULL)
//	{
//		this->pBuffer = MapViewOfFile(hMapFile, // handle to map object
//			FILE_MAP_ALL_ACCESS,  // read/write permission
//			0,
//			offset - lo,
//			MAP_SIZE);
//		DWORD error = GetLastError();
//
//		this->pData = ((char*)this->pBuffer) + lo + sizeof(Header);
//	}
//
//	return this->pData;
//}

LPVOID FileDesc::GetBuffer(DWORD offset)
{
	return MapViewOfFile(hMapFile, // handle to map object
			FILE_MAP_ALL_ACCESS,  // read/write permission
			0,
			offset * MAP_SIZE,
			MAP_SIZE);
}

void FileDesc::ReleaseBuffer(LPVOID pBuffer)
{
	UnmapViewOfFile(pBuffer);
}

