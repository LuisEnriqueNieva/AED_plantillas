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
struct ListaCircularDoble {
    NodoDoble<T>* head = nullptr;
    NodoDoble<T>* tail = nullptr;
    int n = 0;

    ListaCircularDoble() = default;
    ListaCircularDoble(const ListaCircularDoble&) = delete;
    ListaCircularDoble& operator=(const ListaCircularDoble&) = delete;

    bool empty() const { return n == 0; }
    int size() const { return n; }

    void push_front(T x) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(x);
        if (head == nullptr) {
            head = tail = nuevo;
            nuevo->siguiente = nuevo->anterior = nuevo;
        } else {
            nuevo->siguiente = head;
            nuevo->anterior = tail;
            head->anterior = nuevo;
            tail->siguiente = nuevo;
            head = nuevo;
        }
        n++;
    }

    void push_back(T x) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(x);
        if (head == nullptr) {
            head = tail = nuevo;
            nuevo->siguiente = nuevo->anterior = nuevo;
        } else {
            nuevo->anterior = tail;
            nuevo->siguiente = head;
            tail->siguiente = nuevo;
            head->anterior = nuevo;
            tail = nuevo;
        }
        n++;
    }

    void insertar_despues(NodoDoble<T>* p, T x) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(x);
        nuevo->anterior = p;
        nuevo->siguiente = p->siguiente;
        p->siguiente->anterior = nuevo;
        p->siguiente = nuevo;
        if (p == tail) tail = nuevo;
        n++;
    }

    // O(1) dado solo el puntero al nodo
    void eliminar(NodoDoble<T>* p) {
        if (n == 1) {
            head = tail = nullptr;
        } else {
            p->anterior->siguiente = p->siguiente;
            p->siguiente->anterior = p->anterior;
            if (p == head) head = p->siguiente;
            if (p == tail) tail = p->anterior;
        }
        delete p;
        n--;
    }

    void pop_front() { if (!empty()) eliminar(head); }
    void pop_back()  { if (!empty()) eliminar(tail); }

    NodoDoble<T>* buscar(T x) const {
        if (head == nullptr) return nullptr;
        NodoDoble<T>* p = head;
        do {
            if (p->dato == x) return p;
            p = p->siguiente;
        } while (p != head);
        return nullptr;
    }

    void imprimir() const {
        if (head == nullptr) { cout << "\n"; return; }
        NodoDoble<T>* p = head;
        do {
            cout << p->dato << " ";
            p = p->siguiente;
        } while (p != head);
        cout << "\n";
    }

    void imprimir_reversa() const {
        if (tail == nullptr) { cout << "\n"; return; }
        NodoDoble<T>* p = tail;
        do {
            cout << p->dato << " ";
            p = p->anterior;
        } while (p != tail);
        cout << "\n";
    }

    ~ListaCircularDoble() {
        NodoDoble<T>* p = head;
        for (int i = 0; i < n; i++) {
            NodoDoble<T>* siguiente = p->siguiente;
            delete p;
            p = siguiente;
        }
    }
};

int main() {
    ListaCircularDoble<int> L;
    L.push_back(5); L.push_back(3); L.push_back(8);
    L.push_front(9);
    L.imprimir();            // 9 5 3 8
    L.imprimir_reversa();    // 8 3 5 9
    L.pop_back();
    L.eliminar(L.buscar(5));
    L.imprimir();            // 9 3
}