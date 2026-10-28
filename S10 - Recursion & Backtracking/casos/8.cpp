#include <iostream>
#include <vector>
using namespace std;

int n, k; vector<int> c;
void comb(int v) {
    if (c.size() == k) { 
        /* procesar c */ 
        return; 
    }
    for (int x = v; x <= n - (k - c.size()) + 1; x++) {
        c.push_back(x); 
        comb(x + 1); 
        c.pop_back();
    }
}