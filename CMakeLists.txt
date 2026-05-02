cmake_minimum_required(VERSION 3.20)
project(ReproductorMusica)

# Fijar el estándar de C++ requerido por el taller
set(CMAKE_CXX_STANDARD 20)

# 1. Le decimos al compilador dónde buscar los archivos de cabecera (.h)
include_directories(data_structures classes core)

# 2. Recopilamos todos los archivos fuente (.cpp y .h) automáticamente
# Usamos GLOB_RECURSE para que si agregas un archivo nuevo, CMake lo detecte solo.
file(GLOB_RECURSE SOURCES
        "data_structures/*.cpp"
        "data_structures/*.h"
        "classes/*.cpp"
        "classes/*.h"
        "core/*.cpp"
        "core/*.h"
        "main.cpp"
)

# 3. Construimos el ejecutable final con todos los archivos encontrados
add_executable(ReproductorMusica ${SOURCES}
        estructura_data/ListaDoble.cpp
        estructura_data/ListaDoble.h
        Clases/Cancion.cpp
        Clases/Cancion.h
        Clases/EstadoReproductor.cpp
        Clases/EstadoReproductor.h
        Core/GestorArchivos.cpp
        Core/GestorArchivos.h
        Core/InterfazConsola.cpp
        Core/InterfazConsola.h
        Core/ControladorApp.cpp
        Core/ControladorApp.h)
