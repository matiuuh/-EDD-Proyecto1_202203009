#ifndef BSTPUBLICACIONES_H
#define BSTPUBLICACIONES_H

#include <string>
#include "listasimple.h"

class NodoBST {
public:
    std::string fecha;
    ListaSimple publicacionesPorFecha;
    NodoBST* izquierda;
    NodoBST* derecha;

    NodoBST(const std::string& fecha);
};

class BSTPublicaciones {
public:
    BSTPublicaciones();

    void insertar(const std::string& fecha, const std::string& contenido);
    void buscarPorFecha(const std::string& fecha) const;

private:
    NodoBST* raiz;
    NodoBST* insertarRecursivo(NodoBST* nodo, const std::string& fecha, const std::string& contenido);
    NodoBST* buscarRecursivo(NodoBST* nodo, const std::string& fecha) const;
};

#endif // BSTPUBLICACIONES_H
