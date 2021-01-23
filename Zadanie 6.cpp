#include <iostream>
#include <fstream>
#include <random>
#include <queue>
#include <chrono>
#include <string>
using namespace std;

void insert_sort(int tab[], int n)
{
	int max{};
	int index{};
	int tmp{};
	for (int i = n-1; i >=0 ; i--)
	{
		max = tab[0];
		index = 0;
		for (int j = 1; j <= i; j++)
		{
			if (tab[j] > max)
			{
				max = tab[j];
				index = j;
			}
		}
		tmp = tab[index];
		tab[index] = tab[i];
		tab[i] = tmp;
	}
}

void bubble_sort(int tab[], int n)
{
	int tmp{};
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (tab[j] > tab[j + 1])
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
		}
	}
}

void quick_sort(int tab[], int l, int r, int n)
{
	if (l < r)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> RNG(l, r);
		int pivot = l;
		int x = tab[r];
		for (int j = l; j < r; j++)
		{
			if (tab[j] <= x)
			{
				int tmp = tab[pivot];
				tab[pivot] = tab[j];
				tab[j] = tmp;
				pivot++;
			}
		}
		int tmp = tab[r];
		tab[r] = tab[pivot];
		tab[pivot] = tmp;
		quick_sort(tab, l, pivot-1,n);
		quick_sort(tab, pivot+1, r,n);
	}
}

void heapify(int tab[], int i, int m)
{
	int l = 2 * i + 1;
	int p = 2 * i + 2;
	int max=i;
	if (l < m && tab[l] > tab[i])
	{
		max = l;
	}
	if (p < m && tab[p] > tab[max])
	{
		max = p;
	}
	if (max != i)
	{
		int tmp = tab[i];
		tab[i] = tab[max];
		tab[max] = tmp;
		heapify(tab, max, m);
	}
}

void heap_sort(int tab[], int n)
{
	for (int i = n / 2 - 1; i >= 0;i--)
	{
		heapify(tab, i, n);
	}
	for (int i = n - 1; i > 0; i--)
	{
		int tmp = tab[0];
		tab[0] = tab[i];
		tab[i] = tmp;
		heapify(tab, 0, i);
	}
}

void merge(int tab[], int l, int mid, int r)
{
	queue<int> q1, q2;
	for (int i = l; i <= mid; i++)
	{
		q1.push(tab[i]);
	}
	for (int i = mid + 1; i <= r; i++)
	{
		q2.push(tab[i]);
	}
	int i = l;
	while (!q1.empty() && !q2.empty())
	{
		if (q1.front() <= q2.front())
		{
			tab[i] = q1.front();
			q1.pop();
			i++;
		}
		else
		{
			tab[i] = q2.front();
			q2.pop();
			i++;
		}
	}
	while (!q1.empty())
	{
		tab[i] = q1.front();
		q1.pop();
		i++;
	}
	while (!q2.empty())
	{
		tab[i] = q2.front();
		q2.pop();
		i++;
	}
}

void merge_sort(int tab[],int l, int r)
{
	if (l < r)
	{
		int mid = (l + r - 1) / 2;
		merge_sort(tab, l, mid);
		merge_sort(tab, mid + 1, r);
		merge(tab, l, mid, r);
	}
}

/*
---Algorytmy Sortowania---

Dane wejsciowe sa pobierane z plikow. Sa wspolne dla wszystkich algorytmow.
Nazwy plikow wejsciowych: input0_100.txt ... input9_100.txt oraz inptu0_100000.txt ... input9_100000.txt
Wyjscie jest zapisywane do plikow - kazdy plik ma nazwe zawierajaca nazwe algorytmu oraz identyfikator pliku wejscia.
Dodatkowo po zakonczeniu pracy programu w konsoli wyswietlane sa czasy dzialania konkretnych algorytmow na konkretnych zbiorach
oraz statystyki dla danych wielkosci zbiorow. Zostana one rowniez zapisane do pliku analiza_statystyczna.txt.
W plikach wejsciowych w pierwszej linii znajduje sie liczba calkowita n okreslajaca ilosc elementow.
W kolejnych n liniach znajduja sie liczby calkowite do posortowania.

*/

