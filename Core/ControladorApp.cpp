#include "ControladorApp.h"
#include <cctype> // Para std::toupper
#include <stdexcept> // Necesario para atrapar errores de std::stoi
#include <iostream>

ControladorApp::ControladorApp() {
    inventarioGlobal = new ListaDoble();
    listaReproduccion = new ListaDoble();
    estado = new EstadoReproductor();
    archivos = new GestorArchivos();
    consola = new InterfazConsola();
    nodoActual = nullptr;

    // Cargar datos al iniciar
    archivos->cargarCanciones(inventarioGlobal);
    archivos->cargarEstado(estado, inventarioGlobal, listaReproduccion);
}

ControladorApp::~ControladorApp() {
    // Al cerrar, guardar estado y liberar memoria
    archivos->guardarEstado(estado, listaReproduccion);
    
    delete inventarioGlobal;
    delete listaReproduccion;
    delete estado;
    delete archivos;
    delete consola;
}

void ControladorApp::iniciar() {
    bool ejecutando = true;
    std::string opcion;

    while (ejecutando) {
        consola->limpiarPantalla();
        
        Cancion* pistaSonando = (nodoActual != nullptr) ? nodoActual->getDato() : nullptr;
        consola->mostrarMenuPrincipal(estado, pistaSonando);
        
        opcion = consola->capturarEntrada();
        
        // Convertir a mayúscula para evitar errores
        if (!opcion.empty()) opcion[0] = std::toupper(opcion[0]);

        if (opcion == "X") {
            ejecutando = false;
        } else {
            procesarOpcionPrincipal(opcion);
            // Cada vez que se hace una acción, se actualiza el estado (Regla del PDF)
            archivos->guardarEstado(estado, listaReproduccion);
        }
    }
}

void ControladorApp::procesarOpcionPrincipal(std::string opcion) {
    if (opcion == "W") {
        estado->alternarReproduccionPausa();
    }
    else if (opcion == "S") {
        estado->alternarAleatorio();
        if (estado->getAleatorio() && !listaReproduccion->estaVacia()) {
            listaReproduccion->mezclarLista();
        }
    }
    else if (opcion == "R") {
        estado->avanzarModoRepeticion();
    }
    else if (opcion == "L") {
        procesarSubmenuListado();
    }
    else if (opcion == "A") {
        procesarSubmenuListaActual();
    }
    else if (opcion == "E") { // Pista Siguiente
        if (estado->getRepeticion() == ModoRepeticion::REPETIR_UNA && nodoActual != nullptr) {
            // Se queda en la misma canción
            estado->setEstado(ModoReproduccion::REPRODUCIENDO);
        }
        else if (nodoActual != nullptr && nodoActual->getSiguiente() != nullptr) {
            // Avanza al siguiente nodo
            nodoActual = nodoActual->getSiguiente();
            estado->setIdCancionActual(nodoActual->getDato()->getId());
            estado->setEstado(ModoReproduccion::REPRODUCIENDO);
        }
        else if (estado->getRepeticion() == ModoRepeticion::REPETIR_TODAS && !listaReproduccion->estaVacia()) {
            // Vuelve al inicio de la lista
            if (estado->getAleatorio()) listaReproduccion->mezclarLista();
            nodoActual = listaReproduccion->getCabeza();
            estado->setIdCancionActual(nodoActual->getDato()->getId());
        }
        else {
            // Lista vacía o final de lista sin repetición: Comportamiento por defecto del PDF
            estado->setEstado(ModoReproduccion::DETENIDA);
        }
    }
    else if (opcion == "Q") { // Pista Anterior
        if (nodoActual != nullptr && nodoActual->getAnterior() != nullptr) {
            nodoActual = nodoActual->getAnterior();
            estado->setIdCancionActual(nodoActual->getDato()->getId());
            estado->setEstado(ModoReproduccion::REPRODUCIENDO);
        }
    }
}

