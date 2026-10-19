#include <iostream>
#include <string>
using namespace std;

int n;
string s;

void gen(int pos) {
    if (pos == n) {
        cout << s << "\n";
        return;
    }
    for (char d : {'0', '1'}) {
        if (d == '1' && pos > 0 && s.back() == '1') continue;  // poda
        s.push_back(d);     // hacer
        gen(pos + 1);       // explorar
        s.pop_back();       // deshacer
    }
}

int main() {
    cin >> n;
    gen(0);
    return 0;
}