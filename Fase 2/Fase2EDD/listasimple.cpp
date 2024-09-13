#include "listasimple.h"

// Constructor
ListaSimple::ListaSimple() : cabeza(nullptr) {}

// Agregar una solicitud (nombre y correo)
void ListaSimple::agregar(const std::string& nombre, const std::string& correo) {
    NodoSimple* nuevoNodo = new NodoSimple(nombre, correo);
    if (!cabeza) {
        cabeza = nuevoNodo;  // Si la lista está vacía, nuevoNodo es la cabeza
    } else {
        NodoSimple* temp = cabeza;
        while (temp->siguiente) {
            temp = temp->siguiente;  // Recorre la lista hasta el último nodo
        }
        temp->siguiente = nuevoNodo; // Agregar el nuevo nodo al final
    }
}

// Mostrar todas las solicitudes (nombre y correo)
void ListaSimple::mostrar() const {
    NodoSimple* temp = cabeza;
    while (temp) {
        std::cout << "Nombre: " << temp->nombre << ", Correo: " << temp->correo << std::endl;
        temp = temp->siguiente;
    }
}

// Eliminar una solicitud por correo
bool ListaSimple::eliminarPorCorreo(const std::string& correo) {
    if (!cabeza) return false;  // Lista vacía

    NodoSimple* temp = cabeza;
    NodoSimple* anterior = nullptr;

    // Buscar la solicitud a eliminar
    while (temp && temp->correo != correo) {
        anterior = temp;
        temp = temp->siguiente;
    }

    if (!temp) return false;  // No se encontró el correo

    // Eliminar el nodo
    if (!anterior) {
        cabeza = temp->siguiente;  // Eliminar la cabeza
    } else {
        anterior->siguiente = temp->siguiente;  // Saltar el nodo a eliminar
    }

    delete temp;
    return true;
}

// Buscar si existe una solicitud por correo
bool ListaSimple::buscarPorCorreo(const std::string& correo) const {
    NodoSimple* temp = cabeza;
    while (temp) {
        if (temp->correo == correo) {
            return true;  // Se encontró una solicitud con ese correo
        }
        temp = temp->siguiente;
    }
    return false;  // No se encontró la solicitud
}

// Verificar si la lista está vacía
bool ListaSimple::estaVacia() const {
    return cabeza == nullptr;
}
