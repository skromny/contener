#pragma once

typedef struct
{
	int count;
	int first;
	int last;

	int columns;
	int columnSize;

	int reserved0;
	int reserved1;
	int reserved2;
	int reserved3;
	int reserved4;

	char reserved[1024];
} Header;

typedef struct 
{
	int index;
	
	char column1[512];
	char column2[512];
	char column3[512];
	char column4[512];
	char column5[512];
} TinyRow5Cols;

typedef struct
{
	int index;

	char column1[1024];
	char column2[1024];
	char column3[1024];
	char column4[1024];
	char column5[1024];
	char column6[1024];
	char column7[1024];
	char column8[1024];
} SmallRow8Cols;

typedef struct
{
	int index;

	char column1[2048];
	char column2[2048];
	char column3[2048];
	char column4[2048];
	char column5[2048];
	char column6[2048];
	char column7[2048];
	char column8[2048];
} StandardRow8Cols;

typedef struct
{
	int index;

	char column1[2048];
	char column2[2048];
	char column3[2048];
	char column4[2048];
	char column5[2048];
	char column6[2048];
	char column7[2048];
	char column8[2048];
	char column9[2048];
	char column10[2048];
	char column10[2048];
} StandardRow10Cols;

typedef struct
{
	int index;

	char column1[4096];
	char column2[4096];
	char column3[4096];
	char column4[4096];
} BigRow4Cols;

typedef struct
{
	int index;

	char column1[4096];
	char column2[4096];
	char column3[4096];
	char column4[4096];
	char column5[4096];
	char column6[4096];
	char column7[4096];
	char column8[4096];
} BigRow8Cols;


