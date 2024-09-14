#include "listadobleusuariosdisponibles.h"

// Constructor
ListaDobleUsuariosDisponibles::ListaDobleUsuariosDisponibles() : cabeza(nullptr), cola(nullptr) {}

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
}

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
