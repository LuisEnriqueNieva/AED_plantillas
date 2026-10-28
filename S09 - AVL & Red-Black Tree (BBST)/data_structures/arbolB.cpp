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


struct NodoB {
    bool hoja;
    vector<int> claves;       // ordenadas
    vector<NodoB*> hijos;     // vacio si es hoja; si no, claves.size() + 1 hijos
    NodoB(bool h) : hoja(h) {}
};

class ArbolB {
public:
    NodoB* raiz;
    ArbolB() { raiz = new NodoB(true); }

    // ---------- BUSCAR ----------
    bool buscar(int k) {
        NodoB* n = raiz;
        while (true) {
            int i = primeraMayorOIgual(n->claves, k);
            if (i < (int)n->claves.size() && n->claves[i] == k) return true;
            if (n->hoja) return false;      // llegue abajo y no estaba
            n = n->hijos[i];                // bajo por el hijo i
        }
    }

    // ---------- INSERTAR ----------
    void insertar(int k) {
        if (buscar(k)) return;              // sin repetidos
        int subida;
        NodoB* nuevo = nullptr;
        if (insertarRec(raiz, k, subida, nuevo)) {   // la raiz se partio
            NodoB* r = new NodoB(false);             // nueva raiz: el arbol crece por arriba
            r->claves.push_back(subida);
            r->hijos.push_back(raiz);
            r->hijos.push_back(nuevo);
            raiz = r;
        }
    }

    // ---------- ELIMINAR ----------
    void eliminar(int k) {
        if (!buscar(k)) return;
        eliminarRec(raiz, k);
        if (raiz->claves.empty() && !raiz->hoja) {   // la raiz quedo vacia: el arbol baja un nivel
            NodoB* vieja = raiz;
            raiz = raiz->hijos[0];
            delete vieja;
        }
    }

    void imprimir(NodoB* n, int nivel) {
        for (int i = 0; i < nivel; i++) cout << "    ";
        for (int c : n->claves) cout << c << " ";
        cout << "\n";
        if (!n->hoja)
            for (NodoB* h : n->hijos) imprimir(h, nivel + 1);
    }

private:
    // Devuelve true si el nodo n se partio. En ese caso 'subida' es la clave
    // del medio y 'nuevo' es la mitad derecha, para que el padre los acomode.
    bool insertarRec(NodoB* n, int k, int& subida, NodoB*& nuevo) {
        int i = primeraMayorOIgual(n->claves, k);
        if (n->hoja) {
            n->claves.insert(n->claves.begin() + i, k);        // inserto en su lugar
        } else {
            int s;
            NodoB* h = nullptr;
            if (insertarRec(n->hijos[i], k, s, h)) {           // el hijo se partio
                n->claves.insert(n->claves.begin() + i, s);    // la clave que subio entra aqui
                n->hijos.insert(n->hijos.begin() + i + 1, h);  // y su mitad derecha, a su derecha
            }
        }
        if ((int)n->claves.size() <= MAX_CLAVES) return false; // cupo: listo

        // Overflow: partir. La clave del medio sube; izquierda se queda, derecha va a un nodo nuevo
        int mid = n->claves.size() / 2;
        subida = n->claves[mid];
        nuevo = new NodoB(n->hoja);
        nuevo->claves.assign(n->claves.begin() + mid + 1, n->claves.end());
        n->claves.resize(mid);
        if (!n->hoja) {
            nuevo->hijos.assign(n->hijos.begin() + mid + 1, n->hijos.end());
            n->hijos.resize(mid + 1);
        }
        return true;
    }

    void eliminarRec(NodoB* n, int k) {
        int i = primeraMayorOIgual(n->claves, k);
        if (n->hoja) {                                  // borrar en hoja: caso simple
            n->claves.erase(n->claves.begin() + i);
            return;
        }
        bool esta = (i < (int)n->claves.size() && n->claves[i] == k);
        int hijo = i;
        if (esta) {                                     // k esta en nodo interno:
            NodoB* sig = n->hijos[i + 1];               // buscar sucesor = la clave mas chica
            while (!sig->hoja) sig = sig->hijos[0];     // del subarbol derecho (en una hoja)
            int sucesor = sig->claves[0];
            n->claves[i] = sucesor;                     // reemplazar k por el sucesor
            k = sucesor;                                // y ahora borrar el sucesor abajo
            hijo = i + 1;
        }
        eliminarRec(n->hijos[hijo], k);
        if ((int)n->hijos[hijo]->claves.size() < MIN_CLAVES)   // el hijo quedo bajo el minimo
            arreglar(n, hijo);
    }

    // El hijo i del padre p quedo con pocas claves: rotar o unir
    void arreglar(NodoB* p, int i) {
        NodoB* c = p->hijos[i];
        NodoB* izq = (i > 0) ? p->hijos[i - 1] : nullptr;
        NodoB* der = (i + 1 < (int)p->hijos.size()) ? p->hijos[i + 1] : nullptr;

        if (izq && (int)izq->claves.size() > MIN_CLAVES) {      // ROTACION desde el hermano izquierdo
            c->claves.insert(c->claves.begin(), p->claves[i - 1]);  // baja la clave del padre
            p->claves[i - 1] = izq->claves.back();                  // sube la ultima del hermano
            izq->claves.pop_back();
            if (!c->hoja) {                                         // el hijo que sobra tambien se muda
                c->hijos.insert(c->hijos.begin(), izq->hijos.back());
                izq->hijos.pop_back();
            }
        } else if (der && (int)der->claves.size() > MIN_CLAVES) { // ROTACION desde el hermano derecho
            c->claves.push_back(p->claves[i]);
            p->claves[i] = der->claves[0];
            der->claves.erase(der->claves.begin());
            if (!c->hoja) {
                c->hijos.push_back(der->hijos[0]);
                der->hijos.erase(der->hijos.begin());
            }
        } else if (izq) {                                       // MERGE con el hermano izquierdo
            unir(p, i - 1);
        } else {                                                // MERGE con el hermano derecho
            unir(p, i);
        }
    }

    // Une hijos[j] y hijos[j+1] bajando la clave p->claves[j]
    void unir(NodoB* p, int j) {
        NodoB* L = p->hijos[j];
        NodoB* R = p->hijos[j + 1];
        L->claves.push_back(p->claves[j]);                      // baja la clave del padre
        for (int c : R->claves) L->claves.push_back(c);
        for (NodoB* h : R->hijos) L->hijos.push_back(h);
        p->claves.erase(p->claves.begin() + j);
        p->hijos.erase(p->hijos.begin() + j + 1);
        delete R;
    }
};