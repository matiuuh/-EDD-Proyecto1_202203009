#include <memory>
#include <iostream>
#include "C:/Users/estua/OneDrive/Documentos/Proyecto1EDD/encabezados/Usuario.h"


using namespace std;

class Nodo {
public:
    Usuario usuario;
    unique_ptr<Nodo> siguiente;

    Nodo(const Usuario& usuario) : usuario(usuario), siguiente(nullptr) {}
};

class ListaEnlazada {
public:
    unique_ptr<Nodo> cabeza;

    ListaEnlazada();

    void agregarUsuario(const Usuario& usuario);
    Usuario* buscarUsuarioPorCorreo(const string& correo);
    void mostrarUsuarios() const;
};