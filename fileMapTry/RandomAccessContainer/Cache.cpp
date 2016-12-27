
#include "Cache.h"

Cache::Cache() : Cache(4) { }

Cache::Cache(int max)
{
	maxItems = max;
}

Cache::~Cache()
{

}

bool Cache::ContainsKey(int key)
{
	if (items.find(key) == items.end()) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}

LPVOID Cache::Add(int key, LPVOID data)
{
	CacheItem *item = new CacheItem();
	item->SetData(data);

	items[key] = item;

	return data;
}

LPVOID Cache::GetBuffer(int key, LPVOID &buffer)
{
	CacheItem *item = items[key];
	buffer = NULL;
	if (item == NULL) 
	{
		if (items.size() > maxItems)
		{
			int toDelKey = -1;

			DWORD t = GetTickCount() + 1000;

			DWORD t2;
			
			printf_s("Potrzebne miejsce dla %d  \n", key);
			for (map<int, CacheItem*>::iterator it = items.begin(); it != items.end(); ++it)
			{
				if (it->second != NULL)
				{
					printf_s("%d: GB=>   %ld  <  %ld  \n", it->first, (int)it->second->GetLastTouch(), (int)t);
					if ((t2 = it->second->GetLastTouch()) < t)
					{
						t = t2;
						toDelKey = it->first;
						buffer = it->second->GetData();
					}
				}
			}
			
			if (toDelKey >= 0) {
				//delete items[toDelKey];
				items.erase(toDelKey);
			}
			else
				printf_s("HE?????!!!!  \n");
		}
		return NULL;
	}
	else
		return item->GetData();
}

LPVOID Cache::operator[] (const int key)
{
	return items[key];
	//if (items.find(key) != items.end())
	//{
	//	return items[key]->GetData();
	//}
	//else
	//{
	//	return NULL;
	//}
}

int Cache::Size()
{
	return items.size();
}