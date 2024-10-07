#include "listadoblecomentariosaux.h"

// Constructor
ListaDobleComentariosAux::ListaDobleComentariosAux() : cabeza(nullptr), cola(nullptr) {}

// Método para agregar un comentario al final de la lista
void ListaDobleComentariosAux::agregarComentario(std::shared_ptr<Comentario> comentario) {

    if (!comentario) {  // Asegúrate de que el comentario no sea nulo
        std::cout << "Error: Comentario es nulo." << std::endl;
        return;
    }

    NodoComentario* nuevoNodo = new NodoComentario(comentario);

    if (!cabeza) {  // Si la lista está vacía
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }

    if (comentario) {
        //std::cout << "Comentario agregado de: " << comentario->getCorreo().toStdString() << std::endl;
    } else {
        std::cerr << "Error: El comentario es nulo al imprimir." << std::endl;
    }

    // Verificación de consistencia
    if (nuevoNodo->anterior && nuevoNodo->anterior->siguiente != nuevoNodo) {
        std::cerr << "Error: Enlace inconsistente entre nodos." << std::endl;
    }
}

// Método para mostrar todos los comentarios
void ListaDobleComentariosAux::mostrarComentarios() const {
    if (!cabeza) {
        std::cout << "No hay comentarios para mostrar." << std::endl;
        return;
    }
    NodoComentario* actual = cabeza;
    while (actual) {
        std::cout << "Comentario de: " << actual->comentario->getCorreo().toStdString() << std::endl;
        actual = actual->siguiente;
        // Depuración: Verificar punteros
        if (actual) {
            std::cout << "Siguiente nodo encontrado, anterior: " << actual->anterior << std::endl;
        }
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

bool ListaDobleComentariosAux::estaVacia() const {
    return cabeza == nullptr;
}
