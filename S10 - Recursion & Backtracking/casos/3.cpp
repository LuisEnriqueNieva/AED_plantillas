#include <iostream>
#include <vector>
using namespace std;

int n; string s;
void gen(int pos) {
    if (pos == n) { /* procesar s */ return; }
    for (char d : {'0', '1'}) {                   // alfabeto
        if (d == '1' && pos > 0 && s.back() == '1') continue;   // regla de poda
        s.push_back(d); gen(pos + 1); s.pop_back();
    }
} 