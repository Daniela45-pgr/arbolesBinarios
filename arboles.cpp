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

    void setDato(T nuevoDato) { dato = nuevoDato; }
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

    // Método para eliminar un valor del árbol
    void eliminar(T valor) {
        raiz = eliminarRecursivo(raiz, valor);
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

    // Método auxiliar recursivo para eliminar un valor
    NodoArbol<T>* eliminarRecursivo(NodoArbol<T>* nodo, T valor) {
        if (!nodo) {
            return nullptr;
        }

        if (valor < nodo->getDato()) {
            nodo->setIzquierdo(eliminarRecursivo(nodo->getIzquierdo(), valor));
        } else if (valor > nodo->getDato()) {
            nodo->setDerecho(eliminarRecursivo(nodo->getDerecho(), valor));
        } else {
            // Caso 1: Nodo sin hijos
            if (!nodo->getIzquierdo() && !nodo->getDerecho()) {
                delete nodo;
                return nullptr;
            }
            // Caso 2: Nodo con un hijo
            if (!nodo->getIzquierdo()) {
                NodoArbol<T>* temp = nodo->getDerecho();
                delete nodo;
                return temp;
            } else if (!nodo->getDerecho()) {
                NodoArbol<T>* temp = nodo->getIzquierdo();
                delete nodo;
                return temp;
            }
            // Caso 3: Nodo con dos hijos
            NodoArbol<T>* sucesor = encontrarMinimo(nodo->getDerecho());
            nodo->setDato(sucesor->getDato());
            nodo->setDerecho(eliminarRecursivo(nodo->getDerecho(), sucesor->getDato()));
        }
        return nodo;
    }

    // Método auxiliar para encontrar el nodo con el valor mínimo
    NodoArbol<T>* encontrarMinimo(NodoArbol<T>* nodo) {
        while (nodo && nodo->getIzquierdo()) {
            nodo = nodo->getIzquierdo();
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

    // Insertar valores en el árbol
    arbol.insertar(50);
    arbol.insertar(30);
    arbol.insertar(70);
    arbol.insertar(20);
    arbol.insertar(40);
    arbol.insertar(60);
    arbol.insertar(80);

    cout << "Arbol en inorden antes de eliminar: ";
    arbol.imprimirInorden();

    // Eliminar nodos
    arbol.eliminar(20); // Nodo sin hijos
    arbol.eliminar(30); // Nodo con un hijo
    arbol.eliminar(50); // Nodo con dos hijos

    cout << "Arbol en inorden despues de eliminar: ";
    arbol.imprimirInorden();

    return 0;
}
