#include <iostream>
#include <vector>
using namespace std;

const int M = 4;                       // orden: maximo de hijos. Cambia este numero para practicar
const int MAX_CLAVES = M - 1;          // maximo de claves por nodo
const int MIN_CLAVES = (M + 1) / 2 - 1;// minimo de claves (nodo no raiz): ceil(M/2) - 1
const int MIN_HOJA = M / 2;            // minimo de claves en una hoja del B+

// Primera posicion i donde v[i] >= k  (donde iria k si lo insertas)
int primeraMayorOIgual(const vector<int>& v, int k) {
    int i = 0;
    while (i < (int)v.size() && v[i] < k) i++;
    return i;
}
// Primera posicion i donde v[i] > k  (sirve para elegir a que hijo bajar en el B+)
int primeraMayor(const vector<int>& v, int k) {
    int i = 0;
    while (i < (int)v.size() && v[i] <= k) i++;
    return i;
}

struct NodoBP {
    bool hoja;
    vector<int> claves;
    vector<NodoBP*> hijos;    // solo nodos internos
    NodoBP* sig;              // B+: solo hojas, apunta a la hoja siguiente
    NodoBP(bool h) : hoja(h), sig(nullptr) {}
};

class ArbolBP {
public:
    NodoBP* raiz;
    ArbolBP() { raiz = new NodoBP(true); }

    // B+: siempre se baja hasta la hoja. Regla: claves >= separador van a la derecha
    NodoBP* buscarHoja(int k) {
        NodoBP* n = raiz;
        while (!n->hoja) n = n->hijos[primeraMayor(n->claves, k)];
        return n;
    }

    bool buscar(int k) {
        NodoBP* h = buscarHoja(k);
        int i = primeraMayorOIgual(h->claves, k);
        return i < (int)h->claves.size() && h->claves[i] == k;
    }

    // B+: consulta por rango. Bajo una vez y sigo las flechas
    void rango(int a, int b) {
        NodoBP* n = buscarHoja(a);
        while (n != nullptr) {
            for (int x : n->claves) {
                if (x > b) return;
                if (x >= a) cout << x << " ";
            }
            n = n->sig;                                  // siguiente hoja
        }
    }

    void insertar(int k) {
        if (buscar(k)) return;
        int subida;
        NodoBP* nuevo = nullptr;
        if (insertarRec(raiz, k, subida, nuevo)) {
            NodoBP* r = new NodoBP(false);
            r->claves.push_back(subida);
            r->hijos.push_back(raiz);
            r->hijos.push_back(nuevo);
            raiz = r;
        }
    }

    void eliminar(int k) {
        if (!buscar(k)) return;
        eliminarRec(raiz, k);
        if (!raiz->hoja && raiz->claves.empty()) {
            NodoBP* vieja = raiz;
            raiz = raiz->hijos[0];
            delete vieja;
        }
    }

    void imprimir(NodoBP* n, int nivel) {
        for (int i = 0; i < nivel; i++) cout << "    ";
        for (int c : n->claves) cout << c << " ";
        cout << (n->hoja ? " (hoja)" : "") << "\n";
        if (!n->hoja)
            for (NodoBP* h : n->hijos) imprimir(h, nivel + 1);
    }

private:
    bool insertarRec(NodoBP* n, int k, int& subida, NodoBP*& nuevo) {
        if (n->hoja) {
            int i = primeraMayorOIgual(n->claves, k);
            n->claves.insert(n->claves.begin() + i, k);
            if ((int)n->claves.size() <= MAX_CLAVES) return false;

            int mid = n->claves.size() / 2;              // split de HOJA
            nuevo = new NodoBP(true);
            nuevo->claves.assign(n->claves.begin() + mid, n->claves.end());  // B+: el medio SE QUEDA en la hoja derecha
            n->claves.resize(mid);
            nuevo->sig = n->sig;                         // B+: enlazar la lista de hojas
            n->sig = nuevo;
            subida = nuevo->claves[0];                   // B+: al padre se COPIA (no se mueve)
            return true;
        }
        int i = primeraMayor(n->claves, k);
        int s;
        NodoBP* h = nullptr;
        if (!insertarRec(n->hijos[i], k, s, h)) return false;
        n->claves.insert(n->claves.begin() + i, s);
        n->hijos.insert(n->hijos.begin() + i + 1, h);
        if ((int)n->claves.size() <= MAX_CLAVES) return false;

        int mid = n->claves.size() / 2;                  // split de nodo INTERNO: igual que en B
        subida = n->claves[mid];                         // aqui SI se mueve arriba
        nuevo = new NodoBP(false);
        nuevo->claves.assign(n->claves.begin() + mid + 1, n->claves.end());
        nuevo->hijos.assign(n->hijos.begin() + mid + 1, n->hijos.end());
        n->claves.resize(mid);
        n->hijos.resize(mid + 1);
        return true;
    }

