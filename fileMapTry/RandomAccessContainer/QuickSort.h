
#pragma once

#include "Set.h"
#include <string>
#include <algorithm>

using namespace std;

class __declspec(dllexport) QuickSort
{
public:

	QuickSort();
	virtual ~QuickSort();

	template<class T>
	static T& DoSort(Set<T>& set, int col, int pos, int &idx)
	{
		vector<int> index;
		vector<char*> data;
		for (int i = 0; i < set.Count(); i++) 
		{
			index.push_back(i);
			char buf[256];
			strcpy_s(buf, 256, set[i].column[col]);
			data.push_back(buf);
		}

		QuickSort::Sort<T>(data, index, 0, index.size() - 1);

		return set[index[pos]];
	}

	template<class T>
	static char* Find(Set<T>& set, int col, char *toFind)
	{
		vector<int> index;
		vector<char*> data;
		char *response = new char[1024];
		response[0] = 0;
		for (int i = 0; i < set.Count(); i++)
		{
			char buf[256];
			
			strcpy_s(buf, 256, set[i].column[col]);
			if (compare_str(buf, toFind) == 0)
			{
				index.push_back(i);
				data.push_back(buf);
				if (index.size() == 1)
					sprintf_s(response, 1024, "%d", i);
				else
					sprintf_s(response, 1024, "%s,%d", response, i);
			}
		}

		return response;
	}


	template<class T>
	static void DoSortFile(Set<T>& set)
	{
		vector<int> index;
		for (int i = 0; i < set.Count(); i++)
			index.push_back(i);
		QuickSort::SortFile<T>(set, index, 0, index.size() - 1);
	}

private:
	static int compare_int(const void * a, const void * b)
	{
		return (*(int*)a - *(int*)b);
	}

	static int compare_wstr(const wchar_t *a, const wchar_t *b)
	{
		return _wcsicmp(a, b);
	}

	static int compare_str(const char *a, const char *b)
	{
		int r = _stricmp(a, b);
		//printf_s("%s : %s  => %s\n", a, b, ((r > 0) ? "wiekszy" : "mniejszy"));
		return r;
	}

	template<class T>
	static void Sort(vector<char*>& data, vector<int>& index, int p, int r)
	{
		int q;
		if (p < r)
		{
			q = QuickSort::Partition<T>(data, index, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
			QuickSort::Sort<T>(data, index, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
			QuickSort::Sort<T>(data, index, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
		}
	}

	template<class T>
	static void SortFile(Set<T>& set, vector<int>& index, int p, int r)
	{
		int q;
		if (p < r)
		{
			q = QuickSort::Partition<T>(set, index, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
			QuickSort::Sort<T>(set, index, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
			QuickSort::Sort<T>(set, index, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
		}
	}

	template<class T>
	static int Partition(vector<char*>& data, vector<int>& index, int p, int r)
	{
		int idx = index[p];
		char *x = data[idx]; // obieramy x
		int tmp;

		int i = p, j = r; // i, j - indeksy w tabeli

		while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
		{
			while (compare_str(data[index[j]], x) > 0)
				j--;

			while (compare_str(data[index[i]], x) < 0)
				i++;

			if (i < j) // zamieniamy miejscami gdy i < j
			{
				tmp = index[i];
				index[i] = index[j];
				index[j] = tmp;
				i++;
				j--;
			}
			else // gdy i >= j zwracamy j jako punkt podzialu tablicy
				return j;
		}
	}

	template<class T>
	static int PartitionFile(Set<T>& set, vector<int>& index, int p, int r)
	{
		int idx = index[p];
		T x = set[idx]; // obieramy x
		int tmp;

		int i = p, j = r; // i, j - indeksy w tabeli

		while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
		{
			while (compare_str(set[index[j]].column[0], x.column[0]) > 0)
				j--;

			while (compare_str(set[index[i]].column[0], x.column[0]) < 0)
				i++;

			if (i < j) // zamieniamy miejscami gdy i < j
			{
				tmp = index[i];
				index[i] = index[j];
				index[j] = tmp;
				i++;
				j--;
			}
			else // gdy i >= j zwracamy j jako punkt podzialu tablicy
				return j;
		}
	}
};