
#include <iostream>
#include <memory>
#include <string>


using namespace std;

class NodoMenosAmigos {
public:
    string correoUsuario;
    int numeroAmigos;
    unique_ptr<NodoMenosAmigos> siguiente;

    NodoMenosAmigos(const string& correo, int amigos)
        : correoUsuario(correo), numeroAmigos(amigos), siguiente(nullptr) {}
};