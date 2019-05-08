#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <chrono>
#include "lista.cpp"
#include "macierz.cpp"


int main(int argc, char *argv[]) 
{
  
    if(argc == 1) 	
    {
    cout << " M.PIETRAS \n PAMSI \n PROJEKT 2 - GRAFY \n WYWOLANIE: \n ./G metoda(0-lista/1-macierz) gestosc(25, 50, 75, 100) \n \n WYNIKIEM JEST SREDNI CZAS DLA 100 WYWOLAN W MS (DLA 10, 50, 100, 500 i 1000 WIERZCHOLKOW)" <<endl;
    exit(0);
    }

  const int metoda = atoi(argv[1]);     // metoda: 0-lista, 1-macierz
  float g = atoi(argv[2])/100.0;     // gestosc
  float czasy, t;
  srand(time(NULL)); // funkcja do losowania liczb losowych, time musi być, zeby zawsze były inne       


    int ile =100; 	// tyle jest powtorzen
    int w[5] = {10, 50, 100, 500, 1000};  // tyle jest wierzcholkow


    for(int i = 0; i < 5; i++)
    {
      czasy=0;
      for(int j=0; j<ile; j++) 
       {
       if (metoda == 1)  
	{
	graf_matrix G(w[i], g);
	G.start_matrix();

           auto tstart = std::chrono::system_clock::now();         
	   G.prim_matrix();
	   //G.kruskal_matrix();
           auto tend = std::chrono::system_clock::now();
           auto czas = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
           czasy = czasy+czas;
	}

       if (metoda == 0) 
	{
	graf G(w[i], g);
	G.start();
           auto tstart = std::chrono::system_clock::now();
           //G.prim();           
	   G.kruskal();
           auto tend = std::chrono::system_clock::now();
           auto czas = std::chrono::duration_cast<std::chrono::microseconds>(tend - tstart).count();
           czasy = czasy+czas;
           cout << czas << endl;
	}
      }

     t = czasy / ile;
     cout << w[i] << "	" << t << endl;

    }
}
