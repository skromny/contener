
#include "Set.h"
#include <string>

using namespace std;

class __declspec(dllexport) QuickSort
{
public:
	QuickSort();
	virtual ~QuickSort();

	template<class T>
	static void DoSort(Set<T> set)
	{
		//qsort(array, r, sizeof(T), QuickSort::compare);
		QuickSort::Sort<T>(set, p, r);
	}

private:
	static int compare_int(const void * a, const void * b)
	{
		return (*(int*)a - *(int*)b);
	}

	static int compare_str(const wstring *a, const wstring *b)
	{
		return _wcsicmp(a->c_str(), b->c_str());
	}

	template<class T>
	static void Sort(Set<T> set, int p, int r)
	{
		int q;
		if (p < r)
		{
			q = QuickSort::Partition<T>(set, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
			QuickSort::Sort<T>(array, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
			QuickSort::Sort<T>(array, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
		}
	}

	template<class T>
	static int Partition(T array[], int p, int r)
	{
		T& x = array[p]; // obieramy x
		T& tmp;
		int i = p, j = r; // i, j - indeksy w tabeli
		while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
		{
			while (array[j] > x) // dopoki elementy sa wieksze od x
				j--;
			while (array[i] < x) // dopoki elementy sa mniejsze od x
				i++;
			if (i < j) // zamieniamy miejscami gdy i < j
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
				i++;
				j--;
			}
			else // gdy i >= j zwracamy j jako punkt podzialu tablicy
				return j;
		}
	}
};