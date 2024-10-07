#include "matrizdispersaamigos.h"

// Constructor
MatrizDispersaAmigos::MatrizDispersaAmigos() : raiz(nullptr) {}

// Método para agregar una amistad entre dos usuarios
void MatrizDispersaAmigos::agregarAmistad(const std::string& correoRemitente) {
    // Comprobar si ya existe la amistad
    if (buscarAmistad(correoRemitente)) {
        std::cout << "La amistad ya existe con " << correoRemitente << std::endl;
        return;
    }

    // Crear un nuevo nodo con el remitente
    std::shared_ptr<NodoMatriz> nuevoNodo = std::make_shared<NodoMatriz>(correoRemitente);

    if (!raiz) {
        raiz = nuevoNodo;
    } else {
        // Insertar en la columna correcta (implementación simple para demostración)
        std::shared_ptr<NodoMatriz> actual = raiz;

        // Navegar por la columna
        while (actual->abajo) {
            actual = actual->abajo;
        }
        actual->abajo = nuevoNodo;
    }

    std::cout << "Amistad agregada con " << correoRemitente << std::endl;
}

// Método para buscar si existe una amistad con el remitente
bool MatrizDispersaAmigos::buscarAmistad(const std::string& correoRemitente) {
    std::shared_ptr<NodoMatriz> nodoEncontrado = buscarNodo(correoRemitente);
    return nodoEncontrado != nullptr;
}

// Método para eliminar una amistad con el remitente
void MatrizDispersaAmigos::eliminarAmistad(const std::string& correoRemitente) {
    if (!buscarAmistad(correoRemitente)) {
        std::cout << "La amistad no existe con " << correoRemitente << std::endl;
        return;
    }

    // Lógica para eliminar la amistad de la matriz dispersa (simplificada para esta demostración)
    std::shared_ptr<NodoMatriz> actual = raiz;
    std::shared_ptr<NodoMatriz> anterior = nullptr;

    // Buscar la amistad
    while (actual && actual->correoRemitente != correoRemitente) {
        anterior = actual;
        actual = actual->abajo;
    }

    if (anterior) {
        anterior->abajo = actual->abajo;  // Eliminar el nodo
    } else {
        raiz = actual->abajo;  // Eliminar la raíz
    }

    std::cout << "Amistad eliminada con " << correoRemitente << std::endl;
}

// Método auxiliar para buscar un nodo en la matriz
std::shared_ptr<MatrizDispersaAmigos::NodoMatriz> MatrizDispersaAmigos::buscarNodo(const std::string& correoRemitente) const {
    std::shared_ptr<NodoMatriz> actual = raiz;
    while (actual) {
        if (actual->correoRemitente == correoRemitente) {
            return actual;
        }
        actual = actual->abajo;
    }
    return nullptr;
}

// Método para imprimir los amigos de un usuario
void MatrizDispersaAmigos::imprimirAmigos(const std::string& correoUsuario) const {
    std::shared_ptr<NodoMatriz> actual = raiz;
    while (actual) {
        std::cout << "Amigo: " << actual->correoRemitente << std::endl;
        actual = actual->abajo;
    }
}
