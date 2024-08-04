#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include "Usuario.h"
#include <memory>
#include <iostream>

using namespace std;

class Nodo {
public:
    Usuario usuario;
    unique_ptr<Nodo> siguiente;

    Nodo(const Usuario& user, unique_ptr<Nodo> sig = nullptr);
};

class ListaEnlazada {
private:
    unique_ptr<Nodo> cabeza;

public:
    ListaEnlazada();
    ~ListaEnlazada() = default; // Se usa el destructor predeterminado, std::unique_ptr se encargará de liberar la memoria

    void agregarUsuario(const Usuario& usuario);
    void mostrarUsuarios() const;
};

#endif // LISTA_ENLAZADA_H
