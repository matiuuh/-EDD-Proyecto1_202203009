#include "nodocomentario.h"

// Constructor del NodoComentario
NodoComentario::NodoComentario(std::shared_ptr<Comentario> c)
    : comentario(c), siguiente(nullptr), anterior(nullptr) {
    // No es necesario código adicional aquí, ya que todo se inicializa en la lista de inicialización
}
