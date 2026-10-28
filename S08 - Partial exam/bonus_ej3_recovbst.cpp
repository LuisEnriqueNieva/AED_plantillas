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


int main() {
    int cuantos; 
    cin >> cuantos;
    vector<int> valores(cuantos + 2);
    for (int i = 1; i <= cuantos; i++) cin >> valores[i];
    auto comun = [](int x, int y) {
        while (y != 0) {
            int resto = x % y;
            x = y;
            y = resto;
        }
        return x;
    };

    vector<vector<char>> unidos(cuantos + 2, vector<char>(cuantos + 2, 0));
    for (int i = 1; i <= cuantos; i++)
        for (int j = 1; j <= cuantos; j++)
            unidos[i][j] = comun(valores[i], valores[j]) > 1;

    vector<vector<char>> cuelgaIzq(cuantos + 3, vector<char>(cuantos + 3, 0));
    vector<vector<char>> cuelgaDer(cuantos + 3, vector<char>(cuantos + 3, 0));
    vector<vector<int>> raizIzq(cuantos + 3, vector<int>(cuantos + 3, 0));
    vector<vector<int>> raizDer(cuantos + 3, vector<int>(cuantos + 3, 0));
    int raizTotal = 0;

    for (int largo = 1; largo <= cuantos; largo++) {
        for (int ini = 1; ini + largo - 1 <= cuantos; ini++) {
            int fin = ini + largo - 1;
            for (int cen = ini; cen <= fin; cen++) {
                bool ladoIzq = (cen == ini) || cuelgaIzq[ini][cen - 1];
                bool ladoDer = (cen == fin) || cuelgaDer[cen + 1][fin];
                if (!ladoIzq || !ladoDer) continue;
                if (ini == 1 && fin == cuantos) raizTotal = cen;
                if (fin + 1 <= cuantos && unidos[cen][fin + 1]) {
                    cuelgaIzq[ini][fin] = 1;
                    raizIzq[ini][fin] = cen;
                }
                if (ini - 1 >= 1 && unidos[cen][ini - 1]) {
                    cuelgaDer[ini][fin] = 1;
                    raizDer[ini][fin] = cen;
                }
            }
        }
    }

    if (raizTotal == 0) { 
        cout << "No" << endl; 
        return 0; 
    }

    BST<int> arbol;
    vector<vector<int>> pendientes;
    pendientes.push_back({1, cuantos, 0});
    while (!pendientes.empty()) {
        vector<int> tramo = pendientes.back();
        pendientes.pop_back();
        int ini = tramo[0], fin = tramo[1], tipo = tramo[2];
        if (ini > fin) continue;
        int cen;
        if (tipo == 0) cen = raizTotal;
        else if (tipo == 1) cen = raizIzq[ini][fin];
        else cen = raizDer[ini][fin];
        arbol.insertar(valores[cen]);
        pendientes.push_back({ini, cen - 1, 1});
        pendientes.push_back({cen + 1, fin, 2});
    }

    vector<int> orden = arbol.inorder();
    bool coincide = ((int)orden.size() == cuantos);
    for (int i = 0; coincide && i < cuantos; i++)
        if (orden[i] != valores[i + 1]) coincide = false;

    vector<NodoBST<int>*> visita;
    visita.push_back(arbol.raiz);
    while (coincide && !visita.empty()) {
        NodoBST<int>* actual = visita.back();
        visita.pop_back();
        if (actual->izq != nullptr) {
            if (comun(actual->dato, actual->izq->dato) <= 1) coincide = false;
            visita.push_back(actual->izq);
        }
        if (actual->der != nullptr) {
            if (comun(actual->dato, actual->der->dato) <= 1) coincide = false;
            visita.push_back(actual->der);
        }
    }

    cout << (coincide ? "Yes" : "No") << endl;
    return 0;
}



