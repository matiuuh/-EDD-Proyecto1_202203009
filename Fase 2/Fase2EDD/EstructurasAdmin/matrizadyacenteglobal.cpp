#include "matrizadyacenteglobal.h"
#include <iostream>
#include <fstream>

// Inicialización de variables estáticas fuera de la clase
NodoUsuarioe* MatrizAdyacenteGlobal::listaUsuarios = nullptr;
std::vector<std::vector<int>> MatrizAdyacenteGlobal::matrizAdyacencia;
int MatrizAdyacenteGlobal::numUsuarios = 0;

MatrizAdyacenteGlobal::MatrizAdyacenteGlobal() {}

// Agregar un nuevo usuario a la lista enlazada y al grafo
void MatrizAdyacenteGlobal::agregarUsuario(const std::string& correoUsuario) {
    // Verificar si el usuario ya está en la lista enlazada
    if (obtenerIndice(correoUsuario) == -1) {
        NodoUsuarioe* nuevoUsuario = new NodoUsuarioe(correoUsuario, numUsuarios++);

        // Añadir el nuevo usuario al inicio de la lista enlazada
        nuevoUsuario->siguiente = listaUsuarios;
        listaUsuarios = nuevoUsuario;

        // Aumentar el tamaño de la matriz de adyacencia para incluir al nuevo usuario
        matrizAdyacencia.resize(numUsuarios);
        for (int i = 0; i < numUsuarios; ++i) {
            matrizAdyacencia[i].resize(numUsuarios, 0);  // Inicializar con 0 (sin amistad)
        }
    }
}

// Agregar una relación de amistad entre dos usuarios
void MatrizAdyacenteGlobal::agregarRelacion(const std::string& correo1, const std::string& correo2) {
    int indice1 = obtenerIndice(correo1);
    int indice2 = obtenerIndice(correo2);

    if (indice1 != -1 && indice2 != -1) {
        matrizAdyacencia[indice1][indice2] = 1;
        matrizAdyacencia[indice2][indice1] = 1;  // Amistad bidireccional
    }
}

// Eliminar una relación de amistad entre dos usuarios
void MatrizAdyacenteGlobal::eliminarRelacion(const std::string& correo1, const std::string& correo2) {
    int indice1 = obtenerIndice(correo1);
    int indice2 = obtenerIndice(correo2);

    if (indice1 != -1 && indice2 != -1) {
        matrizAdyacencia[indice1][indice2] = 0;
        matrizAdyacencia[indice2][indice1] = 0;  // Eliminar ambas direcciones
    }
}

// Verificar si dos usuarios son amigos
bool MatrizAdyacenteGlobal::sonAmigos(const std::string& correo1, const std::string& correo2) const {
    int indice1 = obtenerIndice(correo1);
    int indice2 = obtenerIndice(correo2);

    if (indice1 != -1 && indice2 != -1) {
        return matrizAdyacencia[indice1][indice2] == 1;
    }
    return false;
}

// Graficar la matriz de adyacencia
void MatrizAdyacenteGlobal::graficarMatriz() const {
    std::ofstream archivo("C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\grafoGlobal.dot");
    archivo << "graph G {\n";

    NodoUsuarioe* actual = listaUsuarios;
    while (actual) {
        NodoUsuarioe* actual2 = listaUsuarios;
        while (actual2) {
            if (matrizAdyacencia[actual->indice][actual2->indice] == 1) {
                archivo << "  \"" << actual->correoUsuario << "\" -- \"" << actual2->correoUsuario << "\";\n";
            }
            actual2 = actual2->siguiente;
        }
        actual = actual->siguiente;
    }

    archivo << "}\n";
    archivo.close();
    std::cout << "Gráfico generado en grafoGlobal.dot\n";

    // Generar la imagen
    std::string command = "dot -Tpng C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\grafoGlobal.dot -o C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\grafoGlobal.png";
    int result = system(command.c_str());

    if (result != 0) {
        std::cout << "Ocurrió un error al generar la imagen del gráfico global.\n";
    } else {
        std::cout << "La imagen del gráfico global fue generada exitosamente.\n";
    }
}


// Obtener el índice de un usuario en la matriz desde la lista enlazada
int MatrizAdyacenteGlobal::obtenerIndice(const std::string& correo) const {
    NodoUsuarioe* actual = listaUsuarios;
    while (actual) {
        if (actual->correoUsuario == correo) {
            return actual->indice;
        }
        actual = actual->siguiente;
    }
    return -1;  // No encontrado
}

//-----------------PARA OBTENER LA INSTANCIA GLOBAL-----------
MatrizAdyacenteGlobal& MatrizAdyacenteGlobal::getInstancia() {
    static MatrizAdyacenteGlobal instancia;  // Instancia local estática, segura para hilos
    return instancia;
}
