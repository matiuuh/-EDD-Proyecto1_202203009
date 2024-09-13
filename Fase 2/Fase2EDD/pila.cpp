#include "pila.h"

// Constructor
Pila::Pila() {}

// Agregar una solicitud a la pila
void Pila::push(const std::string& correo, const std::string& solicitud) {
    pila.push(std::make_unique<NodoSolicitud>(correo, solicitud));
}

// Obtener y eliminar la solicitud en la parte superior
std::unique_ptr<NodoSolicitud> Pila::pop() {
    if (pila.empty()) return nullptr;

    auto topSolicitud = std::move(pila.top());
    pila.pop();
    return topSolicitud;
}

// Eliminar una solicitud específica por correo
bool Pila::eliminarPorCorreo(const std::string& correo) {
    std::stack<std::unique_ptr<NodoSolicitud>> pilaTemporal;

    bool encontrada = false;
    while (!pila.empty()) {
        auto solicitud = std::move(pila.top());
        pila.pop();

        // Si encontramos la solicitud por correo, no la agregamos de nuevo a la pila
        if (solicitud->correo == correo) {
            encontrada = true;
            break;
        } else {
            pilaTemporal.push(std::move(solicitud));
        }
    }

    // Volver a transferir las solicitudes a la pila original
    while (!pilaTemporal.empty()) {
        pila.push(std::move(pilaTemporal.top()));
        pilaTemporal.pop();
    }

    return encontrada;
}

// Buscar una solicitud por correo del remitente
bool Pila::buscarPorCorreo(const std::string& correo) {
    std::stack<std::unique_ptr<NodoSolicitud>> pilaTemporal;
    bool encontrada = false;

    // Recorrer la pila sin modificarla para buscar la solicitud
    while (!pila.empty()) {
        auto solicitud = std::move(pila.top());
        pila.pop();

        // Si se encuentra la solicitud, se marca como encontrada
        if (solicitud->correo == correo) {
            encontrada = true;
        }
        pilaTemporal.push(std::move(solicitud));
    }

    // Volver a transferir las solicitudes a la pila original
    while (!pilaTemporal.empty()) {
        pila.push(std::move(pilaTemporal.top()));
        pilaTemporal.pop();
    }

    return encontrada;
}

// Verificar si la pila está vacía
bool Pila::estaVacia() const {
    return pila.empty();
}
