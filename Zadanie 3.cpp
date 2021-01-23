#include <iostream>
#include <queue>
#include <fstream>
#include <vector>

using namespace std;

struct G {
	int v;
	int k;
	int pred;
	int h;
};

struct Porownanie {
	bool operator()(G g1, G g2)
	{
		if (g1.k > g2.k)
			return true;
		if (g1.k < g2.k)
			return false;

		return false;
	}
};

struct PorownanieA {
	bool operator()(G g1, G g2)
	{
		if (g1.k + g1.h > g2.k + g2.h)
			return true;
		if (g1.k + g1.h < g2.k + g2.h)
			return false;

		return false;
	}
};
/*
---Algorytm Prima---

Dane wczytywane z pliku input_prim.txt:
w 1 linijce ilosc wierzcholkow - v
w kazdej z pozostalych v linii po v elementow (przyklad w linii 1 droga z 1 do 1, z 1 do 2, itd...)
elementy w postaci wag - dla braku drogi podajemy wartosc 0
wierzcholkiem startowym jest ten podany jako pierwszy
przykladowe dane:
5
0 2 4 0 1
2 0 3 0 0
4 3 0 2 2
0 0 2 0 3
1 0 2 3 0

lub

5
0 3 0 3 5
3 0 5 1 0
0 5 0 2 0
3 1 2 0 1
5 0 0 1 0
*/
void Prim()
{
	int v;
	fstream in("input_prim.txt");
	priority_queue<G, vector<G>, Porownanie> pq{};
	priority_queue<G, vector<G>, Porownanie> pq2{};
	in >> v;
	G* g = new G[v];
	int** E = new int*[v];
	for (int i = 0; i < v; i++)
	{
		(g + i)->pred = -1;
		(g + i)->k = INT_MAX;
		(g + i)->v = i;
		E[i] = new int[v];
		for (int x = 0; x < v; x++)
		{
			in >> E[i][x];
		}
	}
	g->k = 0;
	g->pred = 0;
	for (int i = 0; i < v; i++)
	{
		pq.push(g[i]);
	}
	while (!pq.empty())
	{
		G current = pq.top();
		pq.pop();
		while (!pq.empty())
		{
			G tmp = pq.top();
			pq.pop();
			if (E[current.v][tmp.v] != 0)
			{
				if (E[current.v][tmp.v] < tmp.k)
				{
					tmp.pred = current.v;
					tmp.k = E[current.v][tmp.v];
				}
			}
			pq2.push(tmp);
		}
		(g + current.v)->k = current.k;
		(g + current.v)->pred = current.pred;
		while (!pq2.empty())
		{
			pq.push(pq2.top());
			pq2.pop();
		}
	}
	cout << "";
	for (int i = 0; i < v; i++)
	{
		cout << "numer wierzcholka: " << (g + i)->v + 1 << " poprzednik: " << (g + i)->pred + 1 << " koszt: " << (g + i)->k << "\n";
	}
	in.close();
	for (int i = 0; i < v; i++)
	{
		delete[] E[i];
	}
	delete[] E;
	delete[] g;
}

