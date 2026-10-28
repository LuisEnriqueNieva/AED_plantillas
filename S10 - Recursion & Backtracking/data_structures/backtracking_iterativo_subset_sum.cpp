#include <iostream>
#include <vector>
using namespace std;

struct Estado {
    vector<int> indices; // Valores de decisión en cada nivel (s en el pseudocódigo)
    int tact;           // Suma parcial acumulada (acumulador)
};

void Generar(int nivel, Estado& estado, const vector<int>& nums);
bool Solucion(int nivel, int n, const Estado& estado, int target);
bool Criterio(int nivel, int n, const Estado& estado, int target);
bool MasHermanos(int nivel, const Estado& estado);
void Retroceder(int& nivel, Estado& estado, const vector<int>& nums);

void BacktrackingIterativo(int n, const vector<int>& nums, int target) {
    int nivel = 0;
    bool fin = false;
    Estado estado;
    estado.indices.resize(n, -1);  // Índices de las decisiones por nivel (s en el pseudocódigo)
    estado.tact = 0;               // Inicializar suma parcial

    while (!fin) {
        Generar(nivel, estado, nums);

        if (Solucion(nivel, n, estado, target)) {
            cout << "Solución encontrada: ";
            for (int i = 0; i <= nivel; ++i)
                if (estado.indices[i] == 1) cout << nums[i] << " ";
            cout << endl;
        } 

        bool avanzar = Criterio(nivel, n, estado, target) && nivel + 1 < n;
        
        if (avanzar) {
            nivel++; // Avanzar al siguiente nivel
        } else {
            // Retroceder y buscar más hermanos
            while (nivel >= 0 && !MasHermanos(nivel, estado)) {
                Retroceder(nivel, estado, nums);
            }
            if (nivel < 0) fin = true;
        }
    }
}

// Generar (nivel, s) 
//     s[nivel]:= s[nivel] + 1 
//     si s[nivel] == 1  entonces   tact:= tact + t[nivel]
void Generar(int nivel, Estado& estado, const vector<int>& nums) {
    estado.indices[nivel]++;
    if (estado.indices[nivel] == 1) {
        estado.tact += nums[nivel];
    }
}

// Solución (nivel, s) 
//     devolver (nivel == n) Y (tact == P)
bool Solucion(int nivel, int n, const Estado& estado, int target) {
    return nivel == n - 1 && estado.tact == target;
}

// Criterio (nivel, s) 
//     devolver (nivel < n) Y (tact ≤ P)
bool Criterio(int nivel, int n,  const Estado& estado, int target) {
    return nivel < n - 1 && estado.tact <= target;
}

// MasHermanos (nivel, s)
//     devolver s[nivel] < 1
bool MasHermanos(int nivel, const Estado& estado) {
    return estado.indices[nivel] < 1;
}

// Retroceder (nivel, s) 
//     tact:= tact – t[nivel]*s[nivel] 
//     s[nivel]:= -1 
//     nivel:= nivel – 1
void Retroceder(int& nivel, Estado& estado, const vector<int>& nums) {
    estado.tact -= nums[nivel] * estado.indices[nivel];
    estado.indices[nivel] = -1;
    nivel--;
}

int main() {
    vector<int> nums = {3, 6, 4, 12, 5, 2};
    int target = 9;

    cout << "Subset Sum (Backtracking Iterativo)" << endl;
    cout << "Target = " << target << endl;
    cout << "Conjunto: ";
    for (int x : nums) cout << x << " ";
    cout << endl;

    BacktrackingIterativo(nums.size(), nums, target);

    return 0;
}
