#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "Nodo.cpp"

class ListaEnlazadaAmigos {
private:
    struct Nodo {
        string correo;
        unique_ptr<Nodo> siguiente;
        Nodo(const string& correo) : correo(correo), siguiente(nullptr) {}
    };

    unique_ptr<Nodo> cabeza;

public:
    ListaEnlazadaAmigos() : cabeza(nullptr) {}

    // Método para agregar un amigo a la lista
    void agregarAmigo(const string& correo) {
        unique_ptr<Nodo> nuevoNodo = make_unique<Nodo>(correo);
        if (!cabeza) {
            cabeza = move(nuevoNodo);
        } else {
            Nodo* temp = cabeza.get();
            while (temp->siguiente) {
                temp = temp->siguiente.get();
            }
            temp->siguiente = move(nuevoNodo);
        }
    }

    // Método para iterar sobre la lista y realizar una acción con cada amigo
    void paraCadaAmigo(const function<void(const string&)>& accion) const {
        Nodo* temp = cabeza.get();
        while (temp) {
            accion(temp->correo);
            temp = temp->siguiente.get();
        }
    }

    bool estaVacia() const {
        return !cabeza;
    }

    // Método para contar el número de amigos en la lista
    int size() const {
        int contador = 0;
        Nodo* actual = cabeza.get();
        while (actual) {
            contador++;
            actual = actual->siguiente.get();
        }
        return contador;
    }
    
    // Método para obtener el primer nodo
    Nodo* getPrimero() const {
        return cabeza.get();
    }

    // Nuevo método para verificar si un amigo está en la lista
    bool existeAmigo(const string& correo) const {
        Nodo* temp = cabeza.get();
        while (temp) {
            if (temp->correo == correo) {
                return true;
            }
            temp = temp->siguiente.get();
        }
        return false;
    }

    // Método para mostrar los amigos en la lista
    void mostrarAmigos() const {
        Nodo* actual = cabeza.get();
        while (actual) {
            cout << actual->correo << endl;
            actual = actual->siguiente.get();
        }
    }
};