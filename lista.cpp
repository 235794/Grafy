#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

// struktura opisujaca krawedzie
struct edge 
{
  int v1, v2, waga;
};

// klasa opisujaca parametry grafu
class parametry 
{
  public:
  int wierzcholki, krawedzie;
  float gestosc;
};

// tworzenie grafu na listy sasiedztwa
class graf : public parametry 
{
  vector<vector<int> > lista;
  vector<vector<int> > wagi;

public:
    graf() 
 {
    wierzcholki = 0;
    gestosc = 0;
    krawedzie = 0;
  }

    graf(int v, float d) 
 {
    wierzcholki = v;
    gestosc = d;
    krawedzie = gestosc * wierzcholki * (wierzcholki - 1) / 2;
    vector<int> temp;

    for (int i = 0; i < wierzcholki; i++)
      wagi.push_back(temp);

    for (int i = 0; i < wierzcholki; i++)
      lista.push_back(temp);
  }
 
// funkcja do zapelniania grafu losowymi wartosciami
  void start() 
  {
    int k = krawedzie, kk=0;
    int **matrix;
    matrix = new int *[lista.size()];

    for (int i = 0; i < wierzcholki; i++)
      matrix[i] = new int[wierzcholki]{0};

    for (int i = 0; i < wierzcholki; i++)
     for (int j = 0; j < wierzcholki; j++)
     {
       if (j > i)
         matrix[i][j] = 1 + rand() % 100;
       if (matrix[i][j] != 0)
	{
         kk++;
         lista[i].push_back(j);
         lista[j].push_back(i);
         wagi[i].push_back(matrix[i][j]);
         wagi[j].push_back(matrix[i][j]);
	}
      }

   krawedzie = kk;
   for (int i = 0; i < wierzcholki; i++)
      delete matrix[i];

   delete matrix;
  }


  void add_merge(int i, int j, int w) 
 {
    if (wierzcholki >= i && wierzcholki >= j) {
      bool exist = false;
      for (unsigned int k = 0; k < lista[i].size(); k++)
        if (lista[i][k] == j)
          exist = true;

      if (!exist) {
        krawedzie++;
        lista[i].push_back(j);
        wagi[i].push_back(w);

        lista[j].push_back(i);
        wagi[j].push_back(w);
      }
    }
  }

 
// funkcje prawdzajace czy graf jest polaczony

  void visited(vector<bool> &vis, int i) 
 {
    vis[i] = true;

    for (int j = 0; j < lista[i].size(); j++)
      if (!vis[lista[i][j]])
        visited(vis, lista[i][j]);
  }

  bool stopp() {
    bool result = true;
    vector<bool> vis;
    for (int i = 0; i < wierzcholki; i++)
      vis.push_back(false);
    visited(vis, 0);

    for (int i = 0; i < wierzcholki; i++)
      result &= vis[i];

    return result;
  }

  bool polaczenie(int one, int two) {
    if (one > two) {
      int DD = one;
      one = two;
      two = DD;
    }
    vector<bool> vis;
    for (int i = 0; i < wierzcholki; i++)
      vis.push_back(false);

    visited(vis, one);

    return vis[two];
  }

// funkcja sortujaca
  void quicksort_edge(vector<edge> &tab, int first, int last) 
 {
    int i = first;
    int j = last;
    int DD;

    int pivot = tab[(first + last) / 2].waga;
    do {
      while (tab[i].waga < pivot)
        i++;

      while (tab[j].waga > pivot)
        j--;

      if (i <= j) {
        DD = tab[i].v1;
        tab[i].v1 = tab[j].v1;
        tab[j].v1 = DD;

        DD = tab[i].v2;
        tab[i].v2 = tab[j].v2;
        tab[j].v2 = DD;

        DD = tab[i].waga;
        tab[i].waga = tab[j].waga;
        tab[j].waga = DD;

        i++;
        j--;
      }
    } while (i <= j);

    if (first < j)
      quicksort_edge(tab, first, j);
    if (i < last)
      quicksort_edge(tab, i, last);
  }

  void sort(vector<edge> &tab) 
  {
    if (tab.size())
      quicksort_edge(tab, 0, tab.size() - 1);
  }


//alkorytm kruskala
  void kruskal() 
  {
    // zainicjowanie pustego drzewa T
    graf T(lista.size(), 0);
    // kolejka ze wszystkimi krawedziami
    vector<edge> Q;
    edge DD;
    for (int i = 0; i <lista.size(); i++)
      for (int j = 0; j < lista[i].size(); j++) {
        if ((int)i < lista[i][j]) {
          DD.v1 = i;
          DD.v2 = lista[i][j];
          DD.waga = wagi[i][j];
          Q.push_back(DD);
        }
      }
    // sortowanie krawedzi wzgledem wagi
   sort(Q);

   // petla wykonuje sie az nie powstanie minimalne drzewo rozpinajace
    do 
    {
      // usuwanie z kolejki
      Q.erase(Q.begin());
      // sprawdzamy czy klastry sie lacza
      if (!T.polaczenie(Q[0].v1, Q[0].v2)) 
      {
        T.add_merge(Q[0].v1, Q[0].v2, Q[0].waga);
      }
    } while (Q.size() && !T.stopp());
  }


// algorytm prima
  void prim() 
 {
    // stworzenie pustego grafu
    graf T(wierzcholki, 0);
    bool *done;
    done = new bool[lista.size()];
    for (int i = 0; i < lista.size(); i++)
      done[i] = false;

    done[0] = true;

    // kolejka priorytetowa Q
    vector<edge> Q;
    edge DD;

    // dodanie polaczen do kolejki
    for (int i = 0; i < lista[0].size(); i++) 
      {
        DD.v1 = 0;
        DD.v2 = lista[0][i];
        DD.waga = wagi[0][i];
        Q.push_back(DD);
      }


     sort(Q);

    // petla wykonuje sie az koleja nie bedzie pusta
    do 
   {
      Q.erase(Q.begin());
      if (!done[Q[0].v2]) 
       {
        T.add_merge(Q[0].v1, Q[0].v2, Q[0].waga);
        done[Q[0].v2] = true;

        for (int j = 0; j < lista[Q[0].v2].size(); j++) 
        {
            DD.v1 = Q[0].v2;
            DD.v2 = lista[Q[0].v2][j];
            DD.waga = wagi[Q[0].v2][j];
            Q.push_back(DD);
        }
      }

    } while (Q.size());
    delete[] done;
  }


};

