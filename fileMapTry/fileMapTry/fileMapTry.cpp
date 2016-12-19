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

#include "QuickSort.h"

#pragma comment(lib, "user32.lib")

//#define BUF_SIZE 0x80000000
//#define MAP_SIZE 0x80000000

TCHAR szName[] = TEXT("C:\\testmapa.pgf");


//przyk�adowa struktura organizacji rekordu w zbiorze (Set)
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


int random[] = { 4, 2, 1, 3, 8, 5, 7, 6 };


int _tmain()
{
	QuickSort::DoSort<int>(random, 0, 8);
	//vtab_init("D:\\Menerwa\dane");

	//int size = vtab_CountProc("test");

	//char *v = vtab_GetColValue("test", 1, 1);

	//vtab_WriteColValue("test", "2wartosc testowa2", 1, 1);

	//char *v2 = vtab_GetColValue("test", 1, 1);

	//w jakim folderze przechowywane s�/b�d� dane (zbiory - Set)
	Context c(TEXT("C:\\Temp"));
	
	//Set<row> contact = c.get<row>(TEXT("contact"));

	//otw�rz zbi�r o nazwie product i zmapuj go na struktur� row
	Set<row> product = c.get<row>(TEXT("product"));

	row p1;

	time_t t1, t2;



	//Odczyt 500K wierszy ze zbioru
	printf_s("przebieg1: start.\n");


	char tbuf[512];
	time(&t1);

	for (int i = 0; i < 500000; i++) {
		
		//Tak ----------------
		//int a = product[i].id;

		//char *b = product[i].str1;
		//char *c = product[i].str6;


		//lub tak ----------------
		row& data = product[i];

		int a = data.id;
		
		char *b = data.str1;
		char *c = data.str6;

		sprintf_s(tbuf, "[%s][%s]", b, c);
	}
	time(&t2);

	int seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);


	printf_s("przebieg2: start.\n");
	time(&t1);
	for (int i = 0; i < 500000; i++) {

		//tak te� mo�na
		row data = product[i];

		int a = data.id;
		char *b = data.str1;
		char *c = data.str6;

		sprintf_s(tbuf, "[%s][%s]", b, c);

		//printf_s(tbuf);
	}
	time(&t2);

	seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);


	time(&t1);
	//zapisujemy kolejno 500K rekord�w
	for (int i = 499999; i >= 0; i--) {

		p1.id = i + 1;
		p1.lp = i;
		sprintf_s(p1.str1, "rev 1: a %d plus %d is [%d]", i + 1, i, i);
		sprintf_s(p1.str6, "rev 6: a %d plus %d is [%d]", i + 1, i, i);

		product[i] = p1;
	}

	time(&t2);
	seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);

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