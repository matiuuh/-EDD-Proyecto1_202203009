#include <iostream>
#include <string>
#include "NodoMatriz.cpp"
#include <functional>

using namespace std;


class MatrizDispersa {
private:
    NodoMatriz* cabeza;

public:
    MatrizDispersa() : cabeza(nullptr) {}

    void agregarAmistad(const string& correo1, const string& correo2) {
        NodoMatriz* nodo1 = buscarNodo(correo1);
        NodoMatriz* nodo2 = buscarNodo(correo2);

        if (!nodo1) {
            cout << "Nodo para " << correo1 << " no encontrado. Insertando nuevo nodo." << endl;
            insertarNombre(correo1);
            nodo1 = buscarNodo(correo1);
        }
        if (!nodo2) {
            cout << "Nodo para " << correo2 << " no encontrado. Insertando nuevo nodo." << endl;
            insertarNombre(correo2);
            nodo2 = buscarNodo(correo2);
        }

        if (nodo1 && nodo2) {
            nodo1->amigos.agregarAmigo(correo2);
            nodo2->amigos.agregarAmigo(correo1);
            cout << "Amistad entre " << correo1 << " y " << correo2 << " agregada a la matriz dispersa." << endl;
        } else {
            cout << "Error al agregar amistad: uno o ambos nodos no se encontraron." << endl;
        }
    }


    NodoMatriz* buscarNodo(const string nombre) const {
    NodoMatriz* actual = cabeza;
    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            cout << "Nodo encontrado para " << nombre << endl;
            return actual;
        }
        actual = actual->siguiente;
    }
    cout << "Nodo no encontrado para " << nombre << endl;
    return nullptr;
}

    void insertarNombre(const string& correo) {
        if (buscarNodo(correo) == nullptr) {
            NodoMatriz* nuevo = new NodoMatriz(correo);
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
            cout << "Nodo insertado para " << correo << endl;
        } else {
            cout << "Nodo ya existe para " << correo << endl;
        }
    }

    void obtenerAmigos(const string& correoUsuario, ListaEnlazadaAmigos& amigosLista) const {
        NodoMatriz* nodoUsuario = buscarNodo(correoUsuario); // Encuentra el nodo del usuario en la matriz

        if (nodoUsuario) {
            nodoUsuario->amigos.paraCadaAmigo([&](const string& correoAmigo) {
                cout << "Amigo encontrado: " << correoAmigo << endl;
                amigosLista.agregarAmigo(correoAmigo);
            });
        } else {
            cout << "No se encontró el usuario en la matriz dispersa." << endl;
        }
    }

    // Nuevo método para recorrer las relaciones de un usuario específico
    void paraCadaRelacionDelUsuario(const string& correoUsuario, const function<void(const string&, const string&)>& accion) const {
        NodoMatriz* nodoUsuario = buscarNodo(correoUsuario);
        if (nodoUsuario) {
            nodoUsuario->amigos.paraCadaAmigo([&](const string& amigo) {
                accion(correoUsuario, amigo); // Relación entre el usuario conectado y sus amigos
            });
        }
    }

    // Método para verificar si existe una amistad entre dos usuarios
    bool existeAmistad(const string& correo1, const string& correo2) const {
        NodoMatriz* nodo1 = buscarNodo(correo1);
        NodoMatriz* nodo2 = buscarNodo(correo2);

        if (nodo1 && nodo2) {
            // Verificar si correo2 está en la lista de amigos de correo1
            bool amistad1 = nodo1->amigos.existeAmigo(correo2);
            // Verificar si correo1 está en la lista de amigos de correo2
            bool amistad2 = nodo2->amigos.existeAmigo(correo1);

            return amistad1 && amistad2;
        }
        return false;
    }
};
