#include "BSTPublicaciones.h"
#include <iostream>
#include "listadoble.h"
//#include "Publicaciones/colaconteos.h"

// Constructor del NodoBST
NodoBST::NodoBST(const std::string& fecha)
    : fecha(fecha), izquierda(nullptr), derecha(nullptr) {}

// Constructor del BST
BSTPublicaciones::BSTPublicaciones() : raiz(nullptr) {}

// Función para insertar una publicación en el BST
void BSTPublicaciones::insertar(const Publicacion& publicacion) {
    raiz = insertarRecursivo(raiz, publicacion);
}

// Función recursiva para insertar una publicación
NodoBST* BSTPublicaciones::insertarRecursivo(NodoBST* nodo, const Publicacion& publicacion) {
    std::string fecha = publicacion.getFecha().toStdString();

    if (!nodo) {
        NodoBST* nuevoNodo = new NodoBST(fecha);
        nuevoNodo->publicacionesPorFecha.insertar(publicacion);
        return nuevoNodo;
    }

    if (fecha < nodo->fecha) {
        nodo->izquierda = insertarRecursivo(nodo->izquierda, publicacion);
    } else if (fecha > nodo->fecha) {
        nodo->derecha = insertarRecursivo(nodo->derecha, publicacion);
    } else {
        nodo->publicacionesPorFecha.insertar(publicacion);
    }

    return nodo;
}

// Función para buscar publicaciones por fecha
void BSTPublicaciones::buscarPorFecha(const std::string& fecha) const {
    NodoBST* nodo = buscarRecursivo(raiz, fecha);
    if (nodo) {
        std::cout << "Publicaciones del " << fecha << ":\n";
        nodo->publicacionesPorFecha.mostrar();
    } else {
        std::cout << "No se encontraron publicaciones para la fecha: " << fecha << std::endl;
    }
}

// Función recursiva para buscar publicaciones por fecha
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

// Función para eliminar una publicación del BST
void BSTPublicaciones::eliminar(const Publicacion& publicacion) {
    std::string fecha = publicacion.getFecha().toStdString();
    std::string contenido = publicacion.getContenido().toStdString();
    raiz = eliminarRecursivo(raiz, fecha, contenido);
}

// Función recursiva para eliminar una publicación
NodoBST* BSTPublicaciones::eliminarRecursivo(NodoBST* nodo, const std::string& fecha, const std::string& contenido) {
    if (!nodo) {
        return nullptr;  // Si el nodo es nulo, no hay nada que eliminar
    }

    if (fecha < nodo->fecha) {
        nodo->izquierda = eliminarRecursivo(nodo->izquierda, fecha, contenido);
    } else if (fecha > nodo->fecha) {
        nodo->derecha = eliminarRecursivo(nodo->derecha, fecha, contenido);
    } else {
        // Si se encuentra la fecha, eliminar la publicación de la lista
        nodo->publicacionesPorFecha.eliminar(contenido);

        // Si la lista de publicaciones por fecha está vacía, eliminar el nodo del BST
        if (nodo->publicacionesPorFecha.estaVacia()) {
            NodoBST* temp;

            // Caso 1: Nodo sin hijos
            if (!nodo->izquierda && !nodo->derecha) {
                delete nodo;
                return nullptr;
            }

            // Caso 2: Nodo con un solo hijo
            if (!nodo->izquierda || !nodo->derecha) {
                temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
                delete nodo;
                return temp;
            }

            // Caso 3: Nodo con dos hijos
            temp = encontrarMinimo(nodo->derecha);
            nodo->fecha = temp->fecha;
            nodo->publicacionesPorFecha = temp->publicacionesPorFecha;
            nodo->derecha = eliminarRecursivo(nodo->derecha, temp->fecha, contenido);
        }
    }

    return nodo;
}

