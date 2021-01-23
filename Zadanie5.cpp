#include <iostream>
#include <fstream>

using namespace std;


/*
---Szyfr Cezara---
Dane wejsciowe pobierane z pliku "input_cesar.txt"
w pierwszej linii znajduje sie liczba calkowita - przesuniecie
reszta pliku to tekst do zakodowania
Przykladowe dane:
-4
to jest teKst aa BAzzAZXxY
*/

void Cesar()
{
	fstream in("input_cesar.txt");
	int mv;
	in >> mv;
	string t,tmp,o;
	while (!in.eof())
	{
		in >> tmp;
		t += tmp + " ";
	}
	o = t;
	for (int i = 0; i < t.length(); i++)
	{
		if (static_cast<int>(t[i]) <= 90 && static_cast<int>(t[i]) >= 65)
		{
			o[i] = (static_cast<int>(o[i]) + mv);
			if (o[i] > 90)
			{
				o[i] = o[i] % 90 + 64;
			}
			else if(o[i] < 65)
			{
				o[i] = 90 + o[i] - 64;
			}
		}
		else
		{
			if (static_cast<int>(t[i]) <= 122 && static_cast<int>(t[i]) >= 97)
			{
				o[i] = (static_cast<int>(o[i]) + mv);
				if (o[i] > 122)
				{
					o[i] = o[i] % 122 + 96;
				}
				else if (o[i] < 97)
				{
					o[i] = 122 + o[i] - 96;
				}
			}
		}
	}
	cout << "Przed zakodowaniem:\n" << t << "\nPo zakodowaniu:\n" << o << "\n";
}


struct v
{
	string l;
	double p;
	string code;
};

struct tree
{
	v current;
	tree* left;
	tree* right;
};

void code(tree* t, string c)
{
	if (t)
	{
		if (t->current.l != "")
		{
			cout << t->current.l << " " << c<<"\n";
		}
		code(t->left, c + "0");
		code(t->right, c + "1");
	}
}

/*
---Kod Huffmana---
Dane wejsciowe pobierane z pliku "input_huffman.txt"
w pierwszej linii znajduje sie liczba calkowita - ilosc znakow w alfabecie (n)
w nastepnie rozdielane spacjami litery i prawdopodobienstwa wystapien
wartosci sa posortowane wedlug prawdopodobienstw nierosnaco
Przykladowe dane:
5
C 0.4 E 0.2 B 0.2 D 0.1 A 0.1

*/

void Huffman()
{
	fstream in("input_huffman.txt");
	int n{};
	in >> n;
	string tmp1{};
	int tmp2{};
	string* t = new string[n];
	double* p = new double[n];
	for (int i = 0; i < n; i++)
	{
		in >> t[i];
		in >> p[i];
	}
	tree* tr = new tree();
	tr->left = new tree();
	tr->right = new tree();
	tr->left->current.l = t[n-1];
	tr->left->current.p = p[n-1];
	tr->right->current.l = t[n - 2];
	tr->right->current.p = p[n - 2];
	tr->current.p = p[n - 2] + p[n - 1];
	for (int i = n - 3; i >= 0; i--)
	{
		tree* tmp = new tree();
		if (tr->current.p >= p[i])
		{
			tmp->left = tr;
			tmp->right = new tree();
			tmp->right->current.l = t[i];
			tmp->right->current.p = p[i];
		}
		else
		{
			tmp->right = tr;
			tmp->left = new tree();
			tmp->left->current.l = t[i];
			tmp->left->current.p = p[i];
		}
		tmp->current.p = tmp->left->current.p + tmp->right->current.p;
		tr = tmp;
	}
	code(tr, "");
}

int findOptimalSplit(double p[],int start, int end)
{
	double optimalnow=p[start];
	int indexnow=start+1;
	double sum{};
	for (int i = start; i < end; i++)
	{
		sum += p[i];
	}
	for (int i = start + 1; i < end; i++)
	{
		if (abs(optimalnow + p[i] - (sum / 2)) < abs(optimalnow - (sum / 2)))
		{
			optimalnow += p[i];
			indexnow = i+1;
		}
		else
		{
			break;
		}
	}
	return indexnow;
}

void scode(string t[], double p[],int start, int end, string c,int n)
{
	if (end == start)
	{
		cout << t[start] << " " << c << "\n";
	} else
	if (end - start == 2)
	{
		cout << t[start] << " " << c << "0\n";
		cout << t[start + 1] << " " << c << "1\n";
	}
	else
	{
		scode(t, p, start, findOptimalSplit(p, start, end) - 1, c + "0",n);
		scode(t, p, findOptimalSplit(p, start, end), end, c + "1",n);
	}
}

/*
---Kod Shannona-Fano---
Dane wejsciowe pobierane z pliku "input_sf.txt"
w pierwszej linii znajduje sie liczba calkowita - ilosc znakow w alfabecie (n)
w nastepnie rozdielane spacjami litery i prawdopodobienstwa wystapien
wartosci sa posortowane wedlug prawdopodobienstw nierosnaco
Przykladowe dane:
5
C 0.4 B 0.2 E 0.2 A 0.1 D 0.1

*/

void ShannonFano()
{
	fstream in("input_sf.txt");
	int n{};
	in >> n;
	string tmp1{};
	int tmp2{};
	string* t = new string[n];
	double* p = new double[n];
	for (int i = 0; i < n; i++)
	{
		in >> t[i];
		in >> p[i];
	}
	int split = findOptimalSplit(p, 0, n);
	scode(t, p, 0, split, "0",n);
	scode(t, p, split+1, n, "1",n);
}

int main()
{
	cout << "---Szyfr Cezara---\n";
	Cesar();
	cout << "---Kod Huffmana---\n";
	Huffman();
	cout << "---Kod Shannona-Fano---\n";
	ShannonFano();
}