#pragma once

#include "FileDesc.h"
#include "ISet.h"
#include <string>
#include <vector>

using namespace std;

template<class T>
class __declspec(dllexport) Set
{
public:

	Set(LPCWSTR name) {
		StringCchCopy(this->name, MAX_PATH, name);
	}
	virtual ~Set() {
	}

private:
	TCHAR name[MAX_PATH];
	int rowSize;

	//vector<Column> columns;
	vector<FileDesc> files;
};

