#include "bstpublicaciones.h"

NodoBST::NodoBST(const std::string& fecha)
    : fecha(fecha), izquierda(nullptr), derecha(nullptr) {}

BSTPublicaciones::BSTPublicaciones() : raiz(nullptr) {}
/*
void BSTPublicaciones::insertar(const std::string& fecha, const std::string& contenido) {
    raiz = insertarRecursivo(raiz, fecha, contenido);
}

NodoBST* BSTPublicaciones::insertarRecursivo(NodoBST* nodo, const std::string& fecha, const std::string& contenido) {
    if (!nodo) {
        NodoBST* nuevoNodo = new NodoBST(fecha);
        nuevoNodo->publicacionesPorFecha.insertar(contenido, fecha, "");
        return nuevoNodo;
    }

    if (fecha < nodo->fecha) {
        nodo->izquierda = insertarRecursivo(nodo->izquierda, fecha, contenido);
    } else if (fecha > nodo->fecha) {
        nodo->derecha = insertarRecursivo(nodo->derecha, fecha, contenido);
    } else {
        nodo->publicacionesPorFecha.insertar(contenido, fecha, "");
    }

    return nodo;
}

NodoBST* BSTPublicaciones::buscarRecursivo(NodoBST* nodo, const std::string& fecha) const {
    if (!nodo || nodo->fecha == fecha) {
        return nodo;
    }

    if (fecha < nodo->fecha) {
        return buscarRecursivo(nodo->izquierda, fecha);
    } else {
        return buscarRecursivo(nodo->derecha, fecha);
    }
}*/
