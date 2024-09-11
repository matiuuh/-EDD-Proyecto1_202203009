#include <iostream>
#include <memory>
#include "Usuario.cpp"


using namespace std;

// Clase ListaEnlazada
class ListaEnlazada {
public:
    unique_ptr<Nodo> cabeza;

    ListaEnlazada() : cabeza(nullptr) {}

    //funcion para agregar usuarios
    void agregarUsuario(const Usuario& usuario) {
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

    //función para buscar usuarios según el correo
    Usuario* buscarUsuarioPorCorreo(const string& correo) const {
        Nodo* temp = cabeza.get();
        while (temp) {
            if (temp->usuario.getCorreo() == correo) {
                return &temp->usuario;
            }
            temp = temp->siguiente.get();
        }
        return nullptr; // Si no se encuentra el usuario
    }

    //función para mostrar los usuarios
    void mostrarUsuarios() const {
        Nodo* temp = cabeza.get();
        while (temp) {
            cout << "Nombre: " << temp->usuario.getNombre() << ", Apellidos: " << temp->usuario.getApellidos()
                << ", Fecha de Nacimiento: " << temp->usuario.getFechaNacimiento() << ", Correo: " << temp->usuario.getCorreo()
                << endl;
            temp = temp->siguiente.get();
        }
    }

    // Método para eliminar usuario por correo
    bool eliminarUsuario(const string& correo) {
        if (!cabeza) return false; // Lista vacía

        if (cabeza->usuario.getCorreo() == correo) {
            cabeza = move(cabeza->siguiente);
            return true;
        }

        Nodo* temp = cabeza.get();
        while (temp->siguiente && temp->siguiente->usuario.getCorreo() != correo) {
            temp = temp->siguiente.get();
        }

        if (temp->siguiente) {
            temp->siguiente = move(temp->siguiente->siguiente);
            return true;
        }

        return false; // Usuario no encontrado
    }

    // Método en la clase ListaEnlazada para buscar el nombre a partir del correo
    string buscarNombrePorCorreo(const string& correo) const {
        Nodo* actual = cabeza.get(); // Usar .get() para obtener un puntero crudo desde el unique_ptr
        while (actual) {
            if (actual->usuario.getCorreo() == correo) {
                return actual->usuario.getNombre();
            }
            actual = actual->siguiente.get(); // Obtener el siguiente nodo con .get()
        }
        return ""; // Retornar una cadena vacía si no se encuentra el usuario
    }

    // Método para iterar sobre cada usuario y aplicar una acción
    void paraCadaUsuario(const function<void(Usuario*)>& accion) const {
        Nodo* temp = cabeza.get();
        while (temp) {
            accion(&temp->usuario); // Aplicar la acción al usuario actual
            temp = temp->siguiente.get(); // Mover al siguiente nodo
        }
    }
};