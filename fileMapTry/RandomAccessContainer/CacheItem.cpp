
#include "CacheItem.h"

CacheItem::CacheItem() : CacheItem(NULL) { }

CacheItem::CacheItem(LPVOID data)
{
	
	lastTouch = GetTickCount();

	pData = data;
}


CacheItem::~CacheItem()
{

}

LPVOID CacheItem::GetData()
{
	lastTouch = GetTickCount();

	return pData;
}

LONG CacheItem::GetLastTouch()
{
	return lastTouch;
}

void CacheItem::SetData(LPVOID data)
{
	pData = data;
}
