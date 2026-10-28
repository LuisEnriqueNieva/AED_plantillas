#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> w; 
int carga[3]; 
int mejor = 1000000000;   // 3 = k


void rep(int i) {
    if (i == n) { mejor = min(mejor, max(carga[0], max(carga[1], carga[2]))); return; }
    for (int p = 0; p < 3; p++) {
        carga[p] += w[i];
        if (carga[p] < mejor) rep(i + 1);         // poda
        carga[p] -= w[i];
    }
}