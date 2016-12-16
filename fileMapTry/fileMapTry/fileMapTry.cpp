// fileMapTry.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#include "Set.h"
#include "Context.h"
#include "rac.h"
#include <time.h>

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

int _tmain()
{
	vtab_CountProc("test");

	char *v = vtab_GetColValue("test", 1, 1);

	vtab_WriteColValue("test", "2wartosc testowa2", 1, 1);

	char *v2 = vtab_GetColValue("test", 1, 1);

	HANDLE hFile;
	HANDLE hMapFile;
	row* pBuf;

	Context c(TEXT("C:\\Temp"));

	
	Set<row> contact = c.get<row>(TEXT("contact"));

	Set<row> product = c.get<row>(TEXT("product"));

	row p1;

	time_t t1, t2;

	printf_s("przebieg1: start.\n");


	char tbuf[512];
	time(&t1);

	for (int i = 0; i < 500000; i++) {
		
		//printf_s("%d (%d) %s, %s.\n", i, product[i].id, product[i].str1, product[i].str6);
		//_tprintf(TEXT("%d (%d) .\n"), i, product[i].id, p1.str1, p1.str6);

		int a = product[i].id;
		
		char *b = product[i].str1;
		char *c = product[i].str6;

		sprintf_s(tbuf, "[%s][%s]", b, c);
	}
	time(&t2);

	int seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);


	printf_s("przebieg2: start.\n");
	time(&t1);
	for (int i = 0; i < 500000; i++) {

		//printf_s("%d (%d) %s, %s.\n", i, product[i].id, product[i].str1, product[i].str6);
		//_tprintf(TEXT("%d (%d) .\n"), i, product[i].id, p1.str1, p1.str6);

		int a = product[i].id;
		char *b = product[i].str1;
		char *c = product[i].str6;

		sprintf_s(tbuf, "[%s][%s]", b, c);
	}
	time(&t2);

	seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);

	for (int i = 0; i < 500000; i++) {
		//printf_s(": %d\n", i);
		p1.id = i +1;
		p1.lp = i;
		sprintf_s(p1.str1, "1: a %d plus %d is [%d]", i + 1, i, i);
		sprintf_s(p1.str6, "6: a %d plus %d is [%d]", i + 1, i, i);

		

		product[i] = p1;
	}

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



	return 0;
}