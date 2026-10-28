#include <iostream>
using namespace std;

enum Color { ROJO, NEGRO };

struct NodoRB {
    int clave;
    Color color;
    NodoRB* izq;
    NodoRB* der;
    NodoRB* padre;
};

class RBTree {
public:
    NodoRB* nil;
    NodoRB* raiz;

    RBTree() {
        nil = new NodoRB;
        nil->color = NEGRO;
        nil->izq = nil->der = nil->padre = nil;
        nil->clave = 0;
        raiz = nil;
    }
    ~RBTree() {
        liberar(raiz);
        delete nil;
    }

    void insertar(int k) {
        NodoRB* z = new NodoRB;
        z->clave = k;
        z->color = ROJO;
        z->izq = z->der = nil;
        NodoRB* y = nil;
        NodoRB* x = raiz;
        while (x != nil) {
            y = x;
            x = (k < x->clave) ? x->izq : x->der;
        }
        z->padre = y;
        if (y == nil) raiz = z;
        else if (k < y->clave) y->izq = z;
        else y->der = z;
        insertarFix(z);
    }

    void eliminar(int k) {
        NodoRB* z = buscarNodo(k);
        if (z == nil) return;
        NodoRB* y = z;
        Color colorOriginal = y->color;
        NodoRB* x;
        if (z->izq == nil) {
            x = z->der;
            trasplantar(z, z->der);
        } else if (z->der == nil) {
            x = z->izq;
            trasplantar(z, z->izq);
        } else {
            y = minimo(z->der);
            colorOriginal = y->color;
            x = y->der;
            if (y->padre == z) {
                x->padre = y;
            } else {
                trasplantar(y, y->der);
                y->der = z->der;
                y->der->padre = y;
            }
            trasplantar(z, y);
            y->izq = z->izq;
            y->izq->padre = y;
            y->color = z->color;
        }
        delete z;
        if (colorOriginal == NEGRO) eliminarFix(x);
    }

    bool buscar(int k) { return buscarNodo(k) != nil; }

    bool verificar() {
        if (raiz->color != NEGRO) return false;
        return verificar(raiz, -2000000000LL, 2000000000LL) != -1;
    }

    void inorder() { inorder(raiz); cout << "\n"; }

private:
    NodoRB* buscarNodo(int k) {
        NodoRB* x = raiz;
        while (x != nil && k != x->clave)
            x = (k < x->clave) ? x->izq : x->der;
        return x;
    }

    NodoRB* minimo(NodoRB* x) {
        while (x->izq != nil) x = x->izq;
        return x;
    }

    void rotarIzquierda(NodoRB* x) {
        NodoRB* y = x->der;
        x->der = y->izq;
        if (y->izq != nil) y->izq->padre = x;
        y->padre = x->padre;
        if (x->padre == nil) raiz = y;
        else if (x == x->padre->izq) x->padre->izq = y;
        else x->padre->der = y;
        y->izq = x;
        x->padre = y;
    }

    void rotarDerecha(NodoRB* y) {
        NodoRB* x = y->izq;
        y->izq = x->der;
        if (x->der != nil) x->der->padre = y;
        x->padre = y->padre;
        if (y->padre == nil) raiz = x;
        else if (y == y->padre->izq) y->padre->izq = x;
        else y->padre->der = x;
        x->der = y;
        y->padre = x;
    }

    void trasplantar(NodoRB* u, NodoRB* v) {
        if (u->padre == nil) raiz = v;
        else if (u == u->padre->izq) u->padre->izq = v;
        else u->padre->der = v;
        v->padre = u->padre;
    }

    void insertarFix(NodoRB* z) {
        while (z->padre->color == ROJO) {
            if (z->padre == z->padre->padre->izq) {
                NodoRB* tio = z->padre->padre->der;
                if (tio->color == ROJO) {
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    z->padre->padre->color = ROJO;
                    z = z->padre->padre;
                } else {
                    if (z == z->padre->der) {
                        z = z->padre;
                        rotarIzquierda(z);
                    }
                    z->padre->color = NEGRO;
                    z->padre->padre->color = ROJO;
                    rotarDerecha(z->padre->padre);
                }
            } else {
                NodoRB* tio = z->padre->padre->izq;
                if (tio->color == ROJO) {
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    z->padre->padre->color = ROJO;
                    z = z->padre->padre;
                } else {
                    if (z == z->padre->izq) {
                        z = z->padre;
                        rotarDerecha(z);
                    }
                    z->padre->color = NEGRO;
                    z->padre->padre->color = ROJO;
                    rotarIzquierda(z->padre->padre);
                }
            }
        }
        raiz->color = NEGRO;
    }

    void eliminarFix(NodoRB* x) {
        while (x != raiz && x->color == NEGRO) {
            if (x == x->padre->izq) {
                NodoRB* w = x->padre->der;
                if (w->color == ROJO) {
                    w->color = NEGRO;
                    x->padre->color = ROJO;
                    rotarIzquierda(x->padre);
                    w = x->padre->der;
                }
                if (w->izq->color == NEGRO && w->der->color == NEGRO) {
                    w->color = ROJO;
                    x = x->padre;
                } else {
                    if (w->der->color == NEGRO) {
                        w->izq->color = NEGRO;
                        w->color = ROJO;
                        rotarDerecha(w);
                        w = x->padre->der;
                    }
                    w->color = x->padre->color;
                    x->padre->color = NEGRO;
                    w->der->color = NEGRO;
                    rotarIzquierda(x->padre);
                    x = raiz;
                }
            } else {
                NodoRB* w = x->padre->izq;
                if (w->color == ROJO) {
                    w->color = NEGRO;
                    x->padre->color = ROJO;
                    rotarDerecha(x->padre);
                    w = x->padre->izq;
                }
                if (w->der->color == NEGRO && w->izq->color == NEGRO) {
                    w->color = ROJO;
                    x = x->padre;
                } else {
                    if (w->izq->color == NEGRO) {
                        w->der->color = NEGRO;
                        w->color = ROJO;
                        rotarIzquierda(w);
                        w = x->padre->izq;
                    }
                    w->color = x->padre->color;
                    x->padre->color = NEGRO;
                    w->izq->color = NEGRO;
                    rotarDerecha(x->padre);
                    x = raiz;
                }
            }
        }
        x->color = NEGRO;
    }

    int verificar(NodoRB* v, long long lo, long long hi) {
        if (v == nil) return 1;
        if (!(lo <= v->clave && v->clave < hi)) return -1;
        if (v->color == ROJO && (v->izq->color == ROJO || v->der->color == ROJO)) return -1;
        if (v->izq != nil && v->izq->padre != v) return -1;
        if (v->der != nil && v->der->padre != v) return -1;
        int a = verificar(v->izq, lo, v->clave);
        int b = verificar(v->der, v->clave, hi);
        if (a == -1 || b == -1 || a != b) return -1;
        return a + (v->color == NEGRO ? 1 : 0);
    }

    void inorder(NodoRB* v) {
        if (v == nil) return;
        inorder(v->izq);
        cout << v->clave << (v->color == ROJO ? "R " : "N ");
        inorder(v->der);
    }

    void liberar(NodoRB* v) {
        if (v == nil) return;
        liberar(v->izq);
        liberar(v->der);
        delete v;
    }
};