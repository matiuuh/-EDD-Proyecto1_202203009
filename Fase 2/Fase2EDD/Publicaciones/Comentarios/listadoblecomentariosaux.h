#ifndef LISTADOBLECOMENTARIOSAUX_H
#define LISTADOBLECOMENTARIOSAUX_H

#include "nodocomentario.h"
#include <iostream>

class ListaDobleComentariosAux {
private:
    NodoComentario* cabeza;
    NodoComentario* cola;

public:
    ListaDobleComentariosAux();

    // Método para agregar un comentario
    void agregarComentario(std::shared_ptr<Comentario> comentario);

    // Método para mostrar todos los comentarios
    void mostrarComentarios() const;

    // Método para eliminar todos los comentarios (si es necesario)
    void limpiar();

    // Destructor para liberar memoria
    ~ListaDobleComentariosAux();

    bool estaVacia() const;
};

#endif // LISTADOBLECOMENTARIOSAUX_H
