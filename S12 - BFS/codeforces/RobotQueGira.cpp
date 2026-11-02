#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Arista {
    int u, v, w;
};

class Grafo {
public:
    int n, m;
    bool esDirigido;
    vector<vector<int>> listaAdy;
    vector<vector<int>> pesoAdy;
    vector<Arista> listaAristas;
    vector<vector<int>> matrizAdy;
    vector<int> gradoEntrada;
    vector<bool> marca;

    Grafo(int n, bool dirigido = false) : n(n), m(0), esDirigido(dirigido) {
        listaAdy.assign(n + 1, vector<int>());
        pesoAdy.assign(n + 1, vector<int>());
        gradoEntrada.assign(n + 1, 0);
        marca.assign(n + 1, false);
    }

    void agregarArista(int u, int v, int w = 1) {
        listaAdy[u].push_back(v);
        pesoAdy[u].push_back(w);
        gradoEntrada[v]++;
        listaAristas.push_back({u, v, w});
        if (!esDirigido) {
            listaAdy[v].push_back(u);
            pesoAdy[v].push_back(w);
            gradoEntrada[u]++;
        }
        if (!matrizAdy.empty()) {
            matrizAdy[u][v] = w;
            if (!esDirigido) matrizAdy[v][u] = w;
        }
        m++;
    }

    int grado(int u) { return listaAdy[u].size(); }

    bool sonAdyacentesLista(int u, int v) {
        for (int x : listaAdy[u])
            if (x==v) return true;
        return false;
    }

    void construirMatriz() {
        matrizAdy.assign(n + 1, vector<int>(n + 1, 0));
        for (auto& a : listaAristas) {
            matrizAdy[a.u][a.v] = a.w;
            if (!esDirigido) matrizAdy[a.v][a.u] = a.w;
        }
    }

    bool sonAdyacentesMatriz(int u, int v) { return matrizAdy[u][v]!=0; }

    void quitarUno(int u, int v) {
        for (int i = 0; i < (int)listaAdy[u].size(); i++)
            if (listaAdy[u][i]==v) {
                listaAdy[u][i] = listaAdy[u].back();
                pesoAdy[u][i] = pesoAdy[u].back();
                listaAdy[u].pop_back();
                pesoAdy[u].pop_back();
                break;
            }
    }

    void quitarArista(int u, int v) {
        quitarUno(u, v);
        gradoEntrada[v]--;
        if (!esDirigido) {
            quitarUno(v, u);
            gradoEntrada[u]--;
        }
        for (int i = 0; i < (int)listaAristas.size(); i++) {
            Arista a = listaAristas[i];
            if ((a.u==u && a.v==v) || (!esDirigido && a.u==v && a.v==u)) {
                listaAristas.erase(listaAristas.begin() + i);
                break;
            }
        }
        if (!matrizAdy.empty()) {
            matrizAdy[u][v] = 0;
            if (!esDirigido) matrizAdy[v][u] = 0;
        }
        m--;
    }

    vector<vector<int>> obtenerTranspuesto() {
        vector<vector<int>> t(n + 1);
        for (int u = 1; u <= n; u++)
            for (int v : listaAdy[u]) t[v].push_back(u);
        return t;
    }

    int vecinosComunes(int u, int v) {
        int c = 0;
        for (int x : listaAdy[u]) marca[x] = true;
        for (int y : listaAdy[v])
            if (marca[y]) c++;
        for (int x : listaAdy[u]) marca[x] = false;
        return c;
    }

    pair<vector<int>, vector<int>> construirCompacta() {
        vector<int> g(n + 2, 0), inicio(n + 2, 0);
        for (auto& a : listaAristas) {
            g[a.u]++;
            if (!esDirigido) g[a.v]++;
        }
        for (int u = 1; u <= n; u++) inicio[u + 1] = inicio[u] + g[u];
        vector<int> pos = inicio, vecinos(inicio[n + 1]);
        for (auto& a : listaAristas) {
            vecinos[pos[a.u]++] = a.v;
            if (!esDirigido) vecinos[pos[a.v]++] = a.u;
        }
        return {inicio, vecinos};
    }

