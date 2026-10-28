#include <iostream>
#include <vector>
using namespace std;

int n, m; 
vector<string> g; 
vector<vector<bool>> vis; 
long long cont = 0;

int df[4] = {-1, 1, 0, 0}, 
dc[4] = {0, 0, -1, 1};

void dfs(int f, int c) {
    if (f == n - 1 && c == m - 1) { cont++; return; }          // meta
    for (int d = 0; d < 4; d++) {
        int nf = f + df[d], nc = c + dc[d];
        if (0 <= nf && nf < n && 0 <= nc && nc < m && g[nf][nc] == '.' && !vis[nf][nc]) {
            vis[nf][nc] = true; 
            dfs(nf, nc); 
            vis[nf][nc] = false;
        }
    }
}
// main: vis[0][0] = true; dfs(0, 0);