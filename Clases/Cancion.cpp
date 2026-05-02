#include "Cancion.h"

Cancion::Cancion(int id, std::string nombre, std::string artista, std::string album, int anio, int duracion, std::string ruta) {
    this->id = id;
    this->nombre = nombre;
    this->artista = artista;
    this->album = album;
    this->anio = anio;
    this->duracion = duracion;
    this->rutaArchivo = ruta;
}

Cancion::~Cancion() {
    // No hay memoria dinámica reservada internamente por la canción, 
    // así que el destructor queda vacío.
}

// Getters
int Cancion::getId() const { return id; }
std::string Cancion::getNombre() const { return nombre; }
std::string Cancion::getArtista() const { return artista; }
std::string Cancion::getAlbum() const { return album; }
int Cancion::getAnio() const { return anio; }
int Cancion::getDuracion() const { return duracion; }
std::string Cancion::getRutaArchivo() const { return rutaArchivo; }

// Setters
void Cancion::setNombre(std::string nombre) { this->nombre = nombre; }
void Cancion::setArtista(std::string artista) { this->artista = artista; }
void Cancion::setAlbum(std::string album) { this->album = album; }
void Cancion::setAnio(int anio) { this->anio = anio; }
void Cancion::setDuracion(int duracion) { this->duracion = duracion; }
void Cancion::setRutaArchivo(std::string ruta) { this->rutaArchivo = ruta; }