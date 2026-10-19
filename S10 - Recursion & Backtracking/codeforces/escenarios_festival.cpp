#include <iostream>
#include <vector>
using namespace std;

int n;
int c[9][9];
bool usado[9];
int mejor = 1000000000;

void asignar(int i, int costo) {
    if (costo >= mejor) return;                  
    if (i == n) {
        if (costo < mejor) mejor = costo;
        return;                        
    }
    for (int j = 0; j < n; j++) {
        if (usado[j] || c[i][j] == -1) continue;  
        usado[j] = true;                          
        asignar(i + 1, costo + c[i][j]);          
        usado[j] = false;                          
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> c[i][j];
    asignar(0, 0);
    if (mejor == 1000000000) cout << -1 << "\n";
    else cout << mejor << "\n";
    return 0;
}