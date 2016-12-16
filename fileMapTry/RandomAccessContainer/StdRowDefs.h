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
	
	char column[15][256];

} TinyRow15Cols;

typedef struct
{
	int index;

	char column[15][512];

} SmalRow15Cols;

typedef struct
{
	int index;

	char column[10][1024];
} Std1KRow10Cols;

typedef struct
{
	int index;

	char column[8][2048];

} Std2KRow8Cols;




