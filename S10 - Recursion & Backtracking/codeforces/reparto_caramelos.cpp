#include <iostream>
#include <vector>
using namespace std;

vector<int> bolsas;

void reparto(int quedan, int tope) {
    if (quedan == 0){
        for (auto it: bolsas) cout << it << " ";
        cout << endl;
    }

    for (int v = min(tope, quedan); v>=1; v--){
        bolsas.push_back(v);
        reparto(quedan-v, v);
        bolsas.pop_back();
    }
}

int main() {
    int n;
    cin >> n;
    reparto(n,n);

    return 0;
}
