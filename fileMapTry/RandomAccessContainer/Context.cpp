
#include "stdafx.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include "Context.h"

using namespace std;

Context::Context(LPCWSTR path)
{
	this->path = path;
}


Context::~Context()
{
}

