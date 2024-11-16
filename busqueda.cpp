#include <iostream>
#include <limits>
using namespace std;

// Nodo de un árbol binario
template<typename T>
class NodoArbol {
    T dato;
    NodoArbol* izquierdo;
    NodoArbol* derecho;

public:
    NodoArbol(T dato) : dato(dato), izquierdo(nullptr), derecho(nullptr) {}

    T getDato() { return dato; }
    NodoArbol* getIzquierdo() { return izquierdo; }
    NodoArbol* getDerecho() { return derecho; }

    void setIzquierdo(NodoArbol* nodo) { izquierdo = nodo; }
    void setDerecho(NodoArbol* nodo) { derecho = nodo; }
};

// Clase para el árbol binario
template<typename T>
class ArbolBinario {
    NodoArbol<T>* raiz;

public:
    ArbolBinario() : raiz(nullptr) {}

    // Método para insertar un nodo en el árbol
    void insertar(T valor) {
        raiz = insertarRecursivo(raiz, valor);
    }

    // Método de búsqueda en el árbol
    bool buscar(T valor) {
        return buscarRecursivo(raiz, valor);
    }

    // Método para imprimir el árbol (inorden)
    void imprimirInorden() {
        imprimirInordenRecursivo(raiz);
        cout << endl;
    }

private:
    // Método auxiliar recursivo para insertar un nodo
    NodoArbol<T>* insertarRecursivo(NodoArbol<T>* nodo, T valor) {
        if (!nodo) {
            return new NodoArbol<T>(valor);
        }
        if (valor < nodo->getDato()) {
            nodo->setIzquierdo(insertarRecursivo(nodo->getIzquierdo(), valor));
        } else {
            nodo->setDerecho(insertarRecursivo(nodo->getDerecho(), valor));
        }
        return nodo;
    }

    // Método auxiliar recursivo para buscar un valor en el árbol
    bool buscarRecursivo(NodoArbol<T>* nodo, T valor) {
        if (!nodo) {
            return false;
        }
        if (valor == nodo->getDato()) {
            return true;
        }
        if (valor < nodo->getDato()) {
            return buscarRecursivo(nodo->getIzquierdo(), valor);
        } else {
            return buscarRecursivo(nodo->getDerecho(), valor);
        }
    }

    // Método auxiliar recursivo para imprimir el árbol en inorden
    void imprimirInordenRecursivo(NodoArbol<T>* nodo) {
        if (!nodo) {
            return;
        }
        imprimirInordenRecursivo(nodo->getIzquierdo());
        cout << nodo->getDato() << " ";
        imprimirInordenRecursivo(nodo->getDerecho());
    }
};

int main() {
    ArbolBinario<int> arbol;
    int raiz;
    
    cout << "Introduce el valor de la raiz (debe ser un numero entero positivo): ";
    while (true) {
        cin >> raiz;
        if (raiz > 0 && cin.good()) break;

        cout << "Valor invalido. Introduce un numero entero positivo para la raiz: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    char continuar;
    do {
        int valor;
        cout << "Introduce un valor entero positivo que sea divisible por " << raiz << ": ";
        while (true) {
            cin >> valor;
            if (valor > 0 && valor % raiz == 0 && cin.good()) break;
            cout << "Valor invalido. Introduce un numero entero positivo divisible por " << raiz << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        arbol.insertar(valor);
        
        cout << "¿Quieres introducir otro valor? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');
    
    cout << "Asrbol en inorden: ";
    arbol.imprimirInorden();

    int valorBuscado;
    cout << "Introduce un valor para buscar en el arbol: ";
    cin >> valorBuscado;

    if (arbol.buscar(valorBuscado)) {
        cout << "El valor " << valorBuscado << " se encuentra en el arbol." << endl;
    } else {
        cout << "El valor " << valorBuscado << " NO se encuentra en el arbol." << endl;
    }

    return 0;
}
