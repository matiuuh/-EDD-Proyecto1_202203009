#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
#include <string>

class NodoDoble {
public:
    std::string contenido;
    std::string fecha;
    std::string hora;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(const std::string& cont, const std::string& fec, const std::string& hor)
        : contenido(cont), fecha(fec), hora(hor), siguiente(nullptr), anterior(nullptr) {}
};

class ListaDoble {
public:
    ListaDoble();
    void insertar(const std::string& contenido, const std::string& fecha, const std::string& hora);
    void mostrar() const;

private:
    NodoDoble* cabeza;
    NodoDoble* cola;
};

#endif // LISTADOBLE_H