    vector<int> distancias(int s) {
        vector<int> d(n + 1, -1);
        queue<int> q;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : listaAdy[u])
                if (d[v]==-1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
        }
        return d;
    }

    void bfs(int s, vector<int>& distancia, vector<int>& padre) {
    distancia.assign(n + 1, -1);
    padre.assign(n + 1, 0);
    queue<int> q;
    distancia[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : listaAdy[u])
            if (distancia[v]==-1) {
                distancia[v] = distancia[u] + 1;
                padre[v] = u;
                q.push(v);
            }
        }
    }

    vector<int> camino(int s, int t) {
        vector<int> d, p;
        bfs(s, d, p);
        vector<int> r;
        if (d[t]==-1) return r;
        for (int x = t; x!=s; x = p[x]) r.push_back(x);
        r.push_back(s);
        reverse(r.begin(), r.end());
        return r;
    }

    vector<int> componentes(int& k) {
        vector<int> c(n + 1, 0);
        k = 0;
        for (int s = 1; s <= n; s++) {
            if (c[s]!=0) continue;
            k++;
            queue<int> q;
            c[s] = k;
            q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : listaAdy[u])
                    if (c[v]==0) {
                        c[v] = k;
                        q.push(v);
                    }
            }
        }
        return c;
    }

    vector<int> distanciasMultiples(const vector<int>& fuentes) {
        vector<int> d(n + 1, -1);
        queue<int> q;
        for (int s : fuentes) {
            d[s] = 0;
            q.push(s);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : listaAdy[u])
                if (d[v]==-1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
        }
        return d;
    }
    
};

vector<pair<int,int>> vecinosGrilla(int f, int c, int R, int C, const vector<string>& g) {
    int df[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    vector<pair<int,int>> r;
    for (int k = 0; k < 4; k++) {
        int a = f + df[k], b = c + dc[k];
        if (a>=0 && a<R && b>=0 && b<C && g[a][b]!='#') r.push_back({a, b});
    }
    return r;
}
vector<vector<int>> bfsGrilla(int f, int c, int R, int C, const vector<string>& g, char pared) {
    int df[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    vector<vector<int>> d(R, vector<int>(C, -1));
    queue<pair<int,int>> q;
    d[f][c] = 0;
    q.push({f, c});
    while (!q.empty()) {
        int a = q.front().first, b = q.front().second;
        q.pop();
        for (int k = 0; k < 4; k++) {
            int x = a + df[k], y = b + dc[k];
            if (x>=0 && x<R && y>=0 && y<C && g[x][y]!=pared && d[x][y]==-1) {
                d[x][y] = d[a][b] + 1;
                q.push({x, y});
            }
        }
    }
    return d;
}


int main() {
    int n, m;
    cin>>n>>m;
    vector<string> laberinto(n);
    for (int i=0;i<n;i++) cin>>laberinto[i];
    int df[4] = {0, 1, 0, -1}, dc[4] = {1, 0, -1, 0};
    vector<int> distancia(n*m*4, -1);
    queue<int> q;
    distancia[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int e = q.front();
        q.pop();
        int d = e%4, c = e/4%m, f = e/4/m;
        int izq = (f*m + c)*4 + (d + 3)%4;
        int der = (f*m + c)*4 + (d + 1)%4;
        if (distancia[izq]==-1) {
            distancia[izq] = distancia[e] + 1;
            q.push(izq);
        }
        if (distancia[der]==-1) {
            distancia[der] = distancia[e] + 1;
            q.push(der);
        }
        int x = f + df[d], y = c + dc[d];
        if (x>=0 && x<n && y>=0 && y<m && laberinto[x][y]=='.') {
            int s = (x*m + y)*4 + d;
            if (distancia[s]==-1) {
                distancia[s] = distancia[e] + 1;
                q.push(s);
            }
        }
    }
    int mejor = -1;
    for (int d=0;d<4;d++) {
        int v = distancia[((n-1)*m + (m-1))*4 + d];
        if (v!=-1 && (mejor==-1 || v<mejor)) mejor = v;
    }
    cout<<mejor<<"\n";
    return 0;
}