#include <iostream>
#include <string>
#include <fstream>
using namespace std;


/*
---Algorytm Naiwny---

Dane wczytywane z pliku input_n.txt:
W 1 linijce wzorzec
Pozostala zawartosc pliku to tekst
przykladowe dane:

nie
wyszukiwanie wzorca

*/
void N()
{
	fstream in("input_n.txt");
	string w, t, tmp;
	int count;
	in >> w;
	while (!in.eof())
	{
		in >> tmp;
		t += tmp;
	}
	for (int i = 0; i < t.length()-w.length(); i++)
	{
		count = 0;
		for (int x = 0; x < w.length(); x++)
		{
			if (w[x] == t[i + x])
			{
				count++;
			}
			else
			{
				break;
			}
		}
		if (count == w.length())
		{
			cout << "Znaleziono wzorzec: \"" << w << "\" na pozycji: " << i << "\n";
		}
	}
}

int min(int a, int b)
{
	if (a > b) return b;
	return a;
}

/*
---Algorytm Boyer-Moore---

Dane wczytywane z pliku input_bm.txt:
W 1 linijce wzorzec
Pozostala zawartosc pliku to tekst
przykladowe dane:

origami
abacoadefgababgbmiaborigami

*/

void BoyerMoore()
{
	fstream in("input_bm.txt");
	string w, t, tmp;
	in >> w;
	bool quit = false;
	while (!in.eof())
	{
		in >> tmp;
		t += tmp;
	}
	int wystapienia[255]{};
	for (int i = 0; i < w.length(); i++)
	{
		wystapienia[static_cast<int>(w[i])] = i + 1;
	}
	for (int i = w.length() - 1; i < t.length() - 1;)
	{
		for (int j = w.length() - 1; j >= 0;)
		{
			if (w[j] == t[i])
			{
				if (j == 0)
				{
					cout << "Znaleziono wzorzec: \"" << w << "\" na pozycji: " << i << "\n";
					quit = true;
					break;
				}
				else
				{
					j--;
					i--;
				}
			}
			else
			{
				i += w.length() - min(j, wystapienia[static_cast<int>(t[i])]);
				j = w.length() - 1;
			}
		}
		if (quit)
			break;
	}
}

/*
---Algorytm Karpa-Rabina---

Dane wczytywane z pliku input_kr.txt:
W 1 linijce wzorzec
Pozostala zawartosc pliku to tekst
przykladowe dane:

BACA
AEDBACA

*/

void KarpRabin()
{
	fstream in("input_kr.txt");
	string w, t, tmp;
	in >> w;
	while (!in.eof())
	{
		in >> tmp;
		t += tmp;
	}
	int hw{}, ht{};
	int values[255]{};
	int v = 1;
	for (int i = 0; i < w.length(); i++)
	{
		if (values[static_cast<int>(w[i])] == 0)
		{
			values[static_cast<int>(w[i])] = v;
			v++;
		}
	}
	for (int i = 0; i < t.length(); i++)
	{
		if (values[static_cast<int>(t[i])] == 0)
		{
			values[static_cast<int>(t[i])] = v;
			v++;
		}
	}
	v--;
	for (int i = 0; i < w.length(); i++)
	{
		hw += (values[static_cast<int>(w[i])]) * pow(v, w.length() - 1 - i);
	}
	hw = hw % 19;
	for (int i = 0; i < w.length(); i++)
	{
		ht += (values[static_cast<int>(t[i])]) * pow(v, w.length() - 1 - i);
	}
	if ((ht % 19) == hw)
	{
		if (t.substr(0, w.length()) == w)
		{
			cout << "Znaleziono wzorzec: \"" << w << "\" na pozycji 0\n";
		}
	}
	for (int i = 1; i < t.length() - w.length() + 1; i++)
	{
		ht -= (values[static_cast<int>(t[i - 1])] * pow(v, w.length() - 1));
		ht *= v;
		ht += values[static_cast<int>(t[i + w.length() - 1])];
		if ((ht % 19) == hw)
		{
			if (t.substr(i, w.length()) == w)
			{
				cout << "Znaleziono wzorzec: \"" << w << "\" na pozycji " << i << "\n";
				break;
			}
		}
	}
}

int main()
{
	cout << "---Algorytm naiwny---\n";
	N();
	cout << "---Algorytm Boyera-Moore'a---\n";
	BoyerMoore();
	cout << "---Algorytm Karpa-Rabina---\n";
	KarpRabin();
}
