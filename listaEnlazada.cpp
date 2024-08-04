#include "ListaEnlazada.h"
#include <iostream>
#include "Usuario.h"  // Asegúrate de incluir Usuario.h aquí

using namespace std;


Nodo::Nodo(const Usuario& user, unique_ptr<Nodo> sig)
    :usuario(user), siguiente(move(sig)) {}

ListaEnlazada::ListaEnlazada() : cabeza(nullptr) {}

void ListaEnlazada::agregarUsuario(const Usuario& usuario) {
    cabeza = make_unique<Nodo>(usuario, move(cabeza));
}

void ListaEnlazada::mostrarUsuarios() const {
    Nodo* actual = cabeza.get();
    while (actual != nullptr) {
            cout << "Nombre: " << actual->usuario.getNombre()
                << ", Apellidos: " << actual->usuario.getApellidos()
                << ", Fecha de Nacimiento: " << actual->usuario.getFechaNacimiento()
                << ", Correo: " << actual->usuario.getCorreo() << std::endl;
        actual = actual->siguiente.get();
    }
}
