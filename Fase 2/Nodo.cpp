#include <iostream>
#include <fstream>
#include <memory>
#include "Usuario.cpp"

class Usuario; // Forward declaration of Usuario class

class Nodo {
public:
    Usuario usuario;
    std::unique_ptr<Nodo> siguiente;

    Nodo(const Usuario& usuario) : usuario(usuario), siguiente(nullptr) {}
};