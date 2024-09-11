#include <iostream>
#include <fstream>
#include <memory>
#include "Relacion.cpp"

class NodoRelacion {
public:
    Relacion relacion;
    NodoRelacion* siguiente;

    NodoRelacion(const Relacion& r)
        : relacion(r), siguiente(nullptr) {}
};
