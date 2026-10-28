#include <iostream>
#include <vector>
using namespace std;

vector<int> elementos = {1, 2, 3};
vector<int> c;

void sub(int pos) {
    if (pos == elementos.size()) {
        for (int x : c) cout << x << " ";
        cout << "\n";
        return;
    }
    c.push_back(elementos[pos]);   // incluir
    sub(pos + 1);
    c.pop_back();                  // deshacer
    sub(pos + 1);                  // no incluir
}

int main() {
    sub(0);
    return 0;
}