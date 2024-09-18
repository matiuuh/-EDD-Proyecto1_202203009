#ifndef ARBOLBCOMENTARIOS_H
#define ARBOLBCOMENTARIOS_H

#include <vector>
#include "comentario.h"

const int ORDEN = 5;  // Orden 5 del árbol B

class NodoB {
public:
    NodoB(bool hoja);

    // Funciones de nodo
    void insertarNoLleno(const Comentario& comentario);
    void dividirHijo(int i, NodoB* hijo);
    void mostrar() const;
    NodoB* buscar(const QString& claveFechaHora);
    void listarComentarios(std::vector<Comentario>& listaComentarios); // Agregar esta función
    void mostrarTodosLosComentarios() const;

private:
    std::vector<Comentario> comentarios;  // Los comentarios almacenados en el nodo
    std::vector<NodoB*> hijos;            // Los hijos del nodo
    bool esHoja;                          // Indica si es un nodo hoja
    int n;                                // Número actual de comentarios en el nodo

    friend class ArbolBComentarios;
};

class ArbolBComentarios {
public:
    ArbolBComentarios();

    void insertar(const Comentario& comentario);
    void eliminar(const QString& claveFechaHora);
    Comentario* buscar(const QString& claveFechaHora);
    void mostrar() const;  // Muestra todos los comentarios en orden
    std::vector<Comentario> listarComentarios() const; // Agregar esta función
    void mostrarTodosLosComentarios() const;

private:
    NodoB* raiz;
};

#endif // ARBOLBCOMENTARIOS_H
