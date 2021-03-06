/*
  Memory limit exceeded
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>

using namespace std;


//#define debug true
#define debug false
#define dprintf !debug || printf

struct state{
  short i, time;
  int visited;
 bool operator < (const state &t) const {
   return time > t.time;
 }
 state(){}
 state(short I, int V, short T) : i(I), visited(V), time(T) {}
};
const int oo = INT_MAX / 2, deadline = 420;

int n;
short g[21][21];
short t[21];

bool visited[20][1<<20];

int popcount(int i){
 int mask = 1, ans = 0;
 while (mask){
   if (mask & i) ans++;
   mask <<= 1;
 }
 return ans;
}

int dijkstra(){
 priority_queue<state> q;

 for (int i=0; i<n; ++i){
   for (int j=0; j<(1<<n); ++j){
     visited[i][j] = false;
   }
 }


 for (int i=0; i<n; ++i){
   if (t[i] <= deadline){
     q.push(state(i, 1 << i, t[i]));
   }
 }

 int ans = 0;
 while (q.size()){
   int i = q.top().i;
   int v = q.top().visited;
   int w = q.top().time;

   q.pop();
   dprintf("popped %d, %x, %d\n", i, v, w);

   if (w > deadline) break;

   if (visited[i][v]) continue;

   int tmp = popcount(v);
   if (tmp > ans) ans = tmp;

   for (int k=0; k<n; ++k)
     if (i != k)
       if (!(v & (1 << k) )){
         int new_v = v | (1 << k);
         int new_w = w + g[i][k] + t[k];

         if (new_w <= deadline && !visited[k][new_v]){
           q.push(state(k, new_v, new_w));
           dprintf("  pushed %d, %x, %d\n", k, new_v, new_w);
         }
       }

 }

 return ans;
}

int main(){
 while (scanf("%d", &n)==1 && n){

   for (int i=0; i<n; ++i) scanf("%d", &t[i]);
   for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) scanf("%d", &g[i][j]);

   for (int k=0; k<n; ++k)
     for (int i=0; i<n; ++i)
       for (int j=0; j<n; ++j)
         g[i][j] = min((int)g[i][j], g[i][k] + g[k][j]);

   /*
   for (int i=0; i<n; ++i){
     for (int j=0; j<n; ++j){
       cout << g[i][j] << " ";
     }
     cout << endl;
   }
   */

   cout << dijkstra() << endl;

 }
 return 0;
}
