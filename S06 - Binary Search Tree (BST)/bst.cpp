#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename T>
struct NodoBST {
    T dato;
    NodoBST* izq = nullptr;
    NodoBST* der = nullptr;
    NodoBST(T d) : dato(d) {}
};

template<typename T>
struct BST {
    NodoBST<T>* raiz = nullptr;

    void insertar(T valor) {
        raiz = insertarRec(raiz, valor);
    }


    bool buscar(T valor) {
        return buscarRec(raiz, valor);
    }

    void eliminar(T valor) {
        raiz = eliminarRec(raiz, valor);
    }

    T minimo() {
        NodoBST<T>* actual = raiz;
        while (actual->izq != nullptr) actual = actual->izq;
        return actual->dato;
    }

    T maximo() {
        NodoBST<T>* actual = raiz;
        while (actual->der != nullptr) actual = actual->der;
        return actual->dato;
    }

    vector<T> inorder() {
        vector<T> resultado;
        inorderRec(raiz, resultado);
        return resultado;
    }

    vector<T> preorder() {
        vector<T> resultado;
        preorderRec(raiz, resultado);
        return resultado;
    }

    vector<T> postorder() {
        vector<T> resultado;
        postorderRec(raiz, resultado);
        return resultado;
    }

    T find_predecesor(NodoBST<T>* nodo) {
        nodo = nodo->izq;                               
        while (nodo->der != nullptr) nodo = nodo->der;    
        return nodo->dato;
    }

    T find_sucesor(NodoBST<T>* nodo) {
        nodo = nodo->der;
        while (nodo->izq != nullptr) nodo = nodo->izq;
        return nodo->dato;
    }

    int altura(NodoBST<T>* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + max(altura(nodo->izq), altura(nodo->der));
    }

    int contarNodos(NodoBST<T>* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + contarNodos(nodo->izq) + contarNodos(nodo->der);
    }

    int contarHojas(NodoBST<T>* nodo) {
        if (nodo == nullptr) return 0;
        if (nodo->izq == nullptr && nodo->der == nullptr) return 1;
        return contarHojas(nodo->izq) + contarHojas(nodo->der);
    }

    NodoBST<T>* lca(NodoBST<T>* nodo, T p, T q) {
        if (nodo == nullptr) return nullptr;
        if (p < nodo->dato && q < nodo->dato)
            return lca(nodo->izq, p, q);
        if (p > nodo->dato && q > nodo->dato)
            return lca(nodo->der, p, q);
        return nodo; 
    }

    int sumaRango(NodoBST<T>* nodo, T L, T R) {
        if (nodo == nullptr) return 0;
        if (nodo->dato < L) return sumaRango(nodo->der, L, R);
        if (nodo->dato > R) return sumaRango(nodo->izq, L, R);
        return nodo->dato + sumaRango(nodo->izq, L, R) + sumaRango(nodo->der, L, R);
    }

    bool estaBalanceado(NodoBST<T>* nodo) {
        if (nodo == nullptr) return true;
        int hIzq = altura(nodo->izq);
        int hDer = altura(nodo->der);
        if (abs(hIzq - hDer) > 1) return false;
        return estaBalanceado(nodo->izq) && estaBalanceado(nodo->der);
    }

private:
    NodoBST<T>* insertarRec(NodoBST<T>* nodo, T valor) {
        if (nodo == nullptr) return new NodoBST<T>(valor);
        if (valor < nodo->dato) nodo->izq = insertarRec(nodo->izq, valor);
        else if (valor > nodo->dato) nodo->der = insertarRec(nodo->der, valor);
        return nodo;
    }


    bool buscarRec(NodoBST<T>* nodo, T valor) {
        if (nodo == nullptr) return false;
        if (valor == nodo->dato) return true;
        if (valor < nodo->dato) return buscarRec(nodo->izq, valor);
        return buscarRec(nodo->der, valor);
    }

    NodoBST<T>* minimoNodo(NodoBST<T>* nodo) {
        while (nodo->izq != nullptr) nodo = nodo->izq;
        return nodo;
    }

