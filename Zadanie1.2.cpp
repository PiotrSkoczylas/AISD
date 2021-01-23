/*
Dane wejsciowe pobierane sa z pliku input1.2.txt
W pierwszej znajduje sie informacja o operacji do wykonania:
ini_to_post lub post_to_ini
W 2 lini znajduja sie dane do przetworzenia skladajace sie z wymienionych znakow: [0,1,2,3,4,5,6,7,8,9,*,/,+,-,^]
W pliku moze znalezc sie wiele zestawow danych.
Przykladowe dane:

ini_to_post
4*(5-6/3+1)^2
post_to_ini
4563/-1+2^*


*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

std::string i_to_p(string input)
{
	string result{}, stack{};
	for (int i = 0; i < input.length(); i++)
	{
		if (static_cast<int>(input[i]) >= 48 && static_cast<int>(input[i]) <= 57)
		{
			result += input[i];
		}
		else
		{
			if (stack.empty())
			{
				stack = input[i];
				continue;
			}
			if (input[i] == '(')
			{
				stack = input[i] + stack;
				continue;
			}
			if (input[i] == ')')
			{
				for (int c = 0; c < stack.length(); c++)
				{
					if (stack[0] != '(')
					{
						result += stack[0];
						stack.erase(0, 1);
					}
					else
					{
						break;
					}
				}
			}
			if (input[i] == '^')
			{
				stack = input[i] + stack;
				continue;
			}
			if (input[i] == '/' || input[i] == '*')
			{
				if (stack[0] != '^')
				{
					stack = input[i] + stack;
					continue;
				}
				else
				{
					for (int c = 0; c < stack.length(); c++)
					{
						if (stack[0] != '(')
						{
							result += stack[0];
							stack.erase(0, 1);
						}
						else
						{
							break;
						}
					}
					stack = input[i] + stack;
				}
			}
			if (input[i] == '+' || input[i] == '-')
			{
				if (stack[0] != '^' && stack[0] != '/' && stack[0] != '*')
				{
					stack = input[i] + stack;
				}
				else
				{
					for (int c = 0; c < stack.length(); c++)
					{
						if (stack[0] != '(')
						{
							result += stack[0];
							stack.erase(0, 1);
						}
						else
						{
							break;
						}
					}
					stack = input[i] + stack;
				}
			}
		}
	}
	for (int i = 0; i < stack.length(); i++)
	{
		if (stack[i] != '(')
			result += stack[i];
	}
	return result;
}

std::string p_to_i(string input)
{
	string result{};
	string* stack = new string[input.length()];
	int index{};
	for (int i = 0; i < input.length(); i++)
	{
		if (static_cast<int>(input[i]) >= 48 && static_cast<int>(input[i]) <= 57)
		{
			stack[index] = input[i];
			index++;
		}
		else
		{
			if (index >= 2)
			{
				bool added = false;
				for (int c = index - 1; c >= 0 && !added; c--)
				{
					if (!(stack[c].length() <= 1 && !(static_cast<int>(stack[c][0]) >= 48 && static_cast<int>(stack[c][0]) <= 57)))
					{
						for (int x = c - 1; x >= 0 && !added; x--)
						{
							if (!(stack[x].length() <= 1 && !(static_cast<int>(stack[x][0]) >= 48 && static_cast<int>(stack[x][0]) <= 57)))
							{
								result = "(" + stack[x] + input[i] + stack[c] + ")";
								stack[x] = "";
								stack[c] = "";
								index--;
								for (int v = 0; v < index-1; v++)
								{
									if (stack[v] == "" && stack[v + 1] != "")
									{
										stack[v] = stack[v + 1];
										stack[v + 1] = "";
									}
								}
								stack[index-1] = result;
								added = true;
							}
						}
					}
				}
				if(!added)
				{
					stack[index] = input[i];
					index++;
				}
			}
			else
			{
				stack[index] = input[i];
				index++;
			}
		}
	}
	result = "";
	for (int i = 0; i < index; i++)
		result += stack[i];
	delete[] stack;
	return result;
}

int main()
{
	string input{};
	fstream in;
	in.open("input1.2.txt");
	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> input;
			if (input == "ini_to_post")
			{
				in >> input;
				cout << i_to_p(input) << "\n";
			}
			else
			{
				if (input == "post_to_ini")
				{
					in >> input;
					cout << p_to_i(input) << "\n";
				}
			}
		}
	}
	else
	{
		cout << "Nie udalo sie otworzyc pliku\n";
	}
	return 0;
}