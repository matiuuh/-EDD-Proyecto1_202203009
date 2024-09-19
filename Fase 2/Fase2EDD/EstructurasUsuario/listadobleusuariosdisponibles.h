#ifndef LISTADOBLEUSUARIOSDISPONIBLES_H
#define LISTADOBLEUSUARIOSDISPONIBLES_H

#include <memory>
#include <string>
#include <functional>

// Definición del nodo que almacenará solo el correo del usuario
struct NodoUsuario {
    std::string nombre;
    std::string apellido;
    std::string correo;
    std::string fechaNacimiento;
    std::shared_ptr<NodoUsuario> siguiente;
    std::shared_ptr<NodoUsuario> anterior;

    NodoUsuario(const std::string& nombre, const std::string& apellido, const std::string& correo, const std::string& fechaNacimiento)
        : nombre(nombre), apellido(apellido), correo(correo), fechaNacimiento(fechaNacimiento), siguiente(nullptr), anterior(nullptr) {}
};

// Clase para la lista doblemente enlazada de correos de usuarios
class ListaDobleUsuariosDisponibles {
private:
    std::shared_ptr<NodoUsuario> cabeza;
    std::shared_ptr<NodoUsuario> cola;

public:
    ListaDobleUsuariosDisponibles();  // Constructor

    // Método para agregar un correo a la lista
    //void agregarCorreo(const std::string& correo);

    // Método para eliminar un nodo por correo
    bool eliminarPorCorreo(const std::string& correo);

    // Método para obtener el primer nodo de la lista
    std::shared_ptr<NodoUsuario> obtenerPrimero();

    // Método para verificar si la lista está vacía
    bool estaVacia() const;

    //void paraCadaCorreo(const std::function<void(const std::string&)>& funcion) const;

    // Método para agregar un usuario a la lista
    void agregarUsuario(const std::string& nombre, const std::string& apellido, const std::string& correo, const std::string& fechaNacimiento);

    // Método para iterar sobre los usuarios y aplicar una función
    void paraCadaUsuario(const std::function<void(const NodoUsuario&)>& funcion) const;

};

#endif // LISTADOBLEUSUARIOSDISPONIBLES_H
