#include <iostream>
#include <vector>
using namespace std;

int n; 
vector<int> p; 
vector<bool> usado;

void perm(int pos) {
    if (pos == n) { /* procesar p */ return; }
    for (int x = 0; x < n; x++) {
        if (usado[x]) continue;                   // poda
        usado[x] = true; p.push_back(x);          // hacer
        perm(pos + 1);                            // explorar
        p.pop_back(); usado[x] = false;           // deshacer
    }
}