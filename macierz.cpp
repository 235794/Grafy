#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

// struktura opisujaca krawedzie
struct edge_matrix 
{
  int v1, v2, waga;
};

// klasa opisujaca parametry grafu
class parametry_matrix 
{
  public:
  int wierzcholki, krawedzie;
  float gestosc;
};

// tworzenie grafu na macierzy sasiedztwa
class graf_matrix : public parametry_matrix 
{
  int **matrix;

public:
    graf_matrix() 
 {
    wierzcholki = 0;
    gestosc = 0;
    krawedzie = 0;
  }

    graf_matrix(int v, float d) 
 {
    wierzcholki = v;
    gestosc = d;
    krawedzie = gestosc * wierzcholki * (wierzcholki - 1) / 2;

    matrix = new int *[wierzcholki];
    for (int i = 0; i < wierzcholki; i++)
      matrix[i] = new int[wierzcholki];

    for (int i = 0; i < wierzcholki; i++)
      for (int j = 0; j < wierzcholki; j++)
        matrix[i][j] = 0;
  }
 
// funkcja do zapelniania grafu losowymi wartosciami
  void start_matrix() 
  {
    int k = krawedzie, kk=0;

    for (int i = 0; i < wierzcholki; i++)
     for (int j = 0; j < wierzcholki; j++)
     {
       if (j > i)
         matrix[i][j] = 1 + rand() % 100;
       if (matrix[i][j] != 0)
         kk++;
      }

   krawedzie = kk;
  }


  void add_merge_matrix(int i, int j, int w) {
    if (!matrix[i][j])
      krawedzie++;

    if (j > i)
      matrix[i][j] = w;
    else
      matrix[j][i] = w;
  }

 
// funkcje prawdzajace czy graf jest polaczony

  void visited_matrix(vector<bool> &vis, int i) {
    vis[i] = true;

    for (int j = 0; j < wierzcholki; j++)
      if (matrix[i][j] && !vis[j])
        visited_matrix(vis, j);
  }

  bool stopp_matrix() {
    bool result = true;
    vector<bool> vis;
    for (int i = 0; i < wierzcholki; i++)
      vis.push_back(false);
    visited_matrix(vis, 0);

    for (int i = 0; i < wierzcholki; i++)
      result &= vis[i];

    return result;
  }

  bool polaczenie_matrix(int one, int two) {
    if (one > two) {
      int DD = one;
      one = two;
      two = DD;
    }
    vector<bool> vis;
    for (int i = 0; i < wierzcholki; i++)
      vis.push_back(false);

    visited_matrix(vis, one);

    return vis[two];
  }

// funkcja sortujaca
  void quicksort_edge_matrix(vector<edge_matrix> &tab, int first, int last) 
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
      quicksort_edge_matrix(tab, first, j);
    if (i < last)
      quicksort_edge_matrix(tab, i, last);
  }

  void sort_matrix(vector<edge_matrix> &tab) 
  {
    if (tab.size())
      quicksort_edge_matrix(tab, 0, tab.size() - 1);
  }


//alkorytm kruskala
  void kruskal_matrix() 
  {
    // zainicjowanie pustego drzewa T
    graf_matrix T(wierzcholki, 0);
    // kolejka ze wszystkimi krawedziami
    vector<edge_matrix> Q;
    edge_matrix DD;
    for (int i = 0; i < wierzcholki; i++)
      for (int j = 0; j < wierzcholki; j++) {
        if (matrix[i][j]) {
          DD.v1 = i;
          DD.v2 = j;
          DD.waga = matrix[i][j];
          Q.push_back(DD);
        }
      }
    // sortowanie krawedzi wzgledem wagi
   sort_matrix(Q);

   // petla wykonuje sie az nie powstanie minimalne drzewo rozpinajace
    do 
    {
      // usuwanie z kolejki
      Q.erase(Q.begin());
      // sprawdzamy czy klastry sie lacza
      if (!T.polaczenie_matrix(Q[0].v1, Q[0].v2)) 
      {
        T.add_merge_matrix(Q[0].v1, Q[0].v2, Q[0].waga);
      }
    } while (Q.size() && !T.stopp_matrix());
  }


// algorytm prima
  void prim_matrix() 
 {
    // stworzenie pustego grafu
    graf_matrix T(wierzcholki, 0);
    bool *done;
    done = new bool[wierzcholki];
    for (int i = 0; i < wierzcholki; i++)
      done[i] = false;

    done[0] = true;

    // kolejka priorytetowa Q
    vector<edge_matrix> Q;
    edge_matrix DD;

    // dodanie polaczen do kolejki
    for (int i = 0; i < wierzcholki; i++) 
   {
      if (matrix[0][i]) 
      {
        DD.v1 = 0;
        DD.v2 = i;
        DD.waga = matrix[0][i];
        Q.push_back(DD);
      }
    }


     sort_matrix(Q);

    // petla wykonuje sie az koleja nie bedzie pusta
    do 
   {
      Q.erase(Q.begin());
      if (!done[Q[0].v2]) 
       {
        T.add_merge_matrix(Q[0].v1, Q[0].v2, Q[0].waga);
        done[Q[0].v2] = true;

        for (int j = 0; j < wierzcholki; j++) 
        {
          if (matrix[Q[0].v2][j]) 
          {
            DD.v1 = Q[0].v2;
            DD.v2 = j;
            DD.waga = matrix[Q[0].v2][j];
            Q.push_back(DD);
          }
        }
      }

    } while (Q.size());
    delete[] done;
  }


};

