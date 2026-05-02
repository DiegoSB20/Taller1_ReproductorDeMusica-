#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "Nodo.h"

class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;
    int tamano;

public:
    ListaDoble();
    ~ListaDoble();

    // Operaciones básicas
    bool estaVacia() const;
    int getTamano() const;
    void vaciar();

    // Inserción y obtención
    void insertarAlFinal(Cancion* cancion);
    Cancion* obtenerEnPosicion(int indice);

    // Nodos clave para la reproducción
    Nodo* getCabeza() const;
    Nodo* getCola() const;


    void mezclarLista(); // Para la opción 'S'
};

#endif // LISTADOBLE_H
