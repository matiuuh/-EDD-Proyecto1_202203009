#include "matrizadyacenterelacion.h"
#include <fstream>
#include <sstream>

// Clase Vecino (representa un amigo)
Vecino::Vecino(const std::string& correo) : correo(correo), siguiente(nullptr) {}

// Clase Nodo (representa un usuario)
Nodo::Nodo(const std::string& correo) : correo(correo), siguiente(nullptr), vecinos(nullptr) {}

// Insertar un vecino (amigo) en la lista de vecinos
void Nodo::insertarVecino(const std::string& correoAmigo) {
    auto nuevoVecino = std::make_shared<Vecino>(correoAmigo);
    if (!vecinos) {
        vecinos = nuevoVecino;
    } else {
        auto actual = vecinos;
        while (actual->siguiente) {
            if (actual->correo == correoAmigo) return;  // Evitar duplicados
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoVecino;
    }
}

// Clase MatrizAdyacenteRelacion (gestiona el grafo)
MatrizAdyacenteRelacion::MatrizAdyacenteRelacion() : cabeza(nullptr) {}

// Insertar un nuevo usuario en la matriz de adyacencia
void MatrizAdyacenteRelacion::insertarUsuario(const std::string& correoUsuario) {
    auto nuevoNodo = std::make_shared<Nodo>(correoUsuario);
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        auto actual = cabeza;
        while (actual->siguiente) {
            if (actual->correo == correoUsuario) return;  // Evitar duplicados
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

// Crear una relación de amistad (conexión) entre dos usuarios
void MatrizAdyacenteRelacion::crearRelacion(const std::string& correoUsuario, const std::string& correoAmigo) {
    auto actual = cabeza;
    while (actual) {
        if (actual->correo == correoUsuario) {
            actual->insertarVecino(correoAmigo);
            break;
        }
        actual = actual->siguiente;
    }

    // Insertar la relación recíproca
    actual = cabeza;
    while (actual) {
        if (actual->correo == correoAmigo) {
            actual->insertarVecino(correoUsuario);
            break;
        }
        actual = actual->siguiente;
    }
}

// Mostrar las relaciones de un usuario
void MatrizAdyacenteRelacion::mostrarRelaciones(const std::string& correoUsuario) {
    auto actual = cabeza;
    std::cout << "Buscando relaciones para: " << correoUsuario << std::endl;
    while (actual) {
        std::cout << "Revisando usuario: " << actual->correo << std::endl;  // Imprime el correo actual para ver si lo está recorriendo
        if (actual->correo == correoUsuario) {
            auto vecinoActual = actual->vecinos;
            std::cout << "Amigos de " << correoUsuario << ":\n";
            while (vecinoActual) {
                std::cout << "- " << vecinoActual->correo << std::endl;
                vecinoActual = vecinoActual->siguiente;
            }
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "Usuario no encontrado.\n";
}

// Método para graficar la matriz de adyacencia (opcional)
void MatrizAdyacenteRelacion::graficar(const std::string& filename) {
    std::ofstream out(filename + ".dot");
    if (!out) {
        std::cerr << "Error al crear el archivo dot\n";
        return;
    }

    out << "graph g {\n";
    out << "rankdir=LR;\n";

    auto actual = cabeza;
    while (actual) {
        std::stringstream nodoUsuario;
        nodoUsuario << "\"" << actual->correo << "\"";
        out << nodoUsuario.str() << ";\n";

        auto vecino = actual->vecinos;
        while (vecino) {
            out << nodoUsuario.str() << " -- \"" << vecino->correo << "\";\n";
            vecino = vecino->siguiente;
        }
        actual = actual->siguiente;
    }

    out << "}\n";
    out.close();

    // Comando para generar la imagen (si tienes Graphviz instalado)
    std::string command = "dot -Tpng " + filename + ".dot -o C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\" + filename + ".png";

    int result = system(command.c_str());

    if (result != 0) {
        std::cout << "Ocurrió un error al generar la imagen.\n";
    } else {
        std::cout << "La imagen fue generada exitosamente.\n";
    }
}
