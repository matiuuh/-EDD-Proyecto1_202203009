#ifndef NODOCOMENTARIO_H
#define NODOCOMENTARIO_H

#include <memory>
#include "comentario.h"

class NodoComentario {
public:
    std::shared_ptr<Comentario> comentario;
    NodoComentario* siguiente;
    NodoComentario* anterior;
    NodoComentario(std::shared_ptr<Comentario> c);
};

#endif // NODOCOMENTARIO_H
