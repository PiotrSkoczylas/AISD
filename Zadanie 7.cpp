#include <iostream>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

double Rastragin(double x[], int n) {
	double sum = 10.0 * n;
	for (int i = 0; i < n; i++)
	{
		sum += x[i] * x[i] - 10 * cos(2 * M_PI * x[i]);
	}
	return sum;
}

double F(double (*funkcja)(double[], int), double tab[], int n, bool max)
{
	if (!max)
		return 10000.0 * n - funkcja(tab, n);
	return 10000.0 * n + funkcja(tab, n);
}

double Sphere(double x[], int n) {
	double sum{};
	for (int i = 0; i < n; i++)
	{
		sum += x[i] * x[i];
	}
	return sum;
}

void swap(double** tab, int a, int b, int n)
{
	double tmp{};
	for (int i = 0; i < n; i++)
	{
		tmp = tab[a][i];
		tab[a][i] = tab[b][i];
		tab[b][i] = tmp;
	}
}

void sort_B(double** tab, int n, double(*cmpF)(double (*)(double[], int),double[], int, bool), double (*f)(double x[], int n),int psize, bool max)
{
	for (int i = 0; i < psize - 1; i++)
	{
		for (int j = 0; j < psize - i - 1; j++)
		{
			if (cmpF(f,tab[j], n, max) < cmpF(f,tab[j + 1], n, max))
			{
				swap(tab, j, j + 1, n);
			}
		}
	}
}

void range_check(double** p, int i, int j, double l, double r)
{
	if (p[i][j] > r)
	{
		p[i][j] = r;
	}
	if (p[i][j] < l)
	{
		p[i][j] = l;
	}
}

void Algorytm_Genetyczny(int n, double (*f)(double x[], int n), double l, double r, double pm, double pk,int psize, bool max, int ilosc_iteracji)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> RNG(l, r);
	uniform_real_distribution<double> P(0, 1);
	double** populacja = new double*[psize];
	double** nowa_populacja = new double* [psize];
	double** pop = new double* [psize];
	double* sumW = new double[psize];
	double totalW{};
	for (int i = 0; i <psize; i++)
	{
		populacja[i] = new double[n];
		nowa_populacja[i] = new double[n];
		pop[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			populacja[i][j] = RNG(mt);
		}
	}
	sort_B(populacja, n, F, f, psize, max);
	for (int i = 0; i < psize; i++)
	{
		sumW[i] = F(f, populacja[i], n, max);
		totalW += sumW[i];
	}
	for (int i = 0; i < psize; i++)
	{
		sumW[i] /= totalW;
	}
	for (int i = psize - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			sumW[i] += sumW[j];
		}
	}
	for (int t = 0; t < ilosc_iteracji; t++)
	{
		for (int g = 0; g < psize; )
		{
			double los1 = P(mt);
			double los2 = P(mt);
			int mut1{}, mut2{};
			for (int i = 0; i < psize; i++)
				if (los1 < sumW[i]) {
					mut1 = i;
					break;
				}
			for (int i = 0; i < psize; i++)
				if (los2 < sumW[i]) {
					mut2 = i;
					break;
				}
			for (int k = 0; k < n; k++)
			{
				nowa_populacja[g][k] = populacja[mut1][k];
				nowa_populacja[g + 1][k] = populacja[mut2][k];
				los1 = P(mt);
				los2 = P(mt);
				if (los1 < pm)
				{
					nowa_populacja[g][k] += RNG(mt) / 10;
					range_check(nowa_populacja, g, k, l, r);
				}
				if (los2 < pm)
				{
					nowa_populacja[g + 1][k] += RNG(mt) / 10;
					range_check(nowa_populacja, g + 1, k, l, r);
				}
			}
			g += 2;
			double N = P(mt);
			for (int k = 0; k < n; k++)
			{
				los1 = P(mt);
				los2 = P(mt);
				if (los1 < pk)
				{
					nowa_populacja[g][k] = populacja[mut1][k] + N * (populacja[mut1][k] - populacja[mut2][k]);
					range_check(nowa_populacja, g, k, l, r);
				}
				if (los2 < pk)
				{
					nowa_populacja[g + 1][k] = populacja[mut2][k] + N * (populacja[mut2][k] - populacja[mut1][k]);
					range_check(nowa_populacja, g + 1, k, l, r);
				}
			}
			g += 2;
		}
		sort_B(nowa_populacja, n, F, f, psize, max);
		for (int i = 0; i < psize; i++)
		{
			for (int j = 0; j < n; j++)
			{
				pop[i][j] = populacja[i][j];
			}
		}
		int i = 0, j = 0;
		for (int k = 0; k < psize; k++)
		{
			if (F(f, pop[i], n, max) > F(f, nowa_populacja[j], n, max))
			{
				for (int z = 0; z < n; z++)
				{
					populacja[k][z] = pop[i][z];
				}
			}
			else
			{
				for (int z = 0; z < n; z++)
				{
					populacja[k][z] = nowa_populacja[j][z];
				}
			}
		}
		for (int i = 0; i < psize; i++)
		{
			sumW[i] = F(f, populacja[i], n, max);
			totalW += sumW[i];
		}
		for (int i = 0; i < psize; i++)
		{
			sumW[i] /= totalW;
		}
		for (int i = psize - 1; i >= 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				sumW[i] += sumW[j];
			}
		}
	}
	for (int i = 0; i < psize; i++)
	{
		cout << "x[" << i << "]: (";
		for (int j = 0; j < n; j++)
		{
			if (j != n - 1)
				cout << populacja[i][j] << ", ";
			else
				cout << populacja[i][j];
		}
		cout << ")\n";
		delete[] populacja[i];
		delete[] nowa_populacja[i];
		delete[] pop[i];
	}
	delete[] populacja;
	delete[] nowa_populacja;
	delete[] pop;
	delete[] sumW;
}

