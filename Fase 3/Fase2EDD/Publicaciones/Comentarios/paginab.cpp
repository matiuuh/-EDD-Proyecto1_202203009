#include "paginab.h"

PaginaB::PaginaB() {
    for (int i = 0; i < ORDEN; i++) {
        keys[i] = nullptr;
    }

    for (int i = 0; i < ORDEN; i++) {
        branches[i] = nullptr;
    }

    cuenta = 0;
}

bool PaginaB::paginaLlena(){
    return this->cuenta == ORDEN-1;
}
