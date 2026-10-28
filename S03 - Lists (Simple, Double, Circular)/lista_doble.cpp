#include <iostream>
using namespace std;

template <typename T>
struct NodoDoble {
    T dato;
    NodoDoble* siguiente;
    NodoDoble* anterior;
    NodoDoble(T d) : dato(d), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
struct ListaDoble {
    NodoDoble<T>* head = nullptr;
    NodoDoble<T>* tail = nullptr;
    int n = 0;

    ListaDoble() = default;
    ListaDoble(const ListaDoble&) = delete;
    ListaDoble& operator=(const ListaDoble&) = delete;

    bool empty() const { return n == 0; }
    int size() const { return n; }

    void push_front(T x) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(x);
        nuevo->siguiente = head;
        if (head != nullptr) head->anterior = nuevo;
        else tail = nuevo;
        head = nuevo;
        n++;
    }

    void push_back(T x) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(x);
        nuevo->anterior = tail;
        if (tail != nullptr) tail->siguiente = nuevo;
        else head = nuevo;
        tail = nuevo;
        n++;
    }

    void insertar_despues(NodoDoble<T>* p, T x) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(x);
        nuevo->anterior = p;
        nuevo->siguiente = p->siguiente;
        if (p->siguiente != nullptr) p->siguiente->anterior = nuevo;
        else tail = nuevo;
        p->siguiente = nuevo;
        n++;
    }

    // O(1) dado solo el puntero al nodo
    void eliminar(NodoDoble<T>* p) {
        if (p->anterior) p->anterior->siguiente = p->siguiente;
        else head = p->siguiente;

        if (p->siguiente) p->siguiente->anterior = p->anterior;
        else tail = p->anterior;

        delete p;
        n--;
    }

    void pop_front() { if (!empty()) eliminar(head); }
    void pop_back()  { if (!empty()) eliminar(tail); }

    NodoDoble<T>* buscar(T x) const {
        NodoDoble<T>* p = head;
        while (p != nullptr && p->dato != x) p = p->siguiente;
        return p;
    }

    void imprimir() const {
        for (NodoDoble<T>* p = head; p != nullptr; p = p->siguiente)
            cout << p->dato << " ";
        cout << "\n";
    }

    void imprimir_reversa() const {
        for (NodoDoble<T>* p = tail; p != nullptr; p = p->anterior)
            cout << p->dato << " ";
        cout << "\n";
    }

    ~ListaDoble() {
        NodoDoble<T>* p = head;
        while (p != nullptr) {
            NodoDoble<T>* siguiente = p->siguiente;
            delete p;
            p = siguiente;
        }
    }
};

int main() {
    ListaDoble<int> L;
    L.push_back(5); L.push_back(3); L.push_back(8);
    L.push_front(9);
    L.imprimir();            // 9 5 3 8
    L.imprimir_reversa();    // 8 3 5 9
    L.eliminar(L.buscar(3));
    L.imprimir();            // 9 5 8
}