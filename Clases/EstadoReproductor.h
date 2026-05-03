#ifndef ESTADOREPRODUCTOR_H
#define ESTADOREPRODUCTOR_H

// Definimos los posibles estados como enumeraciones para mayor seguridad
enum class ModoReproduccion { DETENIDA, REPRODUCIENDO, PAUSADA };
enum class ModoRepeticion { DESACTIVADO, REPETIR_UNA, REPETIR_TODAS };

class EstadoReproductor {
private:
    ModoReproduccion estadoActual;
    ModoRepeticion repeticionActual;
    //"Decidimos implementarlo por seguridad de tipos (Type Safety). Si definía el estado como un entero (int), el compilador me habría permitido asignar accidentalmente un estado inválido, 
    //por ejemplo, estado = 99. Al encapsular los estados en un enum class, 
    //el compilador revisa por mí que solo se puedan asignar los tres estados válidos (DETENIDA, REPRODUCIENDO, PAUSADA), reduciendo el riesgo de bugs silenciosos durante la ejecución."

    //int estadoActual;     // 0 = Detenida, 1 = Reproduciendo, 2 = Pausada
    //int repeticionActual; // 0 = Desactivado, 1 = Repetir Una, 2 = Repetir Todas
    // si se quisiera hacer sin enum habria que designar en cada if del estadoReproductor.cpp si es 0,1 o 2
    // pero se hace asi ya que es mas entendible y legible


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