// Función para encontrar el nodo mínimo en el subárbol derecho
NodoBST* BSTPublicaciones::encontrarMinimo(NodoBST* nodo) {
    while (nodo && nodo->izquierda) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

// Función para mostrar todas las publicaciones en el BST
void BSTPublicaciones::mostrarPublicaciones() const {
    mostrarRecursivo(raiz);
}

// Función recursiva para mostrar todas las publicaciones
void BSTPublicaciones::mostrarRecursivo(NodoBST* nodo) const {
    if (!nodo) return;

    // Mostrar publicaciones del subárbol izquierdo
    mostrarRecursivo(nodo->izquierda);

    // Mostrar publicaciones del nodo actual
    std::cout << "Fecha: " << nodo->fecha << std::endl;
    nodo->publicacionesPorFecha.mostrar();

    // Mostrar publicaciones del subárbol derecho
    mostrarRecursivo(nodo->derecha);
}

// Método para agregar todas las publicaciones de un usuario al BST
void BSTPublicaciones::agregarPublicacionesDeLista(ListaDoble& listaPublicaciones) {
    NodoDoble* nodoActual = listaPublicaciones.getPrimerNodo();  // Obtener el primer nodo de la lista

    // Recorrer la lista de publicaciones y agregarlas al BST
    while (nodoActual != nullptr) {
        Publicacion publicacion = nodoActual->getPublicacion();  // Obtener la publicación del nodo

        insertar(publicacion);  // Insertar la publicación en el BST
        nodoActual = nodoActual->getSiguiente();  // Moverse al siguiente nodo
    }
}

void BSTPublicaciones::recorrerInOrdenRecursivo(NodoBST* nodo, std::function<void(const Publicacion&)> funcion) const {
    if (!nodo) return;

    // Recorrer el subárbol izquierdo
    recorrerInOrdenRecursivo(nodo->izquierda, funcion);

    // Aplicar la función a todas las publicaciones en el nodo actual
    NodoDoble* nodoPublicacion = nodo->publicacionesPorFecha.getPrimerNodo();
    while (nodoPublicacion) {
        funcion(nodoPublicacion->getPublicacion());
        nodoPublicacion = nodoPublicacion->getSiguiente();
    }

    // Recorrer el subárbol derecho
    recorrerInOrdenRecursivo(nodo->derecha, funcion);
}

// Implementación del método recorrerInOrden
void BSTPublicaciones::recorrerInOrden(std::function<void(const Publicacion&)> funcion) const {
    recorrerInOrdenRecursivo(raiz, funcion);
}

void BSTPublicaciones::recorrerPreOrdenRecursivo(NodoBST* nodo, std::function<void(const Publicacion&)> funcion) const {
    if (!nodo) return;

    // Aplicar la función a todas las publicaciones en el nodo actual
    NodoDoble* nodoPublicacion = nodo->publicacionesPorFecha.getPrimerNodo();
    while (nodoPublicacion) {
        funcion(nodoPublicacion->getPublicacion());
        nodoPublicacion = nodoPublicacion->getSiguiente();
    }

    // Recorrer el subárbol izquierdo
    recorrerPreOrdenRecursivo(nodo->izquierda, funcion);

    // Recorrer el subárbol derecho
    recorrerPreOrdenRecursivo(nodo->derecha, funcion);
}

void BSTPublicaciones::recorrerPreOrden(std::function<void(const Publicacion&)> funcion) const {
    recorrerPreOrdenRecursivo(raiz, funcion);
}

void BSTPublicaciones::recorrerPostOrdenRecursivo(NodoBST* nodo, std::function<void(const Publicacion&)> funcion) const {
    if (!nodo) return;

    // Recorrer el subárbol izquierdo
    recorrerPostOrdenRecursivo(nodo->izquierda, funcion);

    // Recorrer el subárbol derecho
    recorrerPostOrdenRecursivo(nodo->derecha, funcion);

    // Aplicar la función a todas las publicaciones en el nodo actual
    NodoDoble* nodoPublicacion = nodo->publicacionesPorFecha.getPrimerNodo();
    while (nodoPublicacion) {
        funcion(nodoPublicacion->getPublicacion());
        nodoPublicacion = nodoPublicacion->getSiguiente();
    }
}

void BSTPublicaciones::recorrerPostOrden(std::function<void(const Publicacion&)> funcion) const {
    recorrerPostOrdenRecursivo(raiz, funcion);
}


