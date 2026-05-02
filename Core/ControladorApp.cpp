#include "ControladorApp.h"
#include <cctype> // Para std::toupper

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
        std::string input = consola->capturarEntrada();

        if (input.empty()) continue;
        input[0] = std::toupper(input[0]);

        if (input == "V") {
            enSubmenu = false;
        }
        else if (input[0] == 'R' && input.length() > 1) {
            // Extraer el ID (ej: de R12 extrae 12)
            int id = std::stoi(input.substr(1));
            Cancion* seleccionada = buscarCancionPorId(id);

            if (seleccionada != nullptr) {
                listaReproduccion->vaciar(); // Limpiamos la cola actual
                listaReproduccion->insertarAlFinal(seleccionada); // Añadimos la seleccionada
                nodoActual = listaReproduccion->getCabeza(); // Apuntamos el reproductor aquí

                estado->setIdCancionActual(id);
                estado->setEstado(ModoReproduccion::REPRODUCIENDO);
                enSubmenu = false; // Volvemos al menu principal para que empiece a "sonar"
            }
        }
        else if (input[0] == 'A' && input.length() > 1) {
            int id = std::stoi(input.substr(1));
            Cancion* seleccionada = buscarCancionPorId(id);
            if (seleccionada != nullptr) {
                listaReproduccion->insertarAlFinal(seleccionada);
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
            int saltos = std::stoi(input.substr(1));

            // Avanzamos el nodoActual X cantidad de veces
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