/*
---Algorytm Dijkstry---

Dane wczytywane z pliku input_dijkstra.txt:
w 1 linijce ilosc wierzcholkow - v
w kazdej z pozostalych v linii po v elementow (przyklad w linii 1 droga z 1 do 1, z 1 do 2, itd...)
elementy w postaci wag - dla braku drogi podajemy wartosc 0
wierzcholkiem startowym jest ten podany jako pierwszy
przykladowe dane:
5
0 2 4 0 1
2 0 3 0 0
4 3 0 2 2
0 0 2 0 3
1 0 2 3 0

lub

5
0 3 0 3 5
3 0 5 1 0
0 5 0 2 0
3 1 2 0 1
5 0 0 1 0
*/
void Dijkstra()
{
	int v;
	fstream in("input_dijkstra.txt");
	priority_queue<G, vector<G>, Porownanie> pq{};
	priority_queue<G, vector<G>, Porownanie> pq2{};
	in >> v;
	G* g = new G[v];
	int** E = new int* [v];
	for (int i = 0; i < v; i++)
	{
		(g + i)->pred = -1;
		(g + i)->k = INT_MAX;
		(g + i)->v = i;
		E[i] = new int[v];
		for (int x = 0; x < v; x++)
		{
			in >> E[i][x];
		}
	}
	g->k = 0;
	g->pred = 0;
	for (int i = 0; i < v; i++)
	{
		pq.push(g[i]);
	}
	while (!pq.empty())
	{
		G current = pq.top();
		pq.pop();
		while (!pq.empty())
		{
			if (current.k == INT_MAX)
			{
				break;
			}
			G tmp = pq.top();
			pq.pop();
			if (E[current.v][tmp.v] != 0)
			{
				if (E[current.v][tmp.v] + current.k < tmp.k)
				{
					tmp.pred = current.v;
					tmp.k = E[current.v][tmp.v] + current.k;
				}
			}
			pq2.push(tmp);
		}
		(g + current.v)->k = current.k;
		(g + current.v)->pred = current.pred;
		while (!pq2.empty())
		{
			pq.push(pq2.top());
			pq2.pop();
		}
	}
	cout << "";
	for (int i = 0; i < v; i++)
	{
		if ((g + i)->k != INT_MAX)
		{
			cout << "numer wierzcholka: " << (g + i)->v + 1 << " poprzednik: " << (g + i)->pred + 1 << " koszt: " << (g + i)->k << "\n";
		}
		else
		{
			cout << "numer wierzcholka: " << (g + i)->v + 1 << " poprzednik: brak\n";
		}
	}
	in.close();
	for (int i = 0; i < v; i++)
	{
		delete[] E[i];
	}
	delete[] E;
	delete[] g;
}


/*
---Algorytm A*---

Dane wczytywane z pliku input_a.txt:
w 1 linijce ilosc wierzcholkow - v
w 2 linijce v wartosci h(v)
w kazdej z pozostalych v linii po v elementow (przyklad w linii 1 droga z 1 do 1, z 1 do 2, itd...)
elementy w postaci wag - dla braku drogi podajemy wartosc 0
wierzcholek poczatkowy to ten podany jako pierwszy, a docelowy ten podany jako ostatni
przykladowe dane:
8
4 8 3 4 5 2 1 0
0 5 0 1 0 0 0 0
0 0 2 0 1 0 0 0
0 0 0 0 0 0 0 3
0 0 0 0 1 2 0 0
0 0 4 0 0 0 0 0
4 0 0 0 0 0 2 0
0 0 0 0 1 0 0 1
0 0 0 0 2 0 0 0
*/
void A()
{
	int v;
	fstream in("input_a.txt");
	priority_queue<G, vector<G>, PorownanieA> Q{};
	priority_queue<G, vector<G>, PorownanieA> S{};
	priority_queue<G, vector<G>, PorownanieA> T{};
	priority_queue<G, vector<G>, PorownanieA> T2{};
	in >> v;
	int dst = v - 1;
	G* g = new G[v];
	int* h = new int[v];
	int** E = new int* [v];
	for (int i = 0; i < v; i++)
	{
		in >> h[i];
	}
	for (int i = 0; i < v; i++)
	{
		(g + i)->pred = -1;
		(g + i)->k = INT_MAX;
		(g + i)->v = i;
		(g + i)->h = h[i];
		E[i] = new int[v];
		for (int x = 0; x < v; x++)
		{
			in >> E[i][x];
		}
	}
	g->k = 0;
	g->pred = 0;
	Q.push(g[0]);
	while (!Q.empty())
	{
		S.push(Q.top());
		G current = Q.top();
		if (current.v == dst)
		{
			break;
		}
		Q.pop();
		for (int i = 1; i < v; i++)
		{
			if (E[current.v][i] != 0)
			{
				if (E[current.v][i] + h[i] + current.k < g[i].k)
				{
					bool inQ = false;
					bool inS = false;
					G tmp;
					while (!S.empty())
					{
						if (S.top().v == i)
						{
							inS = true;
							if (current.k + h[i] + E[current.v][i] < g[i].k)
							{
								g[i].pred = current.v;
								g[i].k = current.k + E[current.v][i];
								S.pop();
								S.push(g[i]);
							}
							break;
						}
						T2.push(S.top());
						S.pop();
					}
					while (!T2.empty())
					{
						S.push(T2.top());
						T2.pop();
					}
					if (inS)
					{
						continue;
					}
					while (!Q.empty())
					{
						if (Q.top().v == i)
						{
							inQ = true;
							if (current.k + h[i] + E[current.v][i] < g[i].k)
							{
								tmp = Q.top();
								Q.pop();
								tmp.k = current.k + E[current.v][i];
								tmp.pred = current.v;
								g[i] = tmp;
								Q.push(tmp);
							}
							break;
						}
						T.push(Q.top());
						Q.pop();
					}
					if (!inQ)
					{
						g[i].pred = current.v;
						g[i].k = current.k + E[current.v][i];
						Q.push(g[i]);
					}
					while (!T.empty())
					{
						Q.push(T.top());
						T.pop();
					}
				}
			}
		}
	}
	for (int i = 0; i < v; i++)
	{
		if ((g + i)->k != INT_MAX && i > 0)
		{
			cout << "numer wierzcholka: " << (g + i)->v + 1 << " poprzednik: " << (g + i)->pred + 1 << " g(v): " << (g + i)->k << "\n";
		}
		else
		{
			cout << "numer wierzcholka: " << (g + i)->v + 1 << " poprzednik: brak\n";
		}
	}
	in.close();
	for (int i = 0; i < v; i++)
	{
		delete[] E[i];
	}
	delete[] E;
	delete[] g;
	delete[] h;
}


