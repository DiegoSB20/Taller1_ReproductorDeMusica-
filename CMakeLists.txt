cmake_minimum_required(VERSION 3.20)
project(ReproductorMusica)

set(CMAKE_CXX_STANDARD 14)

# Forma segura de buscar TODAS las subcarpetas automáticamente
# para que encuentre Nodo.h, Cancion.h, etc.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Recolectamos absolutamente todos los archivos .cpp del proyecto
file(GLOB_RECURSE SOURCES
        "*.cpp"
        "*.h"
)

# Filtramos para asegurarnos de que no intente compilar basura temporal
list(FILTER SOURCES EXCLUDE REGEX "cmake-build-.*")
list(FILTER SOURCES EXCLUDE REGEX ".idea/.*")

add_executable(ReproductorMusica ${SOURCES})
