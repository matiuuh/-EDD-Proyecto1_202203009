#include "arbolbcomentarios.h"
#include <iostream>

// Constructor del nodo
NodoB::NodoB(bool hoja) : esHoja(hoja), n(0) {
    comentarios.resize(ORDEN - 1);
    hijos.resize(ORDEN);
}

// Función para insertar un comentario en un nodo que no está lleno
void NodoB::insertarNoLleno(const Comentario& comentario) {
    int i = n - 1;

    // Si es una hoja, insertamos el comentario directamente
    if (esHoja) {
        while (i >= 0 && comentarios[i].getFecha() + comentarios[i].getHora() > comentario.getFecha() + comentario.getHora()) {
            comentarios[i + 1] = comentarios[i];
            i--;
        }
        comentarios[i + 1] = comentario;
        n++;
    } else {
        // Si no es hoja, buscamos el hijo apropiado
        while (i >= 0 && comentarios[i].getFecha() + comentarios[i].getHora() > comentario.getFecha() + comentario.getHora())
            i--;
        i++;

        if (hijos[i]->n == ORDEN - 1) {
            dividirHijo(i, hijos[i]);
            if (comentarios[i].getFecha() + comentarios[i].getHora() < comentario.getFecha() + comentario.getHora())
                i++;
        }
        hijos[i]->insertarNoLleno(comentario);
    }
}

// Función para dividir un nodo hijo cuando está lleno
void NodoB::dividirHijo(int i, NodoB* hijo) {
    NodoB* nuevoNodo = new NodoB(hijo->esHoja);
    nuevoNodo->n = ORDEN / 2;

    // Mover la mitad de los comentarios al nuevo nodo
    for (int j = 0; j < ORDEN / 2 - 1; j++)
        nuevoNodo->comentarios[j] = hijo->comentarios[j + ORDEN / 2];

    // Si no es hoja, mover los hijos también
    if (!hijo->esHoja) {
        for (int j = 0; j < ORDEN / 2; j++)
            nuevoNodo->hijos[j] = hijo->hijos[j + ORDEN / 2];
    }

    hijo->n = ORDEN / 2 - 1;

    // Mover los hijos del nodo actual para hacer espacio
    for (int j = n; j >= i + 1; j--)
        hijos[j + 1] = hijos[j];

    // Insertar el nuevo hijo
    hijos[i + 1] = nuevoNodo;

    // Mover los comentarios del nodo actual
    for (int j = n - 1; j >= i; j--)
        comentarios[j + 1] = comentarios[j];

    // Insertar el comentario medio en el nodo actual
    comentarios[i] = hijo->comentarios[ORDEN / 2 - 1];

    n++;
}

// Función para mostrar los comentarios en orden
void NodoB::mostrar() {
    int i;
    for (i = 0; i < n; i++) {
        if (!esHoja)
            hijos[i]->mostrar();
        std::cout << comentarios[i].getContenido().toStdString() << " ("
                  << comentarios[i].getFecha().toStdString() << " "
                  << comentarios[i].getHora().toStdString() << ")" << std::endl;
    }

    if (!esHoja)
        hijos[i]->mostrar();
}

// Función para buscar un comentario por la clave (fecha y hora)
NodoB* NodoB::buscar(const QString& claveFechaHora) {
    int i = 0;
    while (i < n && claveFechaHora > comentarios[i].getFecha() + comentarios[i].getHora())
        i++;

    if (i < n && comentarios[i].getFecha() + comentarios[i].getHora() == claveFechaHora)
        return this;

    if (esHoja)
        return nullptr;

    return hijos[i]->buscar(claveFechaHora);
}

// Constructor del árbol B de comentarios
ArbolBComentarios::ArbolBComentarios() {
    raiz = nullptr;
}

// Función para insertar un comentario
void ArbolBComentarios::insertar(const Comentario& comentario) {
    if (!raiz) {
        raiz = new NodoB(true);
        raiz->comentarios[0] = comentario;
        raiz->n = 1;
    } else {
        if (raiz->n == ORDEN - 1) {
            NodoB* nuevoNodo = new NodoB(false);
            nuevoNodo->hijos[0] = raiz;
            nuevoNodo->dividirHijo(0, raiz);

            int i = 0;
            if (nuevoNodo->comentarios[0].getFecha() + nuevoNodo->comentarios[0].getHora() < comentario.getFecha() + comentario.getHora())
                i++;
            nuevoNodo->hijos[i]->insertarNoLleno(comentario);

            raiz = nuevoNodo;
        } else {
            raiz->insertarNoLleno(comentario);
        }
    }
}

// Función para mostrar todos los comentarios
void ArbolBComentarios::mostrar() {
    if (raiz)
        raiz->mostrar();
}
