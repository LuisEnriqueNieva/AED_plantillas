#include <iostream>
#include <vector>
using namespace std;

struct Estado {
    vector<int> indices;  // Valores de decisión en cada nivel (s en el pseudocódigo)
    int peso_actual;      // Peso acumulado de los objetos seleccionados
    int beneficio_actual; // Beneficio acumulado de los objetos seleccionados
};

void Generar(int nivel, Estado& estado, const vector<int>& pesos, const vector<int>& beneficios);
bool Solucion(int nivel, int n, const Estado& estado, int capacidad);
bool Criterio(int nivel, int n, const Estado& estado, int capacidad);
bool MasHermanos(int nivel, const Estado& estado);
void Retroceder(int& nivel, Estado& estado, const vector<int>& pesos, const vector<int>& beneficios);

void BacktrackingIterativoMochila(int n, const vector<int>& pesos, const vector<int>& beneficios, int capacidad) {
    int nivel = 0;
    bool fin = false;
    Estado estado;
    estado.indices.resize(n, -1);  
    estado.peso_actual = 0;        
    estado.beneficio_actual = 0;   

    int mejor_beneficio = 0;
    vector<int> mejor_solucion(n, 0);

    while (!fin) {
        Generar(nivel, estado, pesos, beneficios);

        if (Solucion(nivel, n, estado, capacidad)) {
            // Encontramos una solución completa, verificamos si es mejor
            if (estado.beneficio_actual > mejor_beneficio) {
                mejor_beneficio = estado.beneficio_actual;
                for (int i = 0; i < n; ++i) {
                    mejor_solucion[i] = estado.indices[i];
                }
            }
        } 

        bool avanzar = Criterio(nivel, n, estado, capacidad);
        
        if (avanzar) {
            nivel++; // Avanzar al siguiente nivel
        } else {
            // Retroceder y buscar más hermanos
            while (nivel >= 0 && !MasHermanos(nivel, estado)) {
                Retroceder(nivel, estado, pesos, beneficios);
            }
            if (nivel < 0) fin = true;
        }
    }

    // Mostrar la mejor solución encontrada
    cout << "\nMejor solución final:" << endl;
    cout << "Objetos seleccionados: ";
    for (int i = 0; i < n; ++i) {
        if (mejor_solucion[i] == 1) 
            cout << i << " ";
    }
    cout << endl;
    cout << "Peso total: ";
    int peso_total = 0;
    for (int i = 0; i < n; ++i) {
        if (mejor_solucion[i] == 1)
            peso_total += pesos[i];
    }
    cout << peso_total << "/" << capacidad << endl;
    cout << "Beneficio total: " << mejor_beneficio << endl;
}

// Generar (nivel, s) 
// s[nivel]:= s[nivel] + 1 
// si s[nivel] == 1 entonces actualizar peso_actual y beneficio_actual
void Generar(int nivel, Estado& estado, const vector<int>& pesos, const vector<int>& beneficios) {
    estado.indices[nivel]++;
    if (estado.indices[nivel] == 1) {
        estado.peso_actual += pesos[nivel];
        estado.beneficio_actual += beneficios[nivel];
    }
}

// Solución (nivel, s) 
// devolver (nivel == n-1)
bool Solucion(int nivel, int n, const Estado& estado, int capacidad) {
    return nivel == n - 1 && estado.peso_actual <= capacidad;
}

// Criterio (nivel, s) 
// devolver (nivel < n) Y (peso_actual ≤ capacidad)
bool Criterio(int nivel, int n, const Estado& estado, int capacidad) {
    return nivel < n - 1 && estado.peso_actual <= capacidad;
}

// MasHermanos (nivel, s)
// devolver s[nivel] < 1
bool MasHermanos(int nivel, const Estado& estado) {
    return estado.indices[nivel] < 1;
}

// Retroceder (nivel, s) 
// si s[nivel] == 1 entonces restar peso y beneficio
// s[nivel]:= -1 
// nivel:= nivel - 1
void Retroceder(int& nivel, Estado& estado, const vector<int>& pesos, const vector<int>& beneficios) {
    if (estado.indices[nivel] == 1) {
        estado.peso_actual -= pesos[nivel];
        estado.beneficio_actual -= beneficios[nivel];
    }
    estado.indices[nivel] = -1;
    nivel--;
}

int main() {
    vector<int> pesos = {4, 2, 3, 1};
    vector<int> beneficios = {10, 4, 7, 2};
    int capacidad = 5;

    cout << "Problema de la Mochila (Backtracking Iterativo)" << endl;
    cout << "Capacidad de la mochila: " << capacidad << endl;
    cout << "Objetos disponibles: " << pesos.size() << endl;
    
    cout << "\nObjeto\tPeso\tBeneficio" << endl;
    for (size_t i = 0; i < pesos.size(); ++i) {
        cout << i << "\t" << pesos[i] << "\t" << beneficios[i] << endl;
    }
    cout << endl;

    BacktrackingIterativoMochila(pesos.size(), pesos, beneficios, capacidad);

    return 0;
}
