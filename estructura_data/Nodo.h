#ifndef NODO_H
#define NODO_H

// Declaración anticipada. Le decimos al compilador que la clase Cancion existe,
// sin necesidad de incluir su cabecera todavía.
class Cancion;

class Nodo {
private:
    Cancion* dato;
    Nodo* siguiente;
    Nodo* anterior;

public:
    Nodo(Cancion* cancion);
    ~Nodo();

    // Getters y Setters
    Cancion* getDato() const;
    void setDato(Cancion* cancion);

    Nodo* getSiguiente() const;
    void setSiguiente(Nodo* sig);

    Nodo* getAnterior() const;
    void setAnterior(Nodo* ant);
};

#endif // NODO_H
