#ifndef LISTADOBLEUSUARIOSDISPONIBLES_H
#define LISTADOBLEUSUARIOSDISPONIBLES_H

#include <memory>
#include <string>

// Definición del nodo que almacenará solo el correo del usuario
struct NodoUsuario {
    std::string correo;
    std::shared_ptr<NodoUsuario> siguiente;
    std::shared_ptr<NodoUsuario> anterior;

    NodoUsuario(const std::string& correo) : correo(correo), siguiente(nullptr), anterior(nullptr) {}
};

// Clase para la lista doblemente enlazada de correos de usuarios
class ListaDobleUsuariosDisponibles {
private:
    std::shared_ptr<NodoUsuario> cabeza;
    std::shared_ptr<NodoUsuario> cola;

public:
    ListaDobleUsuariosDisponibles();  // Constructor

    // Método para agregar un correo a la lista
    void agregarCorreo(const std::string& correo);

    // Método para eliminar un nodo por correo
    bool eliminarPorCorreo(const std::string& correo);

    // Método para obtener el primer nodo de la lista
    std::shared_ptr<NodoUsuario> obtenerPrimero();

    // Método para verificar si la lista está vacía
    bool estaVacia() const;
};

#endif // LISTADOBLEUSUARIOSDISPONIBLES_H
