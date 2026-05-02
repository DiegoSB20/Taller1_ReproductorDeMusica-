#include "EstadoReproductor.h"

EstadoReproductor::EstadoReproductor() {
    // Valores por defecto cuando no existe status.cfg (como pide el enunciado)
    estadoActual = ModoReproduccion::DETENIDA;
    repeticionActual = ModoRepeticion::DESACTIVADO;
    modoAleatorio = false;
    idCancionActual = -1; // -1 indica que no hay canción seleccionada
}

EstadoReproductor::~EstadoReproductor() {}

void EstadoReproductor::alternarReproduccionPausa() {
    if (estadoActual == ModoReproduccion::REPRODUCIENDO) {
        estadoActual = ModoReproduccion::PAUSADA;
    } else if (estadoActual == ModoReproduccion::PAUSADA || estadoActual == ModoReproduccion::DETENIDA) {
        estadoActual = ModoReproduccion::REPRODUCIENDO;
    }
}

void EstadoReproductor::alternarAleatorio() {
    modoAleatorio = !modoAleatorio; // Invierte el valor actual (true a false, o false a true)
}

void EstadoReproductor::avanzarModoRepeticion() {
    // Cicla entre los 3 modos disponibles
    if (repeticionActual == ModoRepeticion::DESACTIVADO) {
        repeticionActual = ModoRepeticion::REPETIR_UNA;
    } else if (repeticionActual == ModoRepeticion::REPETIR_UNA) {
        repeticionActual = ModoRepeticion::REPETIR_TODAS;
    } else {
        repeticionActual = ModoRepeticion::DESACTIVADO;
    }
}

// Getters
ModoReproduccion EstadoReproductor::getEstado() const { return estadoActual; }
ModoRepeticion EstadoReproductor::getRepeticion() const { return repeticionActual; }
bool EstadoReproductor::getAleatorio() const { return modoAleatorio; }
int EstadoReproductor::getIdCancionActual() const { return idCancionActual; }

// Setters
void EstadoReproductor::setEstado(ModoReproduccion estado) { this->estadoActual = estado; }
void EstadoReproductor::setRepeticion(ModoRepeticion repeticion) { this->repeticionActual = repeticion; }
void EstadoReproductor::setAleatorio(bool aleatorio) { this->modoAleatorio = aleatorio; }
void EstadoReproductor::setIdCancionActual(int id) { this->idCancionActual = id; }