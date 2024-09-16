#include "listadoble.h"
#include <iostream>

// Constructor

ListaDoble::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

void ListaDoble::insertar(const Publicacion& publicacion) {
    NodoDoble* nuevoNodo = new NodoDoble(publicacion);

    if (!cabeza) {
        // La lista está vacía
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        // La lista no está vacía
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
}

void ListaDoble::eliminar(const std::string& idPublicacion) {
    // Implementa la lógica para eliminar una publicación (puedes buscar por ID si tu publicación lo tiene)
    NodoDoble* actual = cabeza;
    while (actual) {
        // Suponiendo que Publicacion tiene un método getId() para obtener el ID
        if (actual->publicacion.getCorreo().toStdString() == idPublicacion) {
            if (actual == cabeza) {
                cabeza = actual->siguiente;
                if (cabeza) cabeza->anterior = nullptr;
            } else if (actual == cola) {
                cola = actual->anterior;
                if (cola) cola->siguiente = nullptr;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            delete actual;
            return;
        }
        actual = actual->siguiente;
    }
}

void ListaDoble::mostrar() const {
    NodoDoble* actual = cabeza;
    while (actual) {
        // Imprime la publicación, puedes definir cómo mostrar una publicación
        std::cout << "Correo: " << actual->publicacion.getCorreo().toStdString()
                  << ", Contenido: " << actual->publicacion.getContenido().toStdString()
                  << ", Fecha: " << actual->publicacion.getFecha().toStdString()
                  << ", Hora: " << actual->publicacion.getHora().toStdString() << std::endl;
        actual = actual->siguiente;
    }
}

bool ListaDoble::estaVacia() const {
    return cabeza == nullptr;  // La lista está vacía si la cabeza es nullptr
}