void Algorytm_Ewolucji_Roznicowej(int n, double (*f)(double x[], int n), double l, double r, double k, double pk, int psize, bool max, int ilosc_iteracji)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> RNG(l, r);
	uniform_real_distribution<double> P(0, 1);
	uniform_int_distribution<int> RandIndex(0, psize - 1);
	double** populacja = new double* [psize];
	double** nowa_populacja = new double* [psize];
	double** pop = new double* [psize];
	for (int i = 0; i < psize; i++)
	{
		populacja[i] = new double[n];
		nowa_populacja[i] = new double[n];
		pop[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			populacja[i][j] = RNG(mt);
		}
	}
	sort_B(populacja, n, F, f, psize, max);

	for (int t = 0; t < ilosc_iteracji; t++)
	{
		for (int g = 0; g < psize; g++)
		{
			int i1 = RandIndex(mt);
			int i2 = RandIndex(mt);
			int i3 = RandIndex(mt);
			for (int i = 0; i < n; i++)
			{
				pop[g][i] = populacja[i1][i] + k * (populacja[i2][i] - populacja[i3][i]);
				range_check(pop, g, i, l, r);
			}
		}
		sort_B(pop, n, F, f, psize, max);
		for (int g = 0; g < psize; g++)
		{
			double r{};
			for (int i = 0; i < n; i++)
			{
				r = P(mt);
				if (r >= pk)
				{
					nowa_populacja[g][i] = populacja[g][i];
				}
				else
				{
					nowa_populacja[g][i] = pop[g][i];
				}
			}
		}
		sort_B(nowa_populacja, n, F, f, psize, max);
		for (int i = 0; i < psize; i++)
		{
			for (int j = 0; j < n; j++)
			{
				pop[i][j] = populacja[i][j];
			}
		}
		int i = 0, j = 0;
		for (int k = 0; k < psize; k++)
		{
			if (F(f, pop[i], n, max) > F(f, nowa_populacja[j], n, max))
			{
				for (int z = 0; z < n; z++)
				{
					populacja[k][z] = pop[i][z];
				}
			}
			else
			{
				for (int z = 0; z < n; z++)
				{
					populacja[k][z] = nowa_populacja[j][z];
				}
			}
		}
	}
	for (int i = 0; i < psize; i++)
	{
		cout << "x[" << i << "]: (";
		for (int j = 0; j < n; j++)
		{
			if (j != n - 1)
				cout << populacja[i][j] << ", ";
			else
				cout << populacja[i][j];
		}
		cout << ")\n";
		delete[] populacja[i];
		delete[] nowa_populacja[i];
		delete[] pop[i];
	}
	delete[] populacja;
	delete[] nowa_populacja;
	delete[] pop;
}

double L(double B, double y, double s)
{
	if (0 < B && B < s)
	{
		return sqrt(y / (2 * M_PI)) * (exp(-y / (2 * (B - s))) / (pow((B - s), 3 / 2)));
	}
	return 0.0;
}

