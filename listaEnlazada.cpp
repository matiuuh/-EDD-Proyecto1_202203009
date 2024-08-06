#include "./encabezados/ListaEnlazada.h"

using namespace std;
// Constructor
ListaEnlazada::ListaEnlazada() : cabeza(nullptr) {}

// Función para agregar usuarios
void ListaEnlazada::agregarUsuario(const Usuario& usuario) {
    unique_ptr<Nodo> nuevoNodo = make_unique<Nodo>(usuario);

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

// Función para buscar usuarios según el correo
Usuario* ListaEnlazada::buscarUsuarioPorCorreo(const string& correo) {
    Nodo* temp = cabeza.get();
    while (temp) {
        if (temp->usuario.getCorreo() == correo) {
            return &temp->usuario;
        }
        temp = temp->siguiente.get();
    }
    return nullptr; // Si no se encuentra el usuario
}

// Función para mostrar los usuarios
void ListaEnlazada::mostrarUsuarios() const {
    Nodo* temp = cabeza.get();
    while (temp) {
        cout << "Nombre: " << temp->usuario.getNombre() << ", Apellidos: " << temp->usuario.getApellidos()
            << ", Fecha de Nacimiento: " << temp->usuario.getFechaNacimiento() << ", Correo: " << temp->usuario.getCorreo()
            << endl;
        temp = temp->siguiente.get();
    }
}
