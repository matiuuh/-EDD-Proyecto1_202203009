#include "listadoblecomentariosaux.h"

// Constructor
ListaDobleComentariosAux::ListaDobleComentariosAux() : cabeza(nullptr), cola(nullptr) {}

// Método para agregar un comentario al final de la lista
void ListaDobleComentariosAux::agregarComentario(std::shared_ptr<Comentario> comentario) {
    NodoComentario* nuevoNodo = new NodoComentario(comentario);

    if (!cabeza) {  // Si la lista está vacía
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
}

// Método para mostrar todos los comentarios
void ListaDobleComentariosAux::mostrarComentarios() const {

    if (!cabeza) {  // Verificar si la lista está vacía
        std::cout << "No hay comentarios para mostrar." << std::endl;
        return;
    }

    NodoComentario* actual = cabeza;
    while (actual) {
        std::cout << "Comentario de: " << actual->comentario->getCorreo().toStdString() << std::endl;
        std::cout << "Contenido: " << actual->comentario->getContenido().toStdString() << std::endl;
        std::cout << "Fecha: " << actual->comentario->getFecha().toStdString() << " Hora: " << actual->comentario->getHora().toStdString() << std::endl;
        actual = actual->siguiente;
    }
}

// Método para eliminar todos los comentarios (limpiar la lista)
void ListaDobleComentariosAux::limpiar() {
    NodoComentario* actual = cabeza;
    while (actual) {
        NodoComentario* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = cola = nullptr;
}

// Destructor
ListaDobleComentariosAux::~ListaDobleComentariosAux() {
    limpiar();  // Limpiar la lista al destruirla
}