    NodoBST<T>* eliminarRec(NodoBST<T>* nodo, T valor) {
        if (nodo == nullptr) return nullptr;
        if (valor < nodo->dato) {
            nodo->izq = eliminarRec(nodo->izq, valor);
        } else if (valor > nodo->dato) {
            nodo->der = eliminarRec(nodo->der, valor);
        } else {
            if (nodo->izq == nullptr) {
                NodoBST<T>* temp = nodo->der;
                delete nodo;
                return temp;
            }
            if (nodo->der == nullptr) {
                NodoBST<T>* temp = nodo->izq;
                delete nodo;
                return temp;
            }
            NodoBST<T>* sucesor = minimoNodo(nodo->der);
            nodo->dato = sucesor->dato;
            nodo->der = eliminarRec(nodo->der, sucesor->dato);
        }
        return nodo;
    }

    void inorderRec(NodoBST<T>* nodo, vector<T>& resultado) {
        if (nodo == nullptr) return;
        inorderRec(nodo->izq, resultado);
        resultado.push_back(nodo->dato);
        inorderRec(nodo->der, resultado);
    }

    void preorderRec(NodoBST<T>* nodo, vector<T>& resultado) {
        if (nodo == nullptr) return;
        resultado.push_back(nodo->dato);
        preorderRec(nodo->izq, resultado);
        preorderRec(nodo->der, resultado);
    }

    void postorderRec(NodoBST<T>* nodo, vector<T>& resultado) {
        if (nodo == nullptr) return;
        postorderRec(nodo->izq, resultado);
        postorderRec(nodo->der, resultado);
        resultado.push_back(nodo->dato);
    }
};


void pruebas(){
    BST<int> arbol;
    
    for (int v : {8, 3, 10, 1, 6}) arbol.insertar(v);

    vector<int> in = arbol.inorder();
    vector<int> pre = arbol.preorder();
    vector<int> post = arbol.postorder();

    vector<int> inEsperado = {1, 3, 6, 8, 10};
    vector<int> preEsperado = {8, 3, 1, 6, 10};
    vector<int> postEsperado = {1, 6, 3, 10, 8};

    assert(in == inEsperado);
    assert(pre == preEsperado);
    assert(post == postEsperado);

    cout << "inorder:   ";
    for (int v : in) cout << v << " ";
    cout << "(esperado 1 3 6 8 10)" << endl;

    cout << "preorder:  ";
    for (int v : pre) cout << v << " ";
    cout << "(esperado 8 3 1 6 10)" << endl;

    cout << "postorder: ";
    for (int v : post) cout << v << " ";
    cout << "(esperado 1 6 3 10 8)" << endl;

    assert(arbol.buscar(6) == true);
    assert(arbol.buscar(100) == false);
    assert(arbol.minimo() == 1);
    assert(arbol.maximo() == 10);
    cout << "buscar(6)=" << arbol.buscar(6) << " buscar(100)=" << arbol.buscar(100)
         << " minimo()=" << arbol.minimo() << " maximo()=" << arbol.maximo() << endl;

    arbol.eliminar(1);
    assert(arbol.buscar(1) == false);
    vector<int> tras1 = arbol.inorder();
    vector<int> esperadoTras1 = {3, 6, 8, 10};
    assert(tras1 == esperadoTras1);

    arbol.eliminar(3);
    vector<int> tras2 = arbol.inorder();
    vector<int> esperadoTras2 = {6, 8, 10};
    assert(tras2 == esperadoTras2);

    arbol.eliminar(8);
    vector<int> tras3 = arbol.inorder();
    vector<int> esperadoTras3 = {6, 10};
    assert(tras3 == esperadoTras3);

    cout << "tras eliminar 1, 3 y 8 (raiz con dos hijos): inorder = ";
    for (int v : tras3) cout << v << " ";
    cout << "(esperado 6 10)" << endl;

    cout << "TODOS LOS ASSERTS PASARON" << endl;
}

int main() {
    
    return 0;
}