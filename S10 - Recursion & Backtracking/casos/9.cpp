#include <iostream>
#include <vector>
using namespace std;

void hanoi(int n, char desde, char hasta, char aux) {
    if (n == 0) return;
    hanoi(n - 1, desde, aux, hasta);
    cout << "disco " << n << ": " << desde << " -> " << hasta << "\n";
    hanoi(n - 1, aux, hasta, desde);
}

long long evalPref(const vector<string>& t, int& pos) {      // pos avanza por referencia
    string tok = t[pos++];
    if (tok == "+" || tok == "-" || tok == "*") {
        long long x = evalPref(t, pos), y = evalPref(t, pos);
        return tok == "+" ? x + y : tok == "-" ? x - y : x * y;
    }
    return stoll(tok);
}