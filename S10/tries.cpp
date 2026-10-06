#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int ALFABETO = 26;   // solo letras minusculas a-z

struct NodoTrie {
    NodoTrie* hijos[ALFABETO];   // hijos[0] = 'a', hijos[1] = 'b', ... (nodo como arreglo)
    bool finPalabra;             // true si aqui termina una palabra (el "fin de cadena" de la PPT)
    NodoTrie() {
        finPalabra = false;
        for (int i = 0; i < ALFABETO; i++) hijos[i] = nullptr;
    }
    ~NodoTrie() {                // al borrar un nodo, borra todo lo que cuelga de el
        for (int i = 0; i < ALFABETO; i++) delete hijos[i];
    }
};

class Trie {
public:
    NodoTrie* raiz;
    Trie() { raiz = new NodoTrie(); }
    ~Trie() { delete raiz; }

    // ---------- INSERTAR: O(L) ----------
    void insertar(const string& palabra) {
        NodoTrie* n = raiz;
        for (char c : palabra) {
            int i = c - 'a';                         // 'a'->0, 'b'->1, ...
            if (n->hijos[i] == nullptr)              // falta esta letra: crear el nodo
                n->hijos[i] = new NodoTrie();
            n = n->hijos[i];                         // bajar
        }
        n->finPalabra = true;                        // marcar fin de palabra
    }

    // ---------- BUSCAR palabra: O(L) ----------
    bool buscar(const string& palabra) {
        NodoTrie* n = bajar(palabra);
        return n != nullptr && n->finPalabra;        // llegar Y estar marcado
    }

    // ---------- BUSCAR prefijo: O(L) ----------
    bool existePrefijo(const string& prefijo) {
        return bajar(prefijo) != nullptr;            // basta con poder bajar
    }

    // ---------- ELIMINAR: O(L) ----------
    void eliminar(const string& palabra) {
        eliminarRec(raiz, palabra, 0);
    }

    // ---------- AUTOCOMPLETAR: O(L + subarbol) ----------
    vector<string> autocompletar(const string& prefijo) {
        vector<string> resultado;
        NodoTrie* n = bajar(prefijo);                // 1) bajar hasta el final del prefijo
        if (n != nullptr) recolectar(n, prefijo, resultado);  // 2) listar todo lo que cuelga
        return resultado;
    }

private:
    // Baja siguiendo las letras de s. Devuelve el nodo final, o nullptr si el camino no existe
    NodoTrie* bajar(const string& s) {
        NodoTrie* n = raiz;
        for (char c : s) {
            n = n->hijos[c - 'a'];
            if (n == nullptr) return nullptr;
        }
        return n;
    }

    bool tieneHijos(NodoTrie* n) {
        for (int i = 0; i < ALFABETO; i++)
            if (n->hijos[i] != nullptr) return true;
        return false;
    }

    // Devuelve true si el nodo n quedo inutil y su padre debe borrarlo
    bool eliminarRec(NodoTrie* n, const string& p, int pos) {
        if (pos == (int)p.size()) {                  // llegue al final de la palabra
            if (!n->finPalabra) return false;        // la palabra no existia
            n->finPalabra = false;                   // quitar la marca
            return !tieneHijos(n);                   // si no tiene hijos, se puede borrar
        }
        int i = p[pos] - 'a';
        NodoTrie* h = n->hijos[i];
        if (h == nullptr) return false;              // camino inexistente: nada que borrar
        if (eliminarRec(h, p, pos + 1)) {            // el hijo quedo inutil: borrarlo
            delete h;
            n->hijos[i] = nullptr;
            // yo tambien soy inutil si no soy fin de otra palabra y no me quedan hijos
            return !n->finPalabra && !tieneHijos(n);
        }
        return false;                                // el hijo se queda: aqui paro de borrar
    }

    // Recorre todo el subarbol de n, agregando cada palabra completa (orden alfabetico)
    void recolectar(NodoTrie* n, string actual, vector<string>& res) {
        if (n->finPalabra) res.push_back(actual);
        for (int i = 0; i < ALFABETO; i++)
            if (n->hijos[i] != nullptr)
                recolectar(n->hijos[i], actual + char('a' + i), res);
    }
};