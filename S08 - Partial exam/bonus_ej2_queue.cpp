#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

const int FALLA = -999999;

struct Nodo {
    int clave;
    int altura;
    Nodo* izq;
    Nodo* der;
    int persona;
    int tam;
    int mayor;

    Nodo(int k) : clave(k), altura(0), izq(nullptr), der(nullptr), persona(0), tam(1), mayor(k) {}
    Nodo(int k, int p) : clave(k), altura(0), izq(nullptr), der(nullptr), persona(p), tam(1), mayor(k) {}
};

class AVLTree {
private:
    Nodo* raiz;

    int h(Nodo* v) {
        if (v == nullptr) return -1;
        return v->altura;
    }

    int tamDe(Nodo* v) {
        if (v == nullptr) return 0;
        return v->tam;
    }

    int mayorDe(Nodo* v) {
        if (v == nullptr) return 0;
        return v->mayor;
    }

    void actualizar(Nodo* v) {
        if (v != nullptr) {
            v->altura = 1 + max(h(v->izq), h(v->der));
            v->tam = 1 + tamDe(v->izq) + tamDe(v->der);
            v->mayor = max(v->clave, max(mayorDe(v->izq), mayorDe(v->der)));
        }
    }

    int FB(Nodo* v) {
        if (v == nullptr) return 0;
        return h(v->izq) - h(v->der);
    }

    Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->izq;
        y->izq = x->der;
        x->der = y;
        
        actualizar(y);
        actualizar(x);
        
        return x;
    }

    Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->der;
        x->der = y->izq;
        y->izq = x;
        
        actualizar(x);
        actualizar(y);
        
        return y;
    }

    Nodo* rebalancear(Nodo* v) {
        if (v == nullptr) return nullptr;
        
        actualizar(v);
        
        if (FB(v) > 1) {
            if (FB(v->izq) < 0) {
                v->izq = rotarIzquierda(v->izq);
            }
            return rotarDerecha(v);
        }
        
        if (FB(v) < -1) {
            if (FB(v->der) > 0) {
                v->der = rotarDerecha(v->der);
            }
            return rotarIzquierda(v);
        }
        
        return v;
    }

    Nodo* insertar(Nodo* v, int k) {
        if (v == nullptr) {
            return new Nodo(k);
        }
        
        if (k < v->clave) {
            v->izq = insertar(v->izq, k);
        } else if (k > v->clave) {
            v->der = insertar(v->der, k);
        } else {
            return v;
        }
        
        return rebalancear(v);
    }

    Nodo* minimo(Nodo* v) {
        Nodo* actual = v;
        while (actual && actual->izq != nullptr) {
            actual = actual->izq;
        }
        return actual;
    }

    Nodo* eliminar(Nodo* v, int k) {
        if (v == nullptr) return nullptr;
        
        if (k < v->clave) {
            v->izq = eliminar(v->izq, k);
        } else if (k > v->clave) {
            v->der = eliminar(v->der, k);
        } else {
            if (v->izq == nullptr) {
                Nodo* temp = v->der;
                delete v;
                return temp;
            } else if (v->der == nullptr) {
                Nodo* temp = v->izq;
                delete v;
                return temp;
            }
            Nodo* s = minimo(v->der);
            v->clave = s->clave;
            v->der = eliminar(v->der, s->clave);
        }
        
        return rebalancear(v);
    }

    int verificar(Nodo* v, long long lo, long long hi) {
        if (v == nullptr) return -1;
        
        if (!(lo < v->clave && v->clave < hi)) return FALLA;
        
        int a = verificar(v->izq, lo, v->clave);
        int b = verificar(v->der, v->clave, hi);
        
        if (a == FALLA || b == FALLA) return FALLA;
        if (v->altura != 1 + max(a, b) || abs(a - b) > 1) return FALLA;
        
        return v->altura;
    }

    Nodo* insertarEn(Nodo* v, int antes, int k, int p) {
        if (v == nullptr) {
            return new Nodo(k, p);
        }

        if (antes <= tamDe(v->izq)) {
            v->izq = insertarEn(v->izq, antes, k, p);
        } else {
            v->der = insertarEn(v->der, antes - tamDe(v->izq) - 1, k, p);
        }

        return rebalancear(v);
    }

    int ultimoMas(Nodo* v, int x) {
        if (v == nullptr || v->mayor < x) return 0;
        if (mayorDe(v->der) > x) return tamDe(v->izq) + 1 + ultimoMas(v->der, x);
        if (v->clave > x) return tamDe(v->izq) + 1;
        return ultimoMas(v->izq, x);
    }

    void inordenPersonas(Nodo* v) {
        if (v != nullptr) {
            inordenPersonas(v->izq);
            cout << v->persona << " ";
            inordenPersonas(v->der);
        }
    }

    void inorden(Nodo* v) {
        if (v != nullptr) {
            inorden(v->izq);
            cout << v->clave << " ";
            inorden(v->der);
        }
    }

public:
    AVLTree() : raiz(nullptr) {}

    void insertar(int k) {
        raiz = insertar(raiz, k);
    }

    void eliminar(int k) {
        raiz = eliminar(raiz, k);
    }

    bool esValidoAVL() {
        return verificar(raiz, LLONG_MIN, LLONG_MAX) != FALLA;
    }

    void imprimir() {
        inorden(raiz);
        cout << endl;
    }

    int cantidad() {
        return tamDe(raiz);
    }

    int posicionUltimoMas(int x) {
        return ultimoMas(raiz, x);
    }

    void insertarEnPosicion(int antes, int k, int p) {
        raiz = insertarEn(raiz, antes, k, p);
    }

    void imprimirPersonas() {
        inordenPersonas(raiz);
        cout << endl;
    }
};

int main() {
    int totalGente;
    cin >> totalGente;

    AVLTree fila;
    for (int turno = 1; turno <= totalGente; turno++) {
        int importancia, saltosMax;
        cin >> importancia >> saltosMax;

        int largo = fila.cantidad();
        int tope = fila.posicionUltimoMas(importancia);
        int desdeAqui = max(tope, largo - saltosMax);

        fila.insertarEnPosicion(desdeAqui, importancia, turno);
    }

    fila.imprimirPersonas();
    return 0;
}