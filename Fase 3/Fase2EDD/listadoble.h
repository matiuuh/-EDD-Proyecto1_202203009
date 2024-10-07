#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "Publicaciones/publicacion.h"
#include <string>

class NodoDoble {
public:
    Publicacion publicacion;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(const Publicacion& pub)
        : publicacion(pub), siguiente(nullptr), anterior(nullptr) {}

    // Métodos de acceso (getters)
    Publicacion getPublicacion() const {
        return publicacion;
    }

    NodoDoble* getSiguiente() const {
        return siguiente;
    }
};

class ListaDoble
{
public:
    ListaDoble();

    void insertar(const Publicacion& publicacion);
    void eliminar(const std::string& idPublicacion);  // Añadir parámetros necesarios
    void mostrar() const;
    //Publicacion buscar(const std::string& idPublicacion) const;  // Añadir parámetros necesarios
    bool estaVacia() const;  // Agregar la declaración del método
    NodoDoble* getPrimerNodo() const;

private:
    NodoDoble* cabeza;  // Nodo cabeza de la lista
    NodoDoble* cola;    // Nodo cola de la lista
};

#endif // LISTADOBLE_H
