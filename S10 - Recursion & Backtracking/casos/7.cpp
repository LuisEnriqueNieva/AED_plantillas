#include <iostream>
#include <vector>
using namespace std;

// reinas
int n;
vector<bool> col, d1, d2;
vector<string> g; 
int cont = 0;   // d1: 2n+1, d2: 2n

void reinas(int f) {
    if (f == n) { cont++; return; }
    for (int c = 0; c < n; c++) {
        if (g[f][c] == '#') continue;                          // obstáculo
        if (col[c] || d1[f - c + n] || d2[f + c]) continue;    // poda
        col[c] = d1[f - c + n] = d2[f + c] = true;
        reinas(f + 1);
        col[c] = d1[f - c + n] = d2[f + c] = false;
    }
}

//sudoku
int G[9][9]; bool fil[9][10], colu[9][10], blo[9][10];   // se llenan con las casillas dadas
bool sudoku(int pos) {
    if (pos == 81) return true;
    int f = pos / 9, c = pos % 9;
    if (G[f][c] != 0) return sudoku(pos + 1);
    int b = (f / 3) * 3 + c / 3;
    for (int v = 1; v <= 9; v++) {
        if (fil[f][v] || colu[c][v] || blo[b][v]) continue;
        G[f][c] = v; fil[f][v] = colu[c][v] = blo[b][v] = true;
        if (sudoku(pos + 1)) return true;
        G[f][c] = 0; fil[f][v] = colu[c][v] = blo[b][v] = false;
    }
    return false;
}