#ifndef INTERFAZCONSOLA_H
#define INTERFAZCONSOLA_H

#include <string>
#include "../Clases//EstadoReproductor.h"
#include "../Clases//Cancion.h"
#include "../estructura_data///ListaDoble.h"

class InterfazConsola {
public:
    InterfazConsola();
    ~InterfazConsola();

    void limpiarPantalla();
    void pausar();

    void mostrarListadoCanciones(ListaDoble* inventario);
    void mostrarListaReproduccionActual(ListaDoble* listaReproduccion);


    // Dibuja el cuadro principal según la maqueta del PDF
    void mostrarMenuPrincipal(EstadoReproductor* estado, Cancion* cancionActual);
    
    // Obtiene la tecla ingresada por el usuario
    std::string capturarEntrada();
};

#endif // INTERFAZCONSOLA_H