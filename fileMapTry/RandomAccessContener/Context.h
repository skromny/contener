#pragma once

#include <map>
#include "ISet.h"
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
			TCHAR fname[MAX_PATH];
			SetUtils::concatStrings(this->path, key, TEXT("\\"), fname);

			sets[key] = new Set<T>(fname);
		}

		Set<T> *s = (Set<T>*)sets[key];

		return (Set<T>&) *s;
	}
};

