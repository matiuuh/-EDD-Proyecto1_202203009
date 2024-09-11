#include <iostream>
#include <fstream>

using namespace std;

// Clase ListaSimpleSolicitudes
class ListaSimpleSolicitudes {
public:
    struct NodoLista {
        string solicitud;
        NodoLista* siguiente;
    };

    NodoLista* cabeza;

    ListaSimpleSolicitudes() : cabeza(nullptr) {}

    ~ListaSimpleSolicitudes() {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            NodoLista* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void agregarSolicitud(const string& solicitud) {
        NodoLista* nuevoNodo = new NodoLista{solicitud, cabeza};
        cabeza = nuevoNodo;
    }

    bool eliminarSolicitud(const string& solicitud) {
        NodoLista* actual = cabeza;
        NodoLista* anterior = nullptr;
        while (actual != nullptr) {
            if (actual->solicitud == solicitud) {
                if (anterior == nullptr) {
                    cabeza = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        return false;
    }

    bool buscarSolicitud(const string& solicitud) const {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            if (actual->solicitud == solicitud) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void mostrarSolicitudes() const {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->solicitud << endl;
            actual = actual->siguiente;
        }
    }

    NodoLista* obtenerCabeza() const {
        return cabeza;  // Suponiendo que `cabeza` es el puntero a la cabeza de la lista
    }
    
    bool existeSolicitudPendiente(const std::string& emisor, const std::string& receptor) const {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            // Verificamos si la solicitud está en el formato "emisor:receptor"
            std::string solicitud = actual->solicitud;
            size_t pos = solicitud.find(':');
            if (pos != std::string::npos) {
                std::string solicitudEmisor = solicitud.substr(0, pos);
                std::string solicitudReceptor = solicitud.substr(pos + 1);

                // Verificamos el estado de la solicitud si es necesario
                if (solicitudEmisor == emisor && solicitudReceptor == receptor) {
                    return true; // Encontramos la solicitud pendiente
                }
            }
            actual = actual->siguiente;
        }
        return false; // No encontramos ninguna solicitud pendiente
    }


};
