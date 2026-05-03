#include "GestorArchivos.h"
#include "../Clases//Cancion.h"
#include <fstream>
#include <sstream>
#include <iostream>

GestorArchivos::GestorArchivos(std::string rutaC, std::string rutaE) {
    rutaCanciones = rutaC;
    rutaEstado = rutaE;
}

GestorArchivos::~GestorArchivos() {}

bool GestorArchivos::cargarCanciones(ListaDoble* inventario) {
    std::ifstream archivo(rutaCanciones);
    if (!archivo.is_open()) {
        return false; // El archivo no existe aún
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string item;
        
        // Variables temporales para construir la Cancion
        std::string id_str, nombre, artista, album, anio_str, duracion_str, ruta;
        
        // Parseo separado por comas
        std::getline(ss, id_str, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, artista, ',');
        std::getline(ss, album, ',');
        std::getline(ss, anio_str, ',');
        std::getline(ss, duracion_str, ',');
        std::getline(ss, ruta, ',');

        int id = std::stoi(id_str);
        int anio = std::stoi(anio_str);
        int duracion = std::stoi(duracion_str);

        Cancion* nuevaCancion = new Cancion(id, nombre, artista, album, anio, duracion, ruta);
        inventario->insertarAlFinal(nuevaCancion);
    }
    archivo.close();
    return true;
}

bool GestorArchivos::guardarEstado(EstadoReproductor* estado, ListaDoble* reproduccionActual) {
    std::ofstream archivo(rutaEstado);
    if (!archivo.is_open()) return false;

    // Guardado simple formato CLAVE=VALOR
    archivo << "ID_ACTUAL=" << estado->getIdCancionActual() << "\n";
    archivo << "ESTADO_REP=" << static_cast<int>(estado->getEstado()) << "\n";
    archivo << "ALEATORIO=" << (estado->getAleatorio() ? "1" : "0") << "\n";
    archivo << "MODO_REP=" << static_cast<int>(estado->getRepeticion()) << "\n";
    
    archivo.close();
    return true;
}

bool GestorArchivos::cargarEstado(EstadoReproductor* estado, ListaDoble* inventario, ListaDoble* reproduccionActual) {
    std::ifstream archivo(rutaEstado);
    if (!archivo.is_open()) return false;

    std::string linea;
    while (std::getline(archivo, linea)) {
        // Buscar el signo igual para separar CLAVE=VALOR
        size_t posIgual = linea.find('=');
        if (posIgual != std::string::npos) {
            std::string clave = linea.substr(0, posIgual);
            std::string valor = linea.substr(posIgual + 1);

            if (clave == "ID_ACTUAL") estado->setIdCancionActual(std::stoi(valor));
            else if (clave == "ESTADO_REP") estado->setEstado(static_cast<ModoReproduccion>(std::stoi(valor)));
            else if (clave == "ALEATORIO") estado->setAleatorio(valor == "1");
            else if (clave == "MODO_REP") estado->setRepeticion(static_cast<ModoRepeticion>(std::stoi(valor)));
        }
    }
    archivo.close();
    return true;
}

bool GestorArchivos::guardarInventario(ListaDoble* inventario) {
    std::ofstream archivo(rutaCanciones); // Abre y limpia el archivo
    if (!archivo.is_open()) return false;

    Nodo* actual = inventario->getCabeza();
    while (actual != nullptr) {
        Cancion* c = actual->getDato();
        archivo << c->getId() << "," 
                << c->getNombre() << "," 
                << c->getArtista() << "," 
                << c->getAlbum() << "," 
                << c->getAnio() << "," 
                << c->getDuracion() << "," 
                << c->getRutaArchivo() << "\n";
        actual = actual->getSiguiente();
    }
    archivo.close();
    return true;
}
