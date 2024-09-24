#ifndef PAGINAB_H
#define PAGINAB_H

#define ORDEN 5  // Definir el grado del árbol B
#include "comentario.h"

using namespace std;

class PaginaB {
public:
    PaginaB();

    bool paginaLlena();  // Verifica si la página está llena
    shared_ptr<Comentario> keys[ORDEN];
    PaginaB* branches[ORDEN];
    int cuenta;

private:
};

#endif // PAGINAB_H
