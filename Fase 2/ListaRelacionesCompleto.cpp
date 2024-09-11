#include <iostream>
#include <fstream>
#include <memory>
#include <functional> // Add the necessary header file for std::function
#include "NodoRelacion.cpp"

using namespace std;

class ListaRelacionesCompleto {
private:
    NodoRelacion* cabeza;
    NodoRelacion* cola;

public:
    ListaRelacionesCompleto() : cabeza(nullptr), cola(nullptr) {}

    // Método para agregar una relación a la lista
    void agregarRelacion(const std::string& usuario1, const std::string& usuario2) {
        Relacion nuevaRelacion(usuario1, usuario2);
        NodoRelacion* nuevoNodo = new NodoRelacion(nuevaRelacion);

        if (!cabeza) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            cola = nuevoNodo;
        }
    }

    // Método para recorrer la lista y aplicar una función a cada nodo
    void paraCadaRelacion(const std::function<void(const Relacion&)>& accion) const {
        NodoRelacion* actual = cabeza;
        while (actual) {
            accion(actual->relacion);
            actual = actual->siguiente;
        }
    }

    // Destructor para liberar memoria
    ~ListaRelacionesCompleto() {
        NodoRelacion* actual = cabeza;
        while (actual) {
            NodoRelacion* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
};