int main()
{
	const int xa = 20;
	string sources[xa];
	for (int i = 0; i < xa/2; i++)
	{
		sources[i] = "input" + to_string(i) + "_100.txt";
		sources[i+10] = "input" + to_string(i) + "_100000.txt";
	}
	chrono::duration<double> durations[5][xa];
	double srednia[5][2]{};
	double odchylenie_standardowe[5][2]{};
	string methods[5] = { "\n---Sortowanie babelkowe---\n","\n---Sortowanie przez wstawianie---\n","\n---Sortowanie szybkie---\n", "\n---Sortowanie stogowe---\n","\n---Sortowanie przez scalanie---\n" };
	int n{};
	for (int x = 0; x < xa; x++)
	{
		int* tab;
		int* sort;
		string current = sources[x].substr(sources[x].find('_')+1,sources[x].length()- sources[x].find('_') - 4);
		fstream file(sources[x]);
		file >> n;
		tab = new int[n];
		sort = new int[n];
		for (int i = 0; i < n; i++)
		{
			file >> tab[i];
			sort[i] = tab[i];
		}
		file.close();
		auto start = chrono::high_resolution_clock::now();
		bubble_sort(sort, n);
		auto end = chrono::high_resolution_clock::now();
		durations[0][x] = end - start;
		fstream out("bubble_out" + sources[x].substr(2, sources[x].length() - 2), fstream::out);
		for (int i = 0; i < n; i++)
		{
			out << sort[i] << "\n";
			sort[i] = tab[i];

		}
		out.close();
		start = chrono::high_resolution_clock::now();
		insert_sort(sort, n);
		end = chrono::high_resolution_clock::now();
		durations[1][x] = end - start;
		out.open("insert_out" + sources[x].substr(2, sources[x].length() - 2), fstream::out);
		for (int i = 0; i < n; i++)
		{
			out << sort[i] << "\n";
			sort[i] = tab[i];
		}
		out.close();
		start = chrono::high_resolution_clock::now();
		quick_sort(sort, 0, n - 1, n - 1);
		end = chrono::high_resolution_clock::now();
		durations[2][x] = end - start;
		out.open("quick_out" + sources[x].substr(2, sources[x].length() - 2), fstream::out);
		for (int i = 0; i < n; i++)
		{
			out << sort[i] << "\n";
			sort[i] = tab[i];
		}
		out.close();
		start = chrono::high_resolution_clock::now();
		heap_sort(sort, n);
		end = chrono::high_resolution_clock::now();
		durations[3][x] = end - start;
		out.open("heap_out" + sources[x].substr(2, sources[x].length() - 2), fstream::out);
		for (int i = 0; i < n; i++)
		{
			out << sort[i] << "\n";
			sort[i] = tab[i];
		}
		out.close();
		start = chrono::high_resolution_clock::now();
		merge_sort(sort, 0, n - 1);
		end = chrono::high_resolution_clock::now();
		durations[4][x] = end - start;
		out.open("merge_out" + sources[x].substr(2, sources[x].length() - 2), fstream::out);
		for (int i = 0; i < n; i++)
		{
			out << sort[i] << "\n";
		}
		out.close();
		delete[] tab;
		delete[] sort;
	}
	fstream stat("analiza_statystyczna.txt", fstream::out);
	for (int i = 0; i < 5; i++)
	{
		cout << methods[i] << "\n";
		for (int x = 0; x < xa; x++)
		{
			cout << sources[x]<<" "<<durations[i][x].count() << " [s]\n";
			if (x < xa/2)
			{
				srednia[i][0] += durations[i][x].count();
			}
			else
			{
				srednia[i][1] += durations[i][x].count();
			}
		}
		srednia[i][0] /= 10;
		srednia[i][1] /= 10;
		for (int x = 0; x < xa/2; x++)
		{
			odchylenie_standardowe[i][0] += pow(srednia[i][0] - durations[i][x].count(), 2);
			odchylenie_standardowe[i][1] += pow(srednia[i][1] - durations[i][x+10].count(), 2);
		}
		odchylenie_standardowe[i][0] = sqrt(odchylenie_standardowe[i][0] / 10);
		odchylenie_standardowe[i][1] = sqrt(odchylenie_standardowe[i][1] / 10);
		stat << methods[i] << "\n";
		stat << "Srednia dla 100 elementow: " << srednia[i][0] << "\n";
		stat << "Odchylenie standardowe dla 100 elementow: " << odchylenie_standardowe[i][0] << "\n";
		stat << "Srednia dla 100000 elementow: " << srednia[i][1] << "\n";
		stat << "Odchylenie standardowe dla 100000 elementow: " << odchylenie_standardowe[i][1] << "\n";
		cout << "Srednia dla 100 elementow: " << srednia[i][0] << "\n";
		cout << "Odchylenie standardowe dla 100 elementow: " << odchylenie_standardowe[i][0] << "\n";
		cout << "Srednia dla 100000 elementow: " << srednia[i][1] << "\n";
		cout << "Odchylenie standardowe dla 100000 elementow: " << odchylenie_standardowe[i][1] << "\n";
	}
	stat.close();
}