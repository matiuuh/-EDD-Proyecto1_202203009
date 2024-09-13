#include "bstpublicaciones.h"

// Constructor de NodoBST
NodoBST::NodoBST(const std::string& fecha)
    : fecha(fecha), izquierda(nullptr), derecha(nullptr) {}

// Constructor de BSTPublicaciones
BSTPublicaciones::BSTPublicaciones() : raiz(nullptr) {}

/*
// Método para insertar una publicación en el árbol
void BSTPublicaciones::insertar(const std::string& fecha, const std::string& contenido) {
    raiz = insertarRecursivo(raiz, fecha, contenido);
}*/

// Método para buscar publicaciones por fecha
void BSTPublicaciones::buscarPorFecha(const std::string& fecha) const {
    NodoBST* resultado = buscarRecursivo(raiz, fecha);
    if (resultado) {
        std::cout << "Publicaciones del " << fecha << ":" << std::endl;
        resultado->publicacionesPorFecha.mostrar();
    } else {
        std::cout << "No hay publicaciones en esa fecha." << std::endl;
    }
}
/*
// Método recursivo para insertar en el árbol
NodoBST* BSTPublicaciones::insertarRecursivo(NodoBST* nodo, const std::string& fecha, const std::string& contenido) {
    if (!nodo) {
        NodoBST* nuevoNodo = new NodoBST(fecha);
        nuevoNodo->publicacionesPorFecha.agregar(contenido);
        return nuevoNodo;
    }

    if (fecha < nodo->fecha) {
        nodo->izquierda = insertarRecursivo(nodo->izquierda, fecha, contenido);
    } else if (fecha > nodo->fecha) {
        nodo->derecha = insertarRecursivo(nodo->derecha, fecha, contenido);
    } else {
        nodo->publicacionesPorFecha.agregar(contenido);
    }

    return nodo;
}*/

// Método recursivo para buscar en el árbol
NodoBST* BSTPublicaciones::buscarRecursivo(NodoBST* nodo, const std::string& fecha) const {
    if (!nodo || nodo->fecha == fecha) {
        return nodo;
    }

    if (fecha < nodo->fecha) {
        return buscarRecursivo(nodo->izquierda, fecha);
    } else {
        return buscarRecursivo(nodo->derecha, fecha);
    }
}
