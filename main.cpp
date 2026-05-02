#include <iostream>
#include "core/ControladorApp.h"

int main() {
    // Pequeño mensaje de inicializacion
    std::cout << "Iniciando el sistema de la Fonoteca..." << std::endl;
    std::cout << "Cargando motor de base de datos..." << std::endl;

    // Instanciamos el controlador en la pila (stack)
    // Su constructor se encargará de levantar las listas, los estados y cargar los archivos.
    ControladorApp app;

    // Arrancamos el bucle principal del menú
    app.iniciar();

    // Cuando el usuario presione 'X', el método iniciar() terminará,
    // el destructor de 'app' limpiará toda la memoria dinámica de las listas
    // y el programa se cerrará limpiamente.
    std::cout << "Sistema cerrado exitosamente." << std::endl;

    return 0;
}
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
