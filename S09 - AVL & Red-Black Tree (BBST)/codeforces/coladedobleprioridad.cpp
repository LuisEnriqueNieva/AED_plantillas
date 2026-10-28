#include <iostream>
using namespace std;

struct NodoAVL {
    int clave;
    int altura;
    NodoAVL* izq;
    NodoAVL* der;
    NodoAVL(int k) : clave(k), altura(0), izq(nullptr), der(nullptr) {}
};

class AVL {
public:
    NodoAVL* raiz;

    AVL() : raiz(nullptr) {}
    ~AVL() { liberar(raiz); }

    void insertar(int k) { raiz = insertar(raiz, k); }
    void eliminar(int k) { raiz = eliminar(raiz, k); }

    bool buscar(int k) {
        NodoAVL* v = raiz;
        while (v != nullptr) {
            if (k == v->clave) return true;
            v = (k < v->clave) ? v->izq : v->der;
        }
        return false;
    }

    bool verificar() {
        return verificar(raiz, -2000000000LL, 2000000000LL) != FALLA;
    }

    void inorder() { inorder(raiz); cout << "\n"; }
    bool vacio() { return raiz == nullptr; }
    int menor() { return minimo(raiz)->clave; }
    int mayor() { return maximo(raiz)->clave; }

private:
    static const int FALLA = -2;

    NodoAVL* maximo(NodoAVL* v) {
        while (v->der != nullptr) v = v->der;
        return v;
    }

    int h(NodoAVL* v) { return v == nullptr ? -1 : v->altura; }

    void actualizar(NodoAVL* v) { v->altura = 1 + max(h(v->izq), h(v->der)); }

    int fb(NodoAVL* v) { return h(v->izq) - h(v->der); }

    NodoAVL* rotarDerecha(NodoAVL* y) {
        NodoAVL* x = y->izq;
        y->izq = x->der;
        x->der = y;
        actualizar(y);
        actualizar(x);
        return x;
    }

    NodoAVL* rotarIzquierda(NodoAVL* x) {
        NodoAVL* y = x->der;
        x->der = y->izq;
        y->izq = x;
        actualizar(x);
        actualizar(y);
        return y;
    }

    NodoAVL* rebalancear(NodoAVL* v) {
        actualizar(v);
        if (fb(v) > 1) {
            if (fb(v->izq) < 0) v->izq = rotarIzquierda(v->izq);
            return rotarDerecha(v);
        }
        if (fb(v) < -1) {
            if (fb(v->der) > 0) v->der = rotarDerecha(v->der);
            return rotarIzquierda(v);
        }
        return v;
    }

    NodoAVL* insertar(NodoAVL* v, int k) {
        if (v == nullptr) return new NodoAVL(k);
        if (k < v->clave) v->izq = insertar(v->izq, k);
        else v->der = insertar(v->der, k);
        return rebalancear(v);
    }

    NodoAVL* minimo(NodoAVL* v) {
        while (v->izq != nullptr) v = v->izq;
        return v;
    }

    NodoAVL* eliminar(NodoAVL* v, int k) {
        if (v == nullptr) return nullptr;
        if (k < v->clave) {
            v->izq = eliminar(v->izq, k);
        } else if (k > v->clave) {
            v->der = eliminar(v->der, k);
        } else {
            if (v->izq == nullptr) {
                NodoAVL* r = v->der;
                delete v;
                return r;
            }
            if (v->der == nullptr) {
                NodoAVL* r = v->izq;
                delete v;
                return r;
            }
            NodoAVL* s = minimo(v->der);
            v->clave = s->clave;
            v->der = eliminar(v->der, s->clave);
        }
        return rebalancear(v);
    }

    int verificar(NodoAVL* v, long long lo, long long hi) {
        if (v == nullptr) return -1;
        if (!(lo < v->clave && v->clave < hi)) return FALLA;
        int a = verificar(v->izq, lo, v->clave);
        int b = verificar(v->der, v->clave, hi);
        if (a == FALLA || b == FALLA) return FALLA;
        if (v->altura != 1 + max(a, b) || abs(a - b) > 1) return FALLA;
        return v->altura;
    }

    void inorder(NodoAVL* v) {
        if (v == nullptr) return;
        inorder(v->izq);
        cout << v->clave << " ";
        inorder(v->der);
    }

    void liberar(NodoAVL* v) {
        if (v == nullptr) return;
        liberar(v->izq);
        liberar(v->der);
        delete v;
    }
};

int main() {
    int q;
    cin >> q;
    AVL avl;
    for (int i=0; i < q ; i++) {
        int order, x;
        cin >> order;
        if (order == 1) {
            cin >> x;
            avl.insertar(x);
        }

        else if (order == 2) {
            if (avl.vacio()) cout << "VACIA" << "\n";
            else {
                int menor = avl.menor();
                cout << menor << "\n";
                avl.eliminar(menor);
            }
        }

        else if (order == 3) {
            if (avl.vacio()) cout << "VACIA" << "\n";
            else {
                int mayor = avl.mayor();
                cout << mayor << "\n";
                avl.eliminar(mayor);
            }
        }
    }


}