#include <iostream>
#include <vector>
using namespace std;

vector<int> a; int T, contador = 0;
void sub(int i, int suma) {
    if (suma > T) return;                         // poda (si todos son positivos)
    if (i == a.size()) { if (suma == T) contador++; return; }   // caso base: procesar
    sub(i + 1, suma + a[i]);                      // incluir
    sub(i + 1, suma);                             // no incluir
}