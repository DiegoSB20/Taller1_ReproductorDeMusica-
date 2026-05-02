#include "ListaDoble.h"
#include <cstdlib> // Necesario para la generación de números aleatorios si implementas mezclarLista()
#include <ctime>

ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

ListaDoble::~ListaDoble() {
    vaciar();
}

bool ListaDoble::estaVacia() const {
    return tamano == 0;
}

int ListaDoble::getTamano() const {
    return tamano;
}

void ListaDoble::vaciar() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->getSiguiente();
        delete actual; // Libera la memoria del nodo
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

void ListaDoble::insertarAlFinal(Cancion* cancion) {
    Nodo* nuevoNodo = new Nodo(cancion);

    if (estaVacia()) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->setSiguiente(nuevoNodo);
        nuevoNodo->setAnterior(cola);
        cola = nuevoNodo;
    }
    tamano++;
}

Cancion* ListaDoble::obtenerEnPosicion(int indice) {
    if (indice < 0 || indice >= tamano) {
        return nullptr;
    }

    Nodo* actual = cabeza;
    for (int i = 0; i < indice; i++) {
        actual = actual->getSiguiente();
    }
    return actual->getDato();
}

Nodo* ListaDoble::getCabeza() const { return cabeza; }
Nodo* ListaDoble::getCola() const { return cola; }

void ListaDoble::mezclarLista() {
    if (tamano < 2) return;

    // Lógica básica de Fisher-Yates aplicable a nodos
    // Nota: Como es una lista enlazada y no un array, intercambiar datos 
    // es más eficiente en C++ que rehacer todos los enlaces de punteros.
    
    srand(static_cast<unsigned int>(time(0)));
    
    for (int i = tamano - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        
        // Obtener nodos en posición i y j
        Nodo* nodoI = cabeza;
        for (int k = 0; k < i; ++k) nodoI = nodoI->getSiguiente();
            
        Nodo* nodoJ = cabeza;
        for (int k = 0; k < j; ++k) nodoJ = nodoJ->getSiguiente();
            
        // Intercambiar solo el contenido (los punteros Cancion*)
        Cancion* temp = nodoI->getDato();
        nodoI->setDato(nodoJ->getDato());
        nodoJ->setDato(temp);
    }
}