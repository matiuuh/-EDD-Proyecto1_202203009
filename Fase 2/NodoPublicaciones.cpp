
#include <iostream>
#include <memory>
#include <string>


using namespace std;

class NodoPublicaciones {
public:
    string correoUsuario;
    int numeroPublicaciones;
    unique_ptr<NodoPublicaciones> siguiente;

    NodoPublicaciones(const string& correo, int publicaciones)
        : correoUsuario(correo), numeroPublicaciones(publicaciones), siguiente(nullptr) {}
};