#ifndef NODO_H
#define NODO_H

#include <memory>
//#include "usuario.h"  // Incluye la definición de Usuario

// Declaración anticipada de la clase Usuario
class Usuario;

class Nodo {
public:
    Nodo(const Usuario& usuario);

    Usuario usuario;
    std::unique_ptr<Nodo> siguiente;
};

#endif // NODO_H
