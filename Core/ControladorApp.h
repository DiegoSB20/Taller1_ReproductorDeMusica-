#ifndef CONTROLADORAPP_H
#define CONTROLADORAPP_H

#include "../estructura_data//ListaDoble.h"
#include "../Clases//EstadoReproductor.h"
#include "GestorArchivos.h"
#include "InterfazConsola.h"

class ControladorApp {
private:
    ListaDoble* inventarioGlobal;
    ListaDoble* listaReproduccion;
    EstadoReproductor* estado;
    GestorArchivos* archivos;
    InterfazConsola* consola;

    void procesarSubmenuListado();
    void procesarSubmenuListaActual();
    Cancion* buscarCancionPorId(int id);
    
    // Puntero directo al nodo que está sonando actualmente
    Nodo* nodoActual; 

    // Métodos internos
    void procesarOpcionPrincipal(std::string opcion);

public:
    ControladorApp();
    ~ControladorApp();

    void iniciar(); // El bucle principal (while)
};

#endif // CONTROLADORAPP_H