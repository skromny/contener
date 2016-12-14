#pragma once

#include <map>
#include "SetUtils.h"
#include "Set.h"

using namespace std;

class __declspec(dllexport) Context
{
private:
	LPCWSTR path;

	map<LPCWSTR, void*> sets;

public:
	Context(LPCWSTR path);
	virtual ~Context();

	template <typename T>
	Set<T>& get(const LPCWSTR key)
	{
		if (this->sets.find(key) == this->sets.end()) 
		{
			sets[key] = new Set<T>(path, key);
		}

		Set<T> *s = (Set<T>*)sets[key];


		return (Set<T>&) *s;
	}
};