/* 
---Algorytm Floyda-Warshalla---

Dane wczytywane z pliku input_floydwarshall.txt:
w 1 linijce ilosc wierzcholkow - v
w kazdej z pozostalych v linii po v elementow (przyklad w linii 1 droga z 1 do 1, z 1 do 2, itd...)
elementy w postaci wag - dla braku drogi podajemy wartosc 0
przykladowe dane:

7
0 1 5 0 0 0 0
0 0 2 0 0 0 0
0 0 0 0 0 0 0
7 0 0 0 1 0 0
0 0 0 0 0 1 0
2 0 0 4 0 0 0
6 0 0 0 0 3 0

*/
void FloydWarshall()
{
	int v;
	fstream in("input_floydwarshall.txt");
	in >> v;
	int** E = new int* [v];
	int** d = new int* [v];
	int** p = new int* [v];
	for (int i = 0; i < v; i++)
	{
		E[i] = new int[v];
		d[i] = new int[v];
		p[i] = new int[v];
		for (int x = 0; x < v; x++)
		{
			in >> E[i][x];
			if (E[i][x] != 0)
			{
				d[i][x] = E[i][x];
				p[i][x] = i;
			}
			else
			{
				d[i][x] = INT_MAX;
				p[i][x] = -1;
			}
		}
		d[i][i] = 0;
	}
	for (int u = 0; u < v; u++)
	{
		for (int x = 0; x < v; x++)
		{
			if (x != u)
			for (int w = 0; w < v; w++)
			{
				if (x != w && w != u)
				if (d[x][u] != 0 && d[x][u] != INT_MAX && d[u][w] != 0 && d[u][w] != INT_MAX)
				{
					if (d[x][u] + d[u][w] < d[x][w])
					{
						d[x][w] = d[x][u] + d[u][w];
						p[x][w] = p[u][w];
					}
				}
			}
		}
	}
	cout << "d:\n";
	for (int i = 0; i < v; i++)
	{
		for (int x = 0; x < v; x++)
		{
			cout.width(4);
			if (d[i][x] != INT_MAX)
				cout << d[i][x] << " ";
			else
				cout << " INF ";
		}
		cout << "\n";
	}
	cout << "\np:\n";
	for (int i = 0; i < v; i++)
	{
		for (int x = 0; x < v; x++)
		{
			cout.width(4);
			cout << p[i][x] + 1<< " ";
		}
		cout << "\n";
	}
	in.close();
	for (int i = 0; i < v; i++)
	{
		delete[] E[i];
		delete[] d[i];
		delete[] p[i];
	}
	delete[] E;
	delete[] d;
	delete[] p;
}

int main()
{
	cout << "---Algorytm Prima---\n\n";
	Prim();
	cout << "\n---Algorytm Dijkstry---\n\n";
	Dijkstra();
	cout << "\n---Algorytm A*---\n\n";
	A();
	cout << "\n---Algorytm Floyda-Warshalla---\n\n";
	FloydWarshall();

}