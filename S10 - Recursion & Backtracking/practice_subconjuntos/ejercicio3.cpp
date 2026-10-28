#include <iostream>
#include <vector>
using namespace std;

vector<int> elementos;
int T, contador = 0;

void sub(int pos, int suma) {
    if (suma > T) return;                 // PODA: ya te pasaste, no sigas
    if (pos == elementos.size()) {
        if (suma == T) contador++;        // vuelve a ser ==
        return;
    }
    sub(pos + 1, suma + elementos[pos]);  // incluir
    sub(pos + 1, suma);                   // no incluir
}

int main() {
    int n;
    cin >> n >> T;
    elementos.resize(n);
    for (int i = 0; i < n; i++) cin >> elementos[i];
    sub(0, 0);
    cout << contador << "\n";
    return 0;
}