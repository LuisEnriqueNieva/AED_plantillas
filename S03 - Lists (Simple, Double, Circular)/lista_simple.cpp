#include <iostream>
using namespace std;

template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo(T d) : dato(d), siguiente(nullptr) {}
};

template <typename T>
struct ListaSimple {
    Nodo<T>* head = nullptr;
    Nodo<T>* tail = nullptr;
    int n = 0;

    ListaSimple() = default;
    ListaSimple(const ListaSimple&) = delete;
    ListaSimple& operator=(const ListaSimple&) = delete;

    bool empty() const { return n == 0; }
    int size() const { return n; }

    void push_front(T x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        nuevo->siguiente = head;
        head = nuevo;
        if (tail == nullptr) tail = nuevo;
        n++;
    }

    void push_back(T x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        if (tail == nullptr) head = tail = nuevo;
        else { tail->siguiente = nuevo; tail = nuevo; }
        n++;
    }

    // O(1) si ya tienes el puntero p
    void insertar_despues(Nodo<T>* p, T x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        nuevo->siguiente = p->siguiente;
        p->siguiente = nuevo;
        if (p == tail) tail = nuevo;
        n++;
    }

    void pop_front() {
        if (empty()) return;
        Nodo<T>* viejo = head;
        head = head->siguiente;
        if (head == nullptr) tail = nullptr;
        delete viejo;
        n--;
    }

    // O(n): hay que recorrer para encontrar el penultimo
    void pop_back() {
        if (empty()) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            n = 0;
            return;
        }
        Nodo<T>* p = head;
        while (p->siguiente != tail) p = p->siguiente;
        delete tail;
        tail = p;
        tail->siguiente = nullptr;
        n--;
    }

    // elimina el nodo SIGUIENTE a p, O(1)
    void eliminar_despues(Nodo<T>* p) {
        Nodo<T>* viejo = p->siguiente;
        if (viejo == nullptr) return;
        p->siguiente = viejo->siguiente;
        if (viejo == tail) tail = p;
        delete viejo;
        n--;
    }

    Nodo<T>* buscar(T x) const {
        Nodo<T>* p = head;
        while (p != nullptr && p->dato != x) p = p->siguiente;
        return p;
    }

    void imprimir() const {
        for (Nodo<T>* p = head; p != nullptr; p = p->siguiente)
            cout << p->dato << " ";
        cout << "\n";
    }

    ~ListaSimple() {
        Nodo<T>* p = head;
        while (p != nullptr) {
            Nodo<T>* siguiente = p->siguiente;
            delete p;
            p = siguiente;
        }
    }
};

int main() {
    ListaSimple<int> L;
    L.push_back(5); L.push_back(3); L.push_back(8);
    L.push_front(9);
    L.imprimir();                       // 9 5 3 8
    L.insertar_despues(L.buscar(5), 7);
    L.imprimir();                       // 9 5 7 3 8
    L.pop_front(); L.pop_back();
    L.imprimir();                       // 5 7 3
}