    void eliminarRec(NodoBP* n, int k) {
        if (n->hoja) {
            int i = primeraMayorOIgual(n->claves, k);
            n->claves.erase(n->claves.begin() + i);
            return;
        }
        int i = primeraMayor(n->claves, k);              // B+: siempre bajo hasta la hoja
        eliminarRec(n->hijos[i], k);
        NodoBP* h = n->hijos[i];
        int minimo = h->hoja ? MIN_HOJA : MIN_CLAVES;
        if ((int)h->claves.size() < minimo) arreglar(n, i);
    }

    void arreglar(NodoBP* p, int i) {
        NodoBP* c = p->hijos[i];
        NodoBP* izq = (i > 0) ? p->hijos[i - 1] : nullptr;
        NodoBP* der = (i + 1 < (int)p->hijos.size()) ? p->hijos[i + 1] : nullptr;
        int minimo = c->hoja ? MIN_HOJA : MIN_CLAVES;

        if (izq && (int)izq->claves.size() > minimo) {
            if (c->hoja) {                               // B+ hoja: la clave se pasa directo y el separador se actualiza
                c->claves.insert(c->claves.begin(), izq->claves.back());
                izq->claves.pop_back();
                p->claves[i - 1] = c->claves[0];
            } else {                                     // interno: rotacion como en B
                c->claves.insert(c->claves.begin(), p->claves[i - 1]);
                p->claves[i - 1] = izq->claves.back();
                izq->claves.pop_back();
                c->hijos.insert(c->hijos.begin(), izq->hijos.back());
                izq->hijos.pop_back();
            }
        } else if (der && (int)der->claves.size() > minimo) {
            if (c->hoja) {
                c->claves.push_back(der->claves[0]);
                der->claves.erase(der->claves.begin());
                p->claves[i] = der->claves[0];
            } else {
                c->claves.push_back(p->claves[i]);
                p->claves[i] = der->claves[0];
                der->claves.erase(der->claves.begin());
                c->hijos.push_back(der->hijos[0]);
                der->hijos.erase(der->hijos.begin());
            }
        } else if (izq) {
            unir(p, i - 1);
        } else {
            unir(p, i);
        }
    }

    void unir(NodoBP* p, int j) {
        NodoBP* L = p->hijos[j];
        NodoBP* R = p->hijos[j + 1];
        if (L->hoja) {                                   // B+ hojas: la clave del padre NO baja (solo era guia)
            for (int c : R->claves) L->claves.push_back(c);
            L->sig = R->sig;                             // saltar la hoja que desaparece en la lista
        } else {                                         // internos: baja la clave del padre, como en B
            L->claves.push_back(p->claves[j]);
            for (int c : R->claves) L->claves.push_back(c);
            for (NodoBP* h : R->hijos) L->hijos.push_back(h);
        }
        p->claves.erase(p->claves.begin() + j);
        p->hijos.erase(p->hijos.begin() + j + 1);
        delete R;
    }
};