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


//przyk³adowa struktura organizacji rekordu w zbiorze (Set)
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

int fileCapacity = 30;
int bufferCapacity = 3;


int _tmain()
{


	time_t t1, t2;
	int seconds;

	//vtab_init("D:\\Menerwa\dane");

	//int size = vtab_CountProc("test");

	//char *v = vtab_GetColValue("test", 1, 1);

	//vtab_WriteColValue("test", "2wartosc testowa2", 1, 1);

	//char *v2 = vtab_GetColValue("test", 1, 1);

	//w jakim folderze przechowywane s¹/bêd¹ dane (zbiory - Set)
	Context c(TEXT("C:\\Temp"));
	
	//Set<row> contact = c.get<row>(TEXT("contact"));

	srand(time(NULL));

	//otwórz zbiór o nazwie product i zmapuj go na strukturê row
	Set<row> product = c.get<row>(TEXT("product"));


	row trow;


	//zapisujemy kolejno 500K rekordów
	for (int i = 0; i < 500000; i++) 
	{
		trow.id = i + 1;
		trow.lp = i;
		sprintf_s(trow.str1, "wier %d on %d", (rand() + rand() + rand()) % 590000 + 1, i);


		//printf_s("%s\n", trow.str1);
		product[i] = trow;
	}

	//Odczyt 500K wierszy ze zbioru
	printf_s("przebieg1: start.\n");


	char tbuf[512];
	time(&t1);

	for (int i = 0; i < 500000; i++) {

		row& data = product[i];

		int a = data.id;

		char *b = data.str1;

		sprintf_s(tbuf, "%d: [%s]\n", i, b);
		//printf_s(tbuf);
	}
	time(&t2);

	seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);

	//trow.id = 1;
	//trow.lp = 1;
	//sprintf_s(trow.str1, "wier %d x 01", rand() % 10000 + 1);
	//product[0] = trow;

	//trow.id = 2;
	//trow.lp = 2;
	//sprintf_s(trow.str1, "wier %d x 01", rand() % 10000 + 1);
	//product[1] = trow;

	//trow.id = 3;
	//trow.lp = 3;
	//sprintf_s(trow.str1, "wier %d x 01", rand() % 10000 + 1);
	//product[2] = trow;

	//trow.id = 4;
	//trow.lp = 4;
	//sprintf_s(trow.str1, "wier %d x 01", rand() % 10000 + 1);
	//product[3] = trow;

	/*int ix = 0;
	for (int i = 0; i < 10000000; i++)
	{
		int idx = (rand() + rand() + rand()) % 99000;
		row& p = product[idx];
		ix = i;
		printf_s("%d: %s.\n", idx, p.str1);
	}
	printf_s("ix: %d.\n", ix);*/




	//Odczyt 500K wierszy ze zbioru
	printf_s("sortowanie: start.\n");

	time(&t1);

	QuickSort::DoSort<row>(product);

	time(&t2);

	seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);


	row p1;
	

	//Odczyt 500K wierszy ze zbioru
	printf_s("przebieg1: start.\n");


	tbuf[512];
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

	seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);


	printf_s("przebieg2: start.\n");
	time(&t1);
	for (int i = 0; i < 500000; i++) {

		//tak te¿ mo¿na
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
	//zapisujemy kolejno 500K rekordów
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