void Algorytm_Kukulki(int n, double (*f)(double x[], int n), double l, double r, double s, double y, double pa, int psize, bool max, int ilosc_iteracji)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> RNG(l, r);
	uniform_real_distribution<double> P(0, 1);
	double** populacja = new double* [psize];
	double** nowa_populacja = new double* [psize];
	double** pop = new double* [psize];
	for (int i = 0; i < psize; i++)
	{
		populacja[i] = new double[n];
		nowa_populacja[i] = new double[n];
		pop[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			populacja[i][j] = RNG(mt);
		}
	}
	sort_B(populacja, n, F, f, psize, max);
	for (int t = 0; t < ilosc_iteracji; t++)
	{
		for (int g = 0; g < psize; g++)
		{
			for (int i = 0; i < n; i++)
			{
				nowa_populacja[g][i]=populacja[g][i]+L(P(mt),y,s);
				range_check(nowa_populacja, g, i, l, r);
			}
		}

		sort_B(nowa_populacja, n, F, f, psize, max);
		for (int i = psize - 2; i < psize; i++)
		{
			double los = P(mt);
			if (los < pa)
			{
				for (int j = 0; j < n; j++)
				{
					nowa_populacja[i][j] = RNG(mt);
				}
			}
		}
		sort_B(nowa_populacja, n, F, f, psize, max);
		for (int i = 0; i < psize; i++)
		{
			for (int j = 0; j < n; j++)
			{
				pop[i][j] = populacja[i][j];
			}
		}
		int i = 0, j = 0;
		for (int k = 0; k < psize; k++)
		{
			if (F(f, pop[i], n, max) > F(f, nowa_populacja[j], n, max))
			{
				for (int z = 0; z < n; z++)
				{
					populacja[k][z] = pop[i][z];
				}
			}
			else
			{
				for (int z = 0; z < n; z++)
				{
					populacja[k][z] = nowa_populacja[j][z];
				}
			}
		}
	}

	for (int i = 0; i < psize; i++)
	{
		cout << "x[" << i << "]: (";
		for (int j = 0; j < n; j++)
		{
			if (j != n - 1)
				cout << populacja[i][j] << ", ";
			else
				cout << populacja[i][j];
		}
		cout << ")\n";
		delete[] populacja[i];
		delete[] nowa_populacja[i];
		delete[] pop[i];
	}
	delete[] populacja;
	delete[] nowa_populacja;
	delete[] pop;
}

int main()
{
	double (*fun1)(double[], int) = Rastragin;
	double (*fun2)(double[], int) = Sphere;
	cout << "---Algorytm genetyczny---\n";
	cout << "Minimum funkcji Rastragin'a\n";
	Algorytm_Genetyczny(10, fun1, -10, 10, 0.1, 1, 4, false, 10000);
	cout << "Minimum funkcji Sphere\n";
	Algorytm_Genetyczny(10, fun2, -10, 10, 0.1, 1, 4, false, 10000);
	cout << "Maksimum funkcji Rastragin'a\n";
	Algorytm_Genetyczny(10, fun1, -10, 10, 0.1, 1, 4, true, 10000);
	cout << "Maksimum funkcji Sphere\n";
	Algorytm_Genetyczny(10, fun2, -10, 10, 0.1, 1, 4, true, 10000);
	
	cout << "\n---Algorytm Ewolucji Roznicowej---\n";
	cout << "Minimum funkcji Rastragin'a\n";
	Algorytm_Ewolucji_Roznicowej(10, fun1, -10, 10, 0.5, 0.5, 4, false, 10000);
	cout << "Minimum funkcji Sphere\n";
	Algorytm_Ewolucji_Roznicowej(10, fun2, -10, 10, 0.5, 0.5, 4, false, 10000);
	cout << "Maksimum funkcji Rastragin'a\n";
	Algorytm_Ewolucji_Roznicowej(10, fun1, -10, 10, 0.5, 0.5, 4, true, 10000);
	cout << "Maksimum funkcji Sphere\n";
	Algorytm_Ewolucji_Roznicowej(10, fun2, -10, 10, 0.5, 0.5, 4, true, 10000);

	cout << "\n---Algorytm Kukulki---\n";
	cout << "Minimum funkcji Rastragin'a\n";
	Algorytm_Kukulki(10, fun1, -10, 10, 1, 1, 0.6, 4, false, 10000);
	cout << "Minimum funkcji Sphere\n";
	Algorytm_Kukulki(10, fun2, -10, 10, 1, 1, 0.6, 4, false, 10000);
	cout << "Maksimum funkcji Rastragin'a\n";
	Algorytm_Kukulki(10, fun1, -10, 10, 1, 1, 0.6, 4, true, 10000);
	cout << "Maksimum funkcji Sphere\n";
	Algorytm_Kukulki(10, fun2, -10, 10, 1, 1, 0.6, 4, true, 10000);

}
