#include "listadoble.h"

// Constructor
ListaDoble::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

// Método para insertar un nuevo nodo en la lista doblemente enlazada
void ListaDoble::insertar(const std::string& contenido, const std::string& fecha, const std::string& hora) {
    NodoDoble* nuevoNodo = new NodoDoble(contenido, fecha, hora);
    if (!cabeza) {
        cabeza = cola = nuevoNodo; // Si la lista está vacía, el nuevo nodo es la cabeza y la cola
    } else {
        cola->siguiente = nuevoNodo; // El nuevo nodo se agrega al final de la lista
        nuevoNodo->anterior = cola;
        cola = nuevoNodo; // Actualiza la cola al nuevo nodo
    }
}

// Método para mostrar todas las publicaciones en la lista doblemente enlazada
void ListaDoble::mostrar() const {
    NodoDoble* temp = cabeza;
    while (temp) {
        std::cout << "Fecha: " << temp->fecha << ", Hora: " << temp->hora << ", Contenido: " << temp->contenido << std::endl;
        temp = temp->siguiente;
    }
}
