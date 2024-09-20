#ifndef LISTADOBLEPUBLICACIONESGLOBAL_H
#define LISTADOBLEPUBLICACIONESGLOBAL_H

#include "../Publicaciones/publicacion.h"

class NodoListaDoble
{
public:
    Publicacion publicacion;
    NodoListaDoble* siguiente;
    NodoListaDoble* anterior;

    NodoListaDoble(const Publicacion& pub)
        : publicacion(pub), siguiente(nullptr), anterior(nullptr) {}
};

class ListaDoblePublicacionesGlobal
{
public:
    static ListaDoblePublicacionesGlobal& getInstance();
    ListaDoblePublicacionesGlobal();

    void insertar(const Publicacion& publicacion);
    void eliminar(const std::string& idPublicacion);  // Añadir parámetros necesarios
    void mostrar() const;
    //Publicacion buscar(const std::string& idPublicacion) const;  // Añadir parámetros necesarios
    void generarGrafico() const;

private:
    static ListaDoblePublicacionesGlobal* instance;  // Instancia única del Singleton
    NodoListaDoble* cabeza;  // Nodo cabeza de la lista
    NodoListaDoble* cola;    // Nodo cola de la lista
};

#endif // LISTADOBLEPUBLICACIONESGLOBAL_H
