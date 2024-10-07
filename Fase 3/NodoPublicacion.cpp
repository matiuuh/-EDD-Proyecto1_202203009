#include <iostream>
//#include "Publicacion.cpp"
#include <memory>

using namespace std;

class NodoPublicacion {
public:
    shared_ptr<Publicacion> publicacion;
    shared_ptr<NodoPublicacion> siguiente;
    shared_ptr<NodoPublicacion> anterior;

    NodoPublicacion(const shared_ptr<Publicacion>& publicacion)
        : publicacion(publicacion), siguiente(nullptr), anterior(nullptr) {}
};