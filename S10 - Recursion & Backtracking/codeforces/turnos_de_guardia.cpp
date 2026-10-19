#include <iostream>
#include <vector>
using namespace std;

int n, k;
string turnos;
vector<string> planes;

void rep(int pos, int cuentaA) {
    if (pos == n) {
        if (cuentaA == k) {
            planes.push_back(turnos);
        }
        return;
    }
    for (char d : {'A', 'B', 'C'}) {
        if (turnos.size() >= 2 &&
            turnos[turnos.size() - 1] == d &&
            turnos[turnos.size() - 2] == d) continue;
        
        if (d == 'A' && cuentaA == k) continue;
        turnos.push_back(d);
        rep(pos + 1, cuentaA + (d == 'A'));
        turnos.pop_back();
    }
}

int main() {
    cin >> n >> k;
    rep(0, 0);
    cout << planes.size() << "\n";
    for (auto& s : planes) cout << s << "\n";
    
    return 0;
}