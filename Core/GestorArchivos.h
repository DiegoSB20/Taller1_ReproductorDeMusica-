#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <string>
#include "../estructura_data//ListaDoble.h"
#include "../Clases/EstadoReproductor.h"

class GestorArchivos {
private:
    std::string rutaCanciones;
    std::string rutaEstado;

public:
    GestorArchivos(std::string rutaCanciones = "music_source.txt", std::string rutaEstado = "status.cfg");
    ~GestorArchivos();

    // Carga el inventario total de canciones desde el .txt
    bool cargarCanciones(ListaDoble* inventario);
    
    // Guarda y carga el estado de la aplicación (para status.cfg)
    bool cargarEstado(EstadoReproductor* estado, ListaDoble* inventario, ListaDoble* reproduccionActual);
    bool guardarEstado(EstadoReproductor* estado, ListaDoble* reproduccionActual);
};

#endif // GESTORARCHIVOS_H