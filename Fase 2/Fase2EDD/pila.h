#ifndef PILA_H
#define PILA_H

#include <stack>
#include <string>
#include <memory>

// Nodo para almacenar la solicitud con el correo del remitente
struct NodoSolicitud {
    std::string correo;    // Correo del remitente
    std::string solicitud; // Contenido de la solicitud

    NodoSolicitud(const std::string& correo, const std::string& solicitud)
        : correo(correo), solicitud(solicitud) {}
};

class Pila {
public:
    // Constructor
    Pila();

    // Agregar una solicitud con el correo del remitente
    void push(const std::string& correo, const std::string& solicitud);

    // Obtener y eliminar la solicitud en la parte superior
    std::shared_ptr<NodoSolicitud> pop();

    // Eliminar una solicitud específica por correo
    bool eliminarPorCorreo(const std::string& correo);

    // Buscar una solicitud por correo del remitente (sin eliminar)
    bool buscarPorCorreo(const std::string& correo);

    // Verificar si la pila está vacía
    bool estaVacia() const;

    void imprimir() const;

private:
    std::stack<std::shared_ptr<NodoSolicitud>> pila;
};

#endif // PILA_H
