// fileMapTry.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#include "Set.h"
#include "Context.h"

#pragma comment(lib, "user32.lib")

#define BUF_SIZE 0x80000000
#define MAP_SIZE 0x80000000

TCHAR szName[] = TEXT("C:\\testmapa.pgf");

struct row 
{
	int id;
	int lp;

	char str1[512];
	char str2[512];
	char str3[256];
	char str4[4096];
	char str5[2048];
	char str6[8192];
};

void allocm(char* &p, int size) {

	p = new char[size];
	p[size - 1] = 'K';
	p[0] = 'S';
}


int _tmain()
{
	HANDLE hFile;
	HANDLE hMapFile;
	row* pBuf;

	Context c(TEXT("C:\\Temp"));

	Set<row> product = c.get<row>(TEXT("product"));
	Set<row> contact = c.get<row>(TEXT("contact"));

	row p1;

	p1.id = 1;
	p1.lp = 0;
	strcpy_s(p1.str1, "[(0)to jest testowy tekst str 1]");
	strcpy_s(p1.str6, "[(0)to jest testowy tekst str 6]");

	product[0] = p1;

	p1.id = 2;
	p1.lp = 1;
	strcpy_s(p1.str1, "[(1)to jest testowy tekst str 1]");
	strcpy_s(p1.str6, "[(1)to jest testowy tekst str 6]");

	product[1] = p1;

	p1.id = 137448;
	p1.lp = 137447;
	strcpy_s(p1.str1, "[(137447)to jest testowy tekst str 1]");
	strcpy_s(p1.str6, "[(137447)to jest testowy tekst str 6]");

	product[137447] = p1;

	p1.id = 137449;
	p1.lp = 137448;
	strcpy_s(p1.str1, "[(137447)to jest testowy tekst str 1]");
	strcpy_s(p1.str6, "[(137447)to jest testowy tekst str 6]");

	product[137448] = p1;



	hFile = CreateFile(szName
		, GENERIC_READ | GENERIC_WRITE
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_ALWAYS
		, FILE_ATTRIBUTE_NORMAL
		, NULL
	);

	hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, BUF_SIZE, (LPCWSTR)"FILEMEM");

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not open file mapping object (%d).\n"),
			GetLastError());
		return 1;
	}

	pBuf = (row*)MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		MAP_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		CloseHandle(hMapFile);

		return 1;
	}

	int max = BUF_SIZE / sizeof(row);

	row a;
	a.id = 5;
	a.lp = 1;
	strcpy_s(a.str1, "to jest tekst 1");
	strcpy_s(a.str2, "to jest tekst 2");
	strcpy_s(a.str3, "to jest tekst 3");

	pBuf[0] = a;
	pBuf[1] = a;
	pBuf[2] = a;
	pBuf[500] = a;
	pBuf[1500] = a;
	pBuf[100000] = a;

	char *t = (char*)pBuf;

	char *t2 = t + sizeof(a);

	char *t3 = t + MAP_SIZE - sizeof(row);

	row *r1 = (row*)t3;

	*r1 = a;

	//MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);

	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);

	return 0;
}