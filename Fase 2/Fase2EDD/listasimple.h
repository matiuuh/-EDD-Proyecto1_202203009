#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <iostream>
#include <string>

// Nodo que contendrá el nombre y el correo del destinatario
class NodoSimple {
public:
    std::string nombre;
    std::string correo;
    NodoSimple* siguiente;

    NodoSimple(const std::string& nombre, const std::string& correo)
        : nombre(nombre), correo(correo), siguiente(nullptr) {}
};

class ListaSimple {
public:
    ListaSimple();  // Constructor

    // Agregar una solicitud (nombre y correo del destinatario)
    void agregar(const std::string& nombre, const std::string& correo);

    // Mostrar todas las solicitudes en la lista
    void mostrar() const;

    // Eliminar una solicitud por correo
    bool eliminarPorCorreo(const std::string& correo);

    // Buscar una solicitud por correo
    bool buscarPorCorreo(const std::string& correo) const;

    // Verificar si la lista está vacía
    bool estaVacia() const;

    // Obtener la cabeza de la lista (primer nodo)
    NodoSimple* obtenerPrimero() const;  // <-- Nuevo método agregado

    bool solicitudPendiente(const std::string& correo) const;

private:
    NodoSimple* cabeza; // Apuntador a la cabeza de la lista
};

#endif // LISTASIMPLE_H
