#ifndef BSTPUBLICACIONES_H
#define BSTPUBLICACIONES_H

#include "Publicaciones/publicacion.h"
#include "listadoble.h"


#include <string>

class NodoBST {
public:
    std::string fecha;
    ListaDoble publicacionesPorFecha;
    NodoBST* izquierda;
    NodoBST* derecha;

    NodoBST(const std::string& fecha);
};

class BSTPublicaciones {
public:
    BSTPublicaciones();

    // Insertar una publicación en el BST
    void insertar(const Publicacion& publicacion);

    // Buscar publicaciones por fecha
    void buscarPorFecha(const std::string& fecha) const;

    // Eliminar una publicación por fecha y contenido
    void eliminar(const Publicacion& publicacion);

    // Mostrar todas las publicaciones en el BST
    void mostrarPublicaciones() const;

    // Función recursiva para mostrar todas las publicaciones
    void mostrarRecursivo(NodoBST* nodo) const;

private:
    NodoBST* raiz;

    // Función recursiva para insertar publicaciones
    NodoBST* insertarRecursivo(NodoBST* nodo, const Publicacion& publicacion);

    // Función recursiva para buscar publicaciones por fecha
    NodoBST* buscarRecursivo(NodoBST* nodo, const std::string& fecha) const;

    // Función recursiva para eliminar una publicación
    NodoBST* eliminarRecursivo(NodoBST* nodo, const std::string& fecha, const std::string& contenido);

    // Encontrar el nodo mínimo en el subárbol derecho (para reemplazo)
    NodoBST* encontrarMinimo(NodoBST* nodo);
};

#endif // BSTPUBLICACIONES_H
