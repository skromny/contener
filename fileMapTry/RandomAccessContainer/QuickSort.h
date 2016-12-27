
#include "Set.h"
#include <string>

using namespace std;

class __declspec(dllexport) QuickSort
{
public:
	QuickSort();
	virtual ~QuickSort();

	template<class T>
	static void DoSort(Set<T>& set)
	{
		//qsort(array, r, sizeof(T), QuickSort::compare);
		vector<int> index;
		for (int i = 0; i < set.Count(); i++)
			index.push_back(i);
		QuickSort::Sort<T>(set, index, 0, index.size() - 1);
		//for (int i = 0; i < index.size(); i++)
		//{
		//	printf_s("%d : %s\n", i + 1, set[index[i]].str1);
		//}
	}

private:
	static int compare_int(const void * a, const void * b)
	{
		return (*(int*)a - *(int*)b);
	}

	static int compare_wstr(const wstring *a, const wstring *b)
	{
		return _wcsicmp(a->c_str(), b->c_str());
	}

	static int compare_str(const char *a, const char *b)
	{
		int r = _stricmp(a, b);
		//printf_s("%s : %s  => %s\n", a, b, ((r > 0) ? "wiekszy" : "mniejszy"));
		return r;
	}

	template<class T>
	static void Sort(Set<T>& set, vector<int>& index, int p, int r)
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
	static int Partition(Set<T>& set, vector<int>& index, int p, int r)
	{
		//printf_s("p: %d, i.p: %d\n", p, index[p]);
		int idx = index[p];
		T x = set[idx]; // obieramy x
		int tmp;

		int i = p, j = r; // i, j - indeksy w tabeli


		while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
		{
			
			//idx = index[j];
			//printf_s("j: %d, i.j: %d\n", j, idx);
			//T& z = set[index[j]];
			//printf_s("3.1=>");
			//printf_s("3.2=>%s\n", z.str1);
			while (compare_str(set[index[j]].str1, x.str1) > 0)
				j--;

			//printf_s("4");
			
			while (compare_str(set[index[i]].str1, x.str1) < 0)
				i++;

			//printf_s("5");

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