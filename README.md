 ###[Reproductor de musica UCN]
Integrantes: Diego Seco y David Rodriguez

###📝 Descripción del Proyecto
Este proyecto es un reproductor de medios basado en consola desarrollado en C++ estándar. Implementa la gestión de inventario y colas de reproducción mediante la construcción desde cero de Listas Doblemente Enlazadas, evitando el uso de librerías de contenedores STL. El sistema cuenta con persistencia de estado mediante archivos de configuración locales, permitiendo retomar la reproducción, gestionar modos aleatorios, modos de repetición y moverse dinámicamente entre pistas musicales directamente en la terminal.

###Instrucciones de uso
Este proyecto utiliza CMake como sistema de construcción de software para garantizar la compatibilidad multiplataforma y la correcta vinculación de sus múltiples directorios y archivos de cabecera.

###Requisitos previos:

Compilador compatible con C++14 (MinGW, GCC, Clang).

CMake instalado (o un IDE que lo integre, como CLion).

Compilación mediante CLion (Recomendado):

Abre la carpeta del proyecto en CLion.

El IDE detectará automáticamente el archivo CMakeLists.txt.

Selecciona la configuración de compilación (Debug/Release).

Asegúrate de configurar el Working Directory apuntando a la raíz del proyecto para que detecte los archivos de texto.

Haz clic en Build (icono del martillo) o presiona Ctrl + F9.

Para ejecutar la aplicación, corre el binario generado (ReproductorMusica.exe en Windows o ./ReproductorMusica en Linux/macOS) asegurándote de que los archivos music_source.txt y status.cfg se encuentren en el mismo directorio de trabajo.

Funcionamiento: La aplicación opera enteramente por consola mediante el ingreso de caracteres para navegar por los menús. Al iniciar:

El menú principal detalla la pista actual, el estado de la reproducción, y permite acciones rápidas de cambio de estado (Reproducir/Pausar [W], Aleatorio [S], Repetir [R]) y saltos de canción ([Q] Anterior, [E] Siguiente).

Los submenús permiten interactuar directamente con la lista actual [A] (para saltar pistas) y con la fonoteca completa [L] (para buscar y encolar música).

Todo cambio en el estado o navegación generará automáticamente una sobreescritura sobre el archivo status.cfg para evitar pérdida de progreso. El cierre seguro del sistema se realiza únicamente con la opción [X].

🏗️ Diagrama de Clases




    classDiagram
    class Nodo {
        -Cancion* dato
        -Nodo* siguiente
        -Nodo* anterior
    }
    class ListaDoble {
        -Nodo* cabeza
        -Nodo* cola
        -int tamano
        +insertarAlFinal(Cancion*)
        +mezclarLista()
    }
    class Cancion {
        -int id
        -string nombre
        -string artista
        -int duracion
    }
    class EstadoReproductor {
        -ModoReproduccion estadoActual
        -ModoRepeticion repeticionActual
        -bool modoAleatorio
        -int idCancionActual
    }
    class GestorArchivos {
        +cargarCanciones()
        +cargarEstado()
        +guardarEstado()
    }
    class InterfazConsola {
        +mostrarMenuPrincipal()
        +limpiarPantalla()
    }
    class ControladorApp {
        -ListaDoble* inventarioGlobal
        -ListaDoble* listaReproduccion
        +iniciar()
        -procesarOpcionPrincipal()
        
    }
    
    ListaDoble "1" *-- "many" Nodo : contiene
    Nodo "1" o-- "1" Cancion : apunta a
    ControladorApp "1" *-- "2" ListaDoble : administra
    ControladorApp "1" *-- "1" GestorArchivos : usa
    ControladorApp "1" *-- "1" InterfazConsola : usa
    ControladorApp "1" *-- "1" EstadoReproductor : gestiona# Taller1_ReproductorDeMusicjkj-

