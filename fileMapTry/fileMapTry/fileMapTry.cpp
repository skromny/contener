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

	Context c(TEXT("C:\\Temp"));// = new Context("C:\\Temp");
	//Context *c = new Context("C:\\Temp");


	Set<row> s2 = c.get<row>(TEXT("product"));

	row x1 = s2[0];
	row zx1 = s2[1];

	row x02;
	x02.id = 137447;
	x02.lp = 137447;
	strcpy_s(x02.str1, "to jest tekst 1 [137447]");
	strcpy_s(x02.str2, "to jest tekst 2 [137447]");
	strcpy_s(x02.str3, "to jest tekst 3 [137447]");

	row x2 = s2[137447];
	s2[137447] = x02;

	int rx02 = x2.id;

	row cp_x2 = s2[137447];

	row x03;
	x03.id = 137448;
	x03.lp = 137448;
	strcpy_s(x03.str1, "to jest tekst 1 [137448]");
	strcpy_s(x03.str2, "to jest tekst 2 [137448]");
	strcpy_s(x03.str3, "to jest tekst 3 [137448]");

	row x3 = s2[137448];
	s2[137448] = x03;

	int rx03 = x3.id;

	row cp_x3 = s2[137447];


	Context *c2 = new Context(TEXT("C:\\Temp"));

	Set<row>& s4 = c2->get<row>(TEXT("contact"));

	row cp_x4 = s4[137447];
	row cp_x5 = s4[137448];

	x02.id = -137447;
	x02.lp = -137447;
	strcpy_s(x02.str1, "!! to jest tekst 1 [137447]");
	strcpy_s(x02.str2, "!! to jest tekst 2 [137447]");
	strcpy_s(x02.str3, "!! to jest tekst 3 [137447]");

	s4[137447] = x02;
	row cp_x6 = s4[137447];
	row cp_x7 = s4[137448];




	Set<row> *s5 = &c2->get<row>(TEXT("products"));

	Set<row> s6 = c2->get<row>(TEXT("products"));


	//hMapFile = OpenFileMapping(
	//	FILE_MAP_ALL_ACCESS,   // read/write access
	//	FALSE,                 // do not inherit the name
	//	szName);               // name of mapping object

	//Circle *c = new Circle(5.0);

	//c->move(5.8, 3.0);
	//c->area();


	//char *p;

	//allocm(p, 4);

	//p[1] = 'D';
	//p[32] = 'F';



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