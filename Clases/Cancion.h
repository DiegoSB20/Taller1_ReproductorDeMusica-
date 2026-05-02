#ifndef CANCION_H
#define CANCION_H

#include <string>

class Cancion {
private:
    int id;
    std::string nombre;
    std::string artista;
    std::string album;
    int anio;
    int duracion;
    std::string rutaArchivo;

public:
    // Constructor
    Cancion(int id, std::string nombre, std::string artista, std::string album, int anio, int duracion, std::string ruta);
    
    // Destructor
    ~Cancion();

    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getArtista() const;
    std::string getAlbum() const;
    int getAnio() const;
    int getDuracion() const;
    std::string getRutaArchivo() const;

    // Setters (Por si necesitas editar una canción en el futuro)
    void setNombre(std::string nombre);
    void setArtista(std::string artista);
    void setAlbum(std::string album);
    void setAnio(int anio);
    void setDuracion(int duracion);
    void setRutaArchivo(std::string ruta);
};

#endif // CANCION_H