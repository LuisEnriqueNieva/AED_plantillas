#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class DequeCircular {
public:
    explicit DequeCircular(int capacidad = 1) : buf(capacidad) {}
    int cap() const { 
        return (int) buf.size(); 
    }
    bool empty() const { 
        
        return cnt == 0; }
    int size() const { return cnt; }
    void push_back(T x) { if (cnt == cap()) crecer(); buf[(frente + cnt) % cap()] = x; cnt++; }
    void push_front(T x) { if (cnt == cap()) crecer(); frente = (frente - 1 + cap()) % cap(); buf[frente] = x; cnt++; }
    void pop_back() { cnt--; }
    void pop_front() { frente = (frente + 1) % cap(); cnt--; }
    T front() const { return buf[frente]; }
    T back() const { return buf[(frente + cnt - 1) % cap()]; }

    friend ostream& operator<<(ostream& os, DequeCircular d) {
        for (int i = 0; i < d.cnt; i++) os << d.buf[(d.frente + i) % d.cap()] << " ";
        return os;
    }

private:
    vector<T> buf;
    int frente = 0, cnt = 0;
    void crecer() {
        vector<T> nuevo(max(1, cap() * 2));
        for (int i = 0; i < cnt; i++) nuevo[i] = buf[(frente + i) % cap()];
        buf = nuevo;
        frente = 0;
    }
};


int main() {
    return 0;
}