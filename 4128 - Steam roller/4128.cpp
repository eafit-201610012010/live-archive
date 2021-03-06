/*
  Solo lectura
 */
#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

int main(){
  int r, c, i, j, w, C = 1;
  while (scanf("%d %d", &r, &c) && r + c){
    int start, end;
    scanf("%d %d", &i, &j); --i, --j;
    start = i*c + j;
    scanf("%d %d", &i, &j); --i, --j;
    end = i*c + j;

    //g[3] contiene la lista de vecinos del nodo 3 (El primer nodo es el 0!)
    //Cada vector de vecinos tiene cuatro elementos: abajo, izquierda, arriba, derecha = 0, 1, 2, 3
    //cada vecino es una pareja de enteros donde "first" es la distancia del viaje
    //y "second" es el nodo de destino (-1 si está fuera del tablero).
    vector<vector<pair<int, int> > > g(r*c, vector<pair<int, int> >(4, make_pair(0, -1)));

    for (i = 0; i<r; ++i){
      for (j = 0; j < c - 1; ++j){ //Horizontales
	scanf("%d", &w);
	g[i*c + j][3] = make_pair(w, i*c + j + 1);
	g[i*c + j + 1][1] = make_pair(w, i*c + j);
      }

      for (j = 0; j < c && (i+1)*c + j < r*c; ++j){
	scanf("%d", &w);
	g[i*c + j][0] = make_pair(w, (i+1)*c + j);
	g[(i+1)*c + j][2] = make_pair(w, i*c + j);
      }
    }
    //Ya el grafo está leído.
    printf("Case %d: ", C++);
    printf("\n");
  }
  return 0;
}
