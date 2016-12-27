#pragma once

#include "CacheItem.h"
#include <map>

using namespace std;

class __declspec(dllexport) Cache
{
public:

	Cache();
	Cache(int max);
	~Cache();

	bool ContainsKey(int key);

	LPVOID Add(int key, LPVOID data);

	LPVOID GetBuffer(int key, LPVOID &buffer);

	LPVOID operator[] (const int key);

	int Size();

private:

	int maxItems;

	map<int, CacheItem*> items;
};

