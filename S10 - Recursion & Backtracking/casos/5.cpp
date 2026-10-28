#include <iostream>
#include <vector>
using namespace std;


vector<int> b;
void part(int quedan, int tope) {
    if (quedan == 0) { 
        /* procesar b */ 
        return; 
    }
    for (int v = min(tope, quedan); v >= 1; v--) {
        b.push_back(v); 
        part(quedan - v, v); 
        b.pop_back();
    }
}