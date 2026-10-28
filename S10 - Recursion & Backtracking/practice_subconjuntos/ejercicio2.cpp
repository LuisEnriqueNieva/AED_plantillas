#include <iostream>
#include <vector>
using namespace std;

vector<int> elementos;
int T, contador = 0;

void sub(int pos, int suma) {
    if (pos == elementos.size()) {
        if (suma == T) contador++;
        return;
    }
    sub(pos + 1, suma + elementos[pos]);  
    sub(pos + 1, suma);                   
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