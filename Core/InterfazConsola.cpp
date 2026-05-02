#include "InterfazConsola.h"
#include <iostream>
#include <cstdlib> // Para system()

InterfazConsola::InterfazConsola() {}
InterfazConsola::~InterfazConsola() {}

void InterfazConsola::limpiarPantalla() {
    // Comando multiplataforma básico
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void InterfazConsola::pausar() {
    std::cout << "Presione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

std::string InterfazConsola::capturarEntrada() {
    std::string entrada;
    std::cout << "Ingrese Opcion: ";
    std::cin >> entrada;
    return entrada;
}

void InterfazConsola::mostrarMenuPrincipal(EstadoReproductor* estado, Cancion* cancionActual) {
    std::cout << "--------------------------------------------------\n";
    
    // Formatear la primera línea: Estado (Aleatorio-Repeticion): Nombre
    std::string strEstado = (estado->getEstado() == ModoReproduccion::REPRODUCIENDO) ? "Reproduciendo" : 
                            (estado->getEstado() == ModoReproduccion::PAUSADA) ? "En Pausa" : "Reproduccion Detenida";
    
    std::string extras = "";
    if (estado->getAleatorio() || estado->getRepeticion() != ModoRepeticion::DESACTIVADO) {
        extras += "(";
        if (estado->getAleatorio()) extras += "S";
        if (estado->getAleatorio() && estado->getRepeticion() != ModoRepeticion::DESACTIVADO) extras += "-";
        
        if (estado->getRepeticion() == ModoRepeticion::REPETIR_UNA) extras += "R1";
        else if (estado->getRepeticion() == ModoRepeticion::REPETIR_TODAS) extras += "RA";
        extras += ")";
    }

    if (cancionActual != nullptr) {
        std::cout << strEstado << " " << extras << ": " << cancionActual->getNombre() << "\n";
        std::cout << "Artista: " << cancionActual->getArtista() << "\n";
        std::cout << "Album: " << cancionActual->getAlbum() << " [" << cancionActual->getAnio() << "]\n";
    } else {
        std::cout << strEstado << "\n";
        std::cout << "Ninguna pista seleccionada.\n";
    }

    std::cout << "\nOpciones:\n";
    std::cout << "W - Reproducir/Pausar\n";
    std::cout << "Q - Pista Anterior\n";
    std::cout << "E - Pista Siguiente\n";
    std::cout << "S - Activar/Desactivar modo aleatorio\n";
    std::cout << "R - Repeticion (Desactivado/Repetir una/Repetir todas)\n";
    std::cout << "A - Ver lista de reproduccion actual\n";
    std::cout << "L - Listado de canciones\n";
    std::cout << "X - Salir\n";
    std::cout << "--------------------------------------------------\n";
}

void InterfazConsola::mostrarListadoCanciones(ListaDoble* inventario) {
    std::cout << "\n--- Listado de Canciones Disponibles ---\n";
    if (inventario->estaVacia()) {
        std::cout << "No hay canciones registradas en la fonoteca.\n";
    } else {
        Nodo* actual = inventario->getCabeza();
        while (actual != nullptr) {
            Cancion* c = actual->getDato();
            std::cout << c->getId() << ". " << c->getNombre() << " - " << c->getArtista() << "\n";
            actual = actual->getSiguiente();
        }
    }
    std::cout << "\nOpciones:\n";
    std::cout << "R<num> - Reproducir cancion seleccionada\n";
    std::cout << "A<num> - Agregar cancion al final de la lista de reproduccion actual\n";
    std::cout << "V - Volver al menu principal\n";
    // Nota: Las opciones N y D se pueden implementar después si el tiempo te lo permite
}

void InterfazConsola::mostrarListaReproduccionActual(ListaDoble* listaReproduccion) {
    std::cout << "\n--- Lista de Reproduccion Actual ---\n";
    if (listaReproduccion->estaVacia()) {
        std::cout << "Vacia\n";
    } else {
        Nodo* actual = listaReproduccion->getCabeza();
        int pos = 1;
        while (actual != nullptr) {
            Cancion* c = actual->getDato();
            std::cout << pos << ". " << c->getNombre() << " - " << c->getArtista() << "\n";
            actual = actual->getSiguiente();
            pos++;
        }
    }
    std::cout << "\nOpciones:\n";
    std::cout << "S<num> - Saltar a la cancion seleccionada\n";
    std::cout << "V - Volver al menu principal\n";
}
