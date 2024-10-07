#include "listadobleusuariosdisponibles.h"

// Constructor
ListaDobleUsuariosDisponibles::ListaDobleUsuariosDisponibles() : cabeza(nullptr), cola(nullptr) {}

/*
// Método para agregar un correo a la lista
void ListaDobleUsuariosDisponibles::agregarCorreo(const std::string& correo) {
    std::shared_ptr<NodoUsuario> nuevoNodo = std::make_shared<NodoUsuario>(correo);
    if (!cabeza) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
}*/

// Método para eliminar un nodo por correo
bool ListaDobleUsuariosDisponibles::eliminarPorCorreo(const std::string& correo) {
    std::shared_ptr<NodoUsuario> actual = cabeza;

    while (actual) {
        if (actual->correo == correo) {
            // Si el nodo a eliminar es la cabeza
            if (actual == cabeza) {
                cabeza = actual->siguiente;
                if (cabeza) {
                    cabeza->anterior = nullptr;
                }
            }
            // Si el nodo a eliminar es la cola
            else if (actual == cola) {
                cola = actual->anterior;
                if (cola) {
                    cola->siguiente = nullptr;
                }
            }
            // Si el nodo está en medio
            else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            return true; // Nodo eliminado
        }
        actual = actual->siguiente;
    }

    return false; // No se encontró el nodo con el correo dado
}

// Método para obtener el primer nodo de la lista
std::shared_ptr<NodoUsuario> ListaDobleUsuariosDisponibles::obtenerPrimero() {
    return cabeza;
}

// Método para verificar si la lista está vacía
bool ListaDobleUsuariosDisponibles::estaVacia() const {
    return cabeza == nullptr;
}

/*
// Método para iterar sobre los correos y aplicar una función
void ListaDobleUsuariosDisponibles::paraCadaCorreo(const std::function<void(const std::string&)>& funcion) const {
    std::shared_ptr<NodoUsuario> actual = cabeza;

    while (actual) {
        funcion(actual->correo);  // Llamamos a la función con el correo del nodo actual
        actual = actual->siguiente;  // Avanzamos al siguiente nodo
    }
}*/

// Método para agregar un usuario a la lista
void ListaDobleUsuariosDisponibles::agregarUsuario(const std::string& nombre, const std::string& apellido, const std::string& correo, const std::string& fechaNacimiento) {
    std::shared_ptr<NodoUsuario> nuevoNodo = std::make_shared<NodoUsuario>(nombre, apellido, correo, fechaNacimiento);
    if (!cabeza) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
}

// Método para iterar sobre los usuarios y aplicar una función
void ListaDobleUsuariosDisponibles::paraCadaUsuario(const std::function<void(const NodoUsuario&)>& funcion) const {
    std::shared_ptr<NodoUsuario> actual = cabeza;

    while (actual) {
        funcion(*actual);  // Llamamos a la función con el usuario actual
        actual = actual->siguiente;  // Avanzamos al siguiente nodo
    }
}
