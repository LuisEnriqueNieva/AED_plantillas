#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Arista {
    int u, v, w;
};

class Grafo {
public:
    int n, m;
    bool esDirigido;

    vector<vector<int>> matrizAdy;
    vector<vector<int>> listaAdy;
    vector<Arista> listaAristas;

    Grafo(int n, bool dirigido = false) : n(n), m(0), esDirigido(dirigido) {
        matrizAdy.assign(n + 1, vector<int>(n + 1, 0));
        listaAdy.resize(n + 1);
    }

    void agregarArista(int u, int v, int w = 1) {
        matrizAdy[u][v] = w;
        listaAdy[u].push_back(v);
        listaAristas.push_back({u, v, w});

        if (!esDirigido) {
            matrizAdy[v][u] = w;
            listaAdy[v].push_back(u);
        }
        m++;
    }

    bool sonAdyacentesMatriz(int u, int v) const {
        return matrizAdy[u][v] != 0;
    }

    bool sonAdyacentesLista(int u, int v) const {
        for (int vecino : listaAdy[u]) {
            if (vecino == v) return true;
        }
        return false;
    }

    void quitarAristaLista(int u, int v) {
        for (size_t i = 0; i < listaAdy[u].size(); ++i) {
            if (listaAdy[u][i] == v) {
                listaAdy[u][i] = listaAdy[u].back();
                listaAdy[u].pop_back();
                break;
            }
        }

        if (!esDirigido) {
            for (size_t j = 0; j < listaAdy[v].size(); ++j) {
                if (listaAdy[v][j] == u) {
                    listaAdy[v][j] = listaAdy[v].back();
                    listaAdy[v].pop_back();
                    break;
                }
            }
        }
    }

    vector<vector<int>> obtenerTranspuesto() const {
        vector<vector<int>> adjT(n + 1);
        for (int u = 1; u <= n; ++u) {
            for (int v : listaAdy[u]) {
                adjT[v].push_back(u);
            }
        }
        return adjT;
    }

    int vecinosComunes(int u, int v) const {
        vector<bool> marca(n + 1, false);
        int cnt = 0;

        for (int x : listaAdy[u]) {
            marca[x] = true;
        }
        for (int y : listaAdy[v]) {
            if (marca[y]) cnt++;
        }
        return cnt;
    }

    pair<vector<int>, vector<int>> construirListaCompacta() const {
        vector<int> grado(n + 2, 0);
        vector<int> inicio(n + 2, 0);

        for (const auto& a : listaAristas) {
            grado[a.u]++;
            if (!esDirigido) grado[a.v]++;
        }

        inicio[1] = 0;
        for (int u = 1; u <= n; ++u) {
            inicio[u + 1] = inicio[u] + grado[u];
        }

        vector<int> pos = inicio;
        vector<int> vecinos(inicio[n + 1]);

        for (const auto& a : listaAristas) {
            vecinos[pos[a.u]++] = a.v;
            if (!esDirigido) {
                vecinos[pos[a.v]++] = a.u;
            }
        }

        return {inicio, vecinos};
    }
};

void obtenerVecinosGrilla(int f, int c, int R, int C, const vector<vector<bool>>& esPared) {
    int df[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    cout << "Vecinos de (" << f << ", " << c << "): ";
    for (int k = 0; k < 4; ++k) {
        int nf = f + df[k];
        int nc = c + dc[k];

        if (nf >= 0 && nf < R && nc >= 0 && nc < C && !esPared[nf][nc]) {
            cout << "(" << nf << ", " << nc << ") ";
        }
    }
    cout << "\n";
}  // en el final viene para el de 8 vecinos



vector<long long> ids;

int indice(long long x) {
    for (int i=0;i<(int)ids.size();i++)
        if (ids[i]==x) return i+1;
    ids.push_back(x);
    return ids.size();
}

int main() {
    ifstream file("data.txt");
    long long u, v;
    double w;
    while (file >> u >> v >> w) {
       indice(u);
       indice(v);
    }
    file.close();

    Grafo g(ids.size(), true);
    ifstream file2("data.txt");
    while (file2 >> u >> v >> w) {
       g.agregarArista(indice(u), indice(v), w);
    }
    file2.close();

    cout <<g.sonAdyacentesLista(indice(13506032312), indice(13506032313))<<"\n";
    cout <<g.sonAdyacentesLista(indice(13506032313), indice(13506032312))<<"\n";
    return 0;
}