#ifndef ARBOLBCOMENTARIOS_H
#define ARBOLBCOMENTARIOS_H

#include "comentario.h"
#include "paginab.h"
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class ArbolBComentarios {
public:
    ArbolBComentarios();
    void insertar(shared_ptr<Comentario> comentario);
    void graficar();
    void mostrarTodosLosComentarios();

private:
    PaginaB* root;
    void insertar(PaginaB** root, shared_ptr<Comentario> comentario);  // Inserta en una página
    void push(PaginaB* actualPage, shared_ptr<Comentario> comentario, bool &goUp, shared_ptr<Comentario>& mediano, PaginaB** newPage);
    bool buscarComentarioEnPagina(PaginaB* current, shared_ptr<Comentario> comentario, int &k);  // Busca en la página
    void dividir(PaginaB* current, shared_ptr<Comentario> comentario, PaginaB* rd, int k, shared_ptr<Comentario>& mediano, PaginaB** newPage);
    void insertarClave(PaginaB* current, shared_ptr<Comentario> comentario, PaginaB* rd, int k);
    void obtenerContenido(PaginaB* current, stringstream& accum, int& countNode, int& countAux, stringstream& accumLink);
    void escribirDot(string code);

    void mostrarComentariosDesdePagina(PaginaB* pagina);
    void pushNode(PaginaB* current, shared_ptr<Comentario> comentario, PaginaB* rd, int k);
};

#endif // ARBOLBCOMENTARIOS_H
