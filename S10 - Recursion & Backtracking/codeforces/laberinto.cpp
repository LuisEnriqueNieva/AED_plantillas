#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<string> lab;
vector<vector<bool>> visitado;
int caminos = 0;

int df[4] = {-1, 1, 0, 0};  
int dc[4] = {0, 0, -1, 1};
void contar(int f, int c) {
    if (f == n - 1 && c == m - 1) {
        caminos++;
        return;
    }
    for (int d = 0; d < 4; d++) {
        int nf = f + df[d];
        int nc = c + dc[d];
        if (0 <= nf && nf < n && 0 <= nc && nc < m
            && lab[nf][nc] == '.' && !visitado[nf][nc]) {
                visitado[nf][nc] = true;
                contar(nf, nc);
                visitado[nf][nc] = false;
        }
    }
}

int main() {
    cin >> n >> m;
    lab.resize(n);               
    for (int i = 0; i < n; i++) {
        cin >> lab[i];           
    }
    visitado.assign(n,vector<bool>(m, false));
    visitado[0][0] = true;
    contar(0,0);
    cout << caminos; 

    return 0;
}

