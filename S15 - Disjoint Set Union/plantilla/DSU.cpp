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


class DSU {
public:
    vector<int> padre, tamano;
    int componentes, mayorGrupo;

    DSU(int n) : padre(n + 1), tamano(n + 1, 1), componentes(n), mayorGrupo(n>=1 ? 1 : 0) {
        for (int i = 0; i <= n; i++) padre[i] = i;
    }

    int encontrar(int x) {
        while (padre[x]!=x) {
            padre[x] = padre[padre[x]];
            x = padre[x];
        }
        return x;
    }

    bool unir(int a, int b) {
        a = encontrar(a);
        b = encontrar(b);
        if (a==b) return false;
        if (tamano[a]<tamano[b]) swap(a, b);
        padre[b] = a;
        tamano[a] += tamano[b];
        mayorGrupo = max(mayorGrupo, tamano[a]);
        componentes--;
        return true;
    }

    bool mismoGrupo(int a, int b) { return encontrar(a)==encontrar(b); }

    int tamanoGrupo(int x) { return tamano[encontrar(x)]; }

    vector<vector<int>> obtenerGrupos() {
        vector<vector<int>> g(padre.size());
        for (int i = 1; i < (int)padre.size(); i++) g[encontrar(i)].push_back(i);
        vector<vector<int>> r;
        for (auto& x : g)
            if (!x.empty()) r.push_back(x);
        return r;
    }
};

long long kruskal(int n, vector<Arista> aristas, vector<Arista>& elegidas) {
    sort(aristas.begin(), aristas.end(), [](const Arista& x, const Arista& y) { return x.w<y.w; });
    DSU d(n);
    long long total = 0;
    for (auto& a : aristas)
        if (d.unir(a.u, a.v)) {
            total += a.w;
            elegidas.push_back(a);
        }
    if (d.componentes!=1) return -1;
    return total;
}