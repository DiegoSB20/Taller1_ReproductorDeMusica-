#include "Nodo.h"

Nodo::Nodo(Cancion* cancion) {
    this->dato = cancion;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

Nodo::~Nodo() {
    // Importante: El Nodo NO destruye el objeto Cancion con 'delete dato'.
    // Esto es porque una misma canción puede estar en el inventario global
    // y al mismo tiempo en la lista de reproducción. Solo borramos el enlace.
}

Cancion* Nodo::getDato() const { return dato; }
void Nodo::setDato(Cancion* cancion) { this->dato = cancion; }

Nodo* Nodo::getSiguiente() const { return siguiente; }
void Nodo::setSiguiente(Nodo* sig) { this->siguiente = sig; }

Nodo* Nodo::getAnterior() const { return anterior; }
void Nodo::setAnterior(Nodo* ant) { this->anterior = ant; }