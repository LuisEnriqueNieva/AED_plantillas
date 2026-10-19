#include <iostream>
#include <vector>
using namespace std;

int carga[3] = {0,0,0};
int mejor = 1000000000;
vector<int> w;
int n;

void repartoCaja(int i) {    // i es la caja_i
    if (i == n) {
        int puntaje = max(carga[0], max(carga[1], carga[2]));
        if (puntaje < mejor) {
            mejor = puntaje;
        }
        return;
    }
    for (int p = 0; p < 3; p++) {
        carga[p] += w[i];
        repartoCaja(i + 1);
        carga[p] -= w[i];
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int weight;
        cin >> weight;
        w.push_back(weight);
    }
    
    repartoCaja(0);
    cout << mejor << "\n";

    return 0;
}