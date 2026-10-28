#include <iostream>
#include <vector>
#include <algorithm>

struct MinHeap {
    std::vector<int> H;
    int padre(int i) {
    return (i - 1) / 2;
    }
    int izq(int i) {
    return 2 * i + 1;
    }
    int der(int i) {
    return 2 * i + 2;
    }
    int tamano() {
    return (int)H.size();
    }
    void siftUp(int i) {
    while (i > 0 && H[padre(i)] > H[i]) {
    std::swap(H[padre(i)], H[i]);
    i = padre(i);
    }
    }
    void insertar(int x) {
    H.push_back(x);
    siftUp(tamano() - 1);
    }
    void siftDown(int i, int n) {
    while (true) {
    int m = i;
    if (izq(i) < n && H[izq(i)] < H[m]) {
    m = izq(i);
    }
    if (der(i) < n && H[der(i)] < H[m]) {
    m = der(i);
    }
    if (m == i) {
    break;
    }
    std::swap(H[i], H[m]);
    i = m;
    }
    }
    int extraerExtremo() {
    int n = tamano();
    if (n == 0) return -1;
    int minVal = H[0];
    H[0] = H[n - 1];
    H.pop_back();
    if (tamano() > 0) {
    siftDown(0, tamano());
    }
    return minVal;
    }
    void construirHeap(const std::vector<int>& arreglo) {
    H = arreglo;
    int n = tamano();
    for (int i = (n / 2) - 1; i >= 0; i--) {
    siftDown(i, n);
    }
    }
    void imprimir() {
    for (int i = 0; i < tamano(); i++) {
    std::cout << H[i] << " ";
    }
    std::cout << "\n";
    }
    };
    int main() {
    MinHeap heap;
    heap.insertar(9);
    heap.insertar(5);
    heap.insertar(2);
    heap.insertar(7);
    heap.insertar(1);
    heap.imprimir();
    std::cout << heap.extraerExtremo() << "\n";
    heap.imprimir();
    std::vector<int> datos = {14, 8, 10, 3, 5, 1, 6};
    heap.construirHeap(datos);
    heap.imprimir();
    return 0;
    }