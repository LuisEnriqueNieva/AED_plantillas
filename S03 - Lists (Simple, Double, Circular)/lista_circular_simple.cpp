#include <iostream>
using namespace std;

template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo(T d) : dato(d), siguiente(nullptr) {}
};

template <typename T>
struct ListaCircularSimple {
    Nodo<T>* head = nullptr;
    Nodo<T>* tail = nullptr;
    int n = 0;

    ListaCircularSimple() = default;
    ListaCircularSimple(const ListaCircularSimple&) = delete;
    ListaCircularSimple& operator=(const ListaCircularSimple&) = delete;

    bool empty() const { return n == 0; }
    int size() const { return n; }

    void push_front(T x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        if (head == nullptr) {
            head = tail = nuevo;
            nuevo->siguiente = nuevo;     // se apunta a si mismo
        } else {
            nuevo->siguiente = head;
            tail->siguiente = nuevo;
            head = nuevo;
        }
        n++;
    }

    void push_back(T x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        if (head == nullptr) {
            head = tail = nuevo;
            nuevo->siguiente = nuevo;
        } else {
            nuevo->siguiente = head;
            tail->siguiente = nuevo;
            tail = nuevo;
        }
        n++;
    }

    void insertar_despues(Nodo<T>* p, T x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        nuevo->siguiente = p->siguiente;
        p->siguiente = nuevo;
        if (p == tail) tail = nuevo;
        n++;
    }

    void pop_front() {
        if (empty()) return;
        if (n == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Nodo<T>* viejo = head;
            head = head->siguiente;
            tail->siguiente = head;
            delete viejo;
        }
        n--;
    }

    // O(n): hay que encontrar el penultimo
    void pop_back() {
        if (empty()) return;
        if (n == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Nodo<T>* p = head;
            while (p->siguiente != tail) p = p->siguiente;
            p->siguiente = head;
            delete tail;
            tail = p;
        }
        n--;
    }

    Nodo<T>* buscar(T x) const {
        if (head == nullptr) return nullptr;
        Nodo<T>* p = head;
        do {
            if (p->dato == x) return p;
            p = p->siguiente;
        } while (p != head);
        return nullptr;
    }

    void imprimir() const {
        if (head == nullptr) { cout << "\n"; return; }
        Nodo<T>* p = head;
        do {
            cout << p->dato << " ";
            p = p->siguiente;
        } while (p != head);          // NO: while (p != nullptr)
        cout << "\n";
    }

    ~ListaCircularSimple() {
        Nodo<T>* p = head;
        for (int i = 0; i < n; i++) {   // n vueltas, no hay nullptr
            Nodo<T>* siguiente = p->siguiente;
            delete p;
            p = siguiente;
        }
    }
};

int main() {
    ListaCircularSimple<int> L;
    L.push_back(5); L.push_back(3); L.push_back(8);
    L.push_front(9);
    L.imprimir();            // 9 5 3 8
    L.pop_front(); L.pop_back();
    L.imprimir();            // 5 3
}