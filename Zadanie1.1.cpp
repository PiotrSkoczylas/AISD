/*
Dane wejsciowe pobierane sa z pliku input1.2.txt
Przykladowe dane:

11;4;2.3;8.1;9;15.2

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	string input{};
	fstream in;
	in.open("input1.1.txt");
	if (in.is_open())
	{
		in >> input;
		in.close();
		int delimiters{};
		for (int i = 0; i < input.length(); i++)
			if (input[i] == ';')
				delimiters++;
		double* tab = new double[delimiters + 1];
		string raw;
		for (int i = 0; i <= delimiters; i++)
		{
			raw = "";
			for (int c = 0; c < input.length(); c++)
			{
				if (input[c] == ';')
				{
					input.erase(0, c + 1);
					break;
				}
				raw += input[c];
			}
			tab[i] = stod(raw);
		}
		double max = tab[0];
		for (int i = 1; i <= delimiters; i++)
		{
			if (max < tab[i])
				max = tab[i];
		}
		cout << "Najwieksza wartosc w zbiorze: " << max << "\n";
		delete[] tab;
	}
	else
	{
		cout << "Nie udalo sie otworzyc pliku";
	}

	return 0;
}