// Lógica del Submenú L
void ControladorApp::procesarSubmenuListado() {
    bool enSubmenu = true;
    while (enSubmenu) {
        consola->limpiarPantalla();
        consola->mostrarListadoCanciones(inventarioGlobal);
        std::cout << "N - Agregar cancion al registro\n";
        std::cout << "D<num> - Eliminar cancion seleccionada\n";
        
        std::string input = consola->capturarEntrada();
        if (input.empty()) continue;
        input[0] = std::toupper(input[0]);

        if (input == "V") {
            enSubmenu = false;
        } 
        else if (input == "N") {
            // Lógica para agregar nueva canción
            std::string nombre, artista, album, ruta;
            int anio, duracion;
            
            consola->limpiarPantalla();
            std::cout << "--- Agregar Nueva Cancion ---\n";
            std::cin.ignore(); // Limpiar el buffer
            
            std::cout << "Nombre: "; std::getline(std::cin, nombre);
            std::cout << "Artista: "; std::getline(std::cin, artista);
            std::cout << "Album: "; std::getline(std::cin, album);
            std::cout << "Anio: "; std::cin >> anio;
            std::cout << "Duracion (segundos): "; std::cin >> duracion;
            std::cin.ignore();
            std::cout << "Ruta del archivo: "; std::getline(std::cin, ruta);

            // Generar nuevo ID buscando el mayor actual
            int nuevoId = 1;
            Nodo* temp = inventarioGlobal->getCabeza();
            while(temp != nullptr) {
                if(temp->getDato()->getId() >= nuevoId) nuevoId = temp->getDato()->getId() + 1;
                temp = temp->getSiguiente();
            }

            Cancion* nueva = new Cancion(nuevoId, nombre, artista, album, anio, duracion, ruta);
            inventarioGlobal->insertarAlFinal(nueva);
            archivos->guardarInventario(inventarioGlobal); // Guardar en el .txt
        }
        else if (input[0] == 'R' || input[0] == 'A' || input[0] == 'D') {
            try {
                int id = std::stoi(input.substr(1)); // Extrae el número. Si falla, va al catch.
                
                if (input[0] == 'R') {
                    Cancion* seleccionada = buscarCancionPorId(id);
                    if (seleccionada != nullptr) {
                        listaReproduccion->vaciar();
                        listaReproduccion->insertarAlFinal(seleccionada);
                        nodoActual = listaReproduccion->getCabeza();
                        estado->setIdCancionActual(id);
                        estado->setEstado(ModoReproduccion::REPRODUCIENDO);
                        enSubmenu = false;
                    }
                } 
                else if (input[0] == 'A') {
                    Cancion* seleccionada = buscarCancionPorId(id);
                    if (seleccionada != nullptr) listaReproduccion->insertarAlFinal(seleccionada);
                }
                else if (input[0] == 'D') {
                    if (inventarioGlobal->eliminarPorId(id)) {
                        archivos->guardarInventario(inventarioGlobal); // Actualizar .txt
                    }
                }
            } catch (const std::exception& e) {
                // Si el usuario escribe "R-hola", el programa entra aquí y no se cierra.
                continue; 
            }
        }
    }
}

// Lógica del Submenú A
void ControladorApp::procesarSubmenuListaActual() {
    bool enSubmenu = true;
    while (enSubmenu) {
        consola->limpiarPantalla();
        consola->mostrarListaReproduccionActual(listaReproduccion);
        std::string input = consola->capturarEntrada();
        
        if (input.empty()) continue;
        input[0] = std::toupper(input[0]);

        if (input == "V") {
            enSubmenu = false;
        }
        else if (input[0] == 'S' && input.length() > 1) {
            try {
                int saltos = std::stoi(input.substr(1));
                Nodo* temp = nodoActual;
                for(int i = 1; i < saltos && temp != nullptr; i++) {
                    temp = temp->getSiguiente();
                }
                if (temp != nullptr) {
                    nodoActual = temp;
                    estado->setIdCancionActual(nodoActual->getDato()->getId());
                    estado->setEstado(ModoReproduccion::REPRODUCIENDO);
                }
                enSubmenu = false;
            } catch (const std::exception& e) {
                continue; // Manejo de errores por si no es un número válido
            }
        }
    }
}

// Función auxiliar de búsqueda manual (Reemplaza a std::find)
Cancion* ControladorApp::buscarCancionPorId(int id) {
    Nodo* actual = inventarioGlobal->getCabeza();
    while (actual != nullptr) {
        if (actual->getDato()->getId() == id) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}
