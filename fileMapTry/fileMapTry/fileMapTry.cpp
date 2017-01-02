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
#include "StdRowDefs.h"

#pragma comment(lib, "user32.lib")

//#define BUF_SIZE 0x80000000
//#define MAP_SIZE 0x80000000

TCHAR szName[] = TEXT("C:\\testmapa.pgf");


//przyk³adowa struktura organizacji rekordu w zbiorze (Set)


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
	
	//Context c(TEXT("C:\\Temp"));
	
	srand(time(NULL));

	//otwórz zbiór o nazwie product i zmapuj go na strukturê row
	//Set<TinyRow15Cols> product = c.get<TinyRow15Cols>(TEXT("product"));


	TinyRow15Cols trow;


	//zapisujemy kolejno 500K rekordów
	//for (int i = 0; i < 500000; i++) 
	//{
	//	trow.index = i + 1;
	//	sprintf_s(trow.column[0], "wier %d on %d", (rand() + rand() + rand() + rand() + rand() + rand()) % 590000 + 1, 100);


	//	//printf_s("%s\n", trow.str1);
	//	product[i] = trow;
	//}

	//Odczyt 500K wierszy ze zbioru
	printf_s("przebieg1: start.\n");


	char tbuf[512];
	time(&t1);

	//for (int i = 0; i < 500000; i++) {

	//	TinyRow15Cols& data = product[i];

	//	int a = data.index;

	//	char *b = data.column[0];

	//	sprintf_s(tbuf, "%d: [%s]\n", i, b);
	//	printf_s(tbuf);
	//}
	time(&t2);

	seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);


	//Odczyt 500K wierszy ze zbioru
	printf_s("sortowanie: start.\n");

	time(&t1);
	int orig;
	//TinyRow15Cols& r = QuickSort::DoSort<TinyRow15Cols>(product, 0, 0, orig);

	//QuickSort::Find<TinyRow15Cols>(product, 0, "wier 76181 on 100");

	char buf[256];

	for (int i = 0; i < 500000; i++) 
	{
		trow.index = i + 1;
		sprintf_s(buf, "wier %d on %d", (rand() + rand() + rand() + rand() + rand() + rand()) % 590000 + 1, i);

		printf_s("%s\n", buf);
		vtab_WriteColValue("product", buf, 0, i);
		
	}
	char *res = vtab_GetEqualPosListProc("product", 0, "wier 76181 on 100");

	time(&t2);

	seconds = difftime(t2, t1);

	printf_s("czas: %d.\n", seconds);

	
	return 0;
}