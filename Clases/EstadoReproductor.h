#ifndef ESTADOREPRODUCTOR_H
#define ESTADOREPRODUCTOR_H

// Definimos los posibles estados como enumeraciones para mayor seguridad
enum class ModoReproduccion { DETENIDA, REPRODUCIENDO, PAUSADA };
enum class ModoRepeticion { DESACTIVADO, REPETIR_UNA, REPETIR_TODAS };

class EstadoReproductor {
private:
    ModoReproduccion estadoActual;
    ModoRepeticion repeticionActual;
    bool modoAleatorio;
    int idCancionActual; // Guardamos el ID en lugar del puntero para facilitar el guardado en status.cfg

public:
    EstadoReproductor();
    ~EstadoReproductor();

    // Métodos de alternancia (Toggles) requeridos por el enunciado
    void alternarReproduccionPausa(); // Para la opción 'W'
    void alternarAleatorio();         // Para la opción 'S'
    void avanzarModoRepeticion();     // Para la opción 'R'

    // Getters
    ModoReproduccion getEstado() const;
    ModoRepeticion getRepeticion() const;
    bool getAleatorio() const;
    int getIdCancionActual() const;

    // Setters (Útiles al cargar el status.cfg)
    void setEstado(ModoReproduccion estado);
    void setRepeticion(ModoRepeticion repeticion);
    void setAleatorio(bool aleatorio);
    void setIdCancionActual(int id);
};

#endif // ESTADOREPRODUCTOR_H