#include <string>

using namespace std;

// Clase PilaSolicitudes
class PilaSolicitudes {
public:
    struct NodoPilaSolicitudes {
        string solicitud;
        NodoPilaSolicitudes* siguiente;
    };

    NodoPilaSolicitudes* tope;

    PilaSolicitudes() : tope(nullptr) {}

    void eliminarSolicitud(const string& solicitud) {
    NodoPilaSolicitudes* actual = tope;
    NodoPilaSolicitudes* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->solicitud == solicitud) {
            if (anterior == nullptr) {
                // El nodo a eliminar es el tope de la pila
                tope = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            cout << "Solicitud eliminada: " << solicitud << endl;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    cout << "Solicitud no encontrada: " << solicitud << endl;
}


    void push(const string& solicitud) {
        NodoPilaSolicitudes* nuevoNodo = new NodoPilaSolicitudes{solicitud, tope};
        tope = nuevoNodo;
    }

    void pop() {
    if (tope) {
        //cout << "Solicitud en el tope (dentro de pop): " << tope->solicitud << endl;
        NodoPilaSolicitudes* nodoAEliminar = tope;
        tope = tope->siguiente;
        delete nodoAEliminar;
        //cout << "Nodo eliminado correctamente." << endl;
    } else {
        cout << "La pila está vacía, no se puede hacer pop." << endl;
    }
}

    NodoPilaSolicitudes* obtenerCima() const {
        return tope;  // Suponiendo que `tope` es el puntero a la cima de la pila
    }

    bool estaVacia() const {
        return tope == nullptr;
    }

    string obtenerTope() const {
        return tope ? tope->solicitud : "";
    }

    bool buscarSolicitud(const string& solicitud) const {
        NodoPilaSolicitudes* actual = tope;
        while (actual != nullptr) {
            if (actual->solicitud == solicitud) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void mostrarSolicitudes() const {
        NodoPilaSolicitudes* actual = tope;
        while (actual != nullptr) {
            cout << actual->solicitud << endl;
            actual = actual->siguiente;
        }
    }

    // Clase Iterador
    class Iterador {
    public:
        Iterador(NodoPilaSolicitudes* nodo) : actual(nodo) {}

        bool hasNext() const {
            return actual != nullptr;
        }

        string next() {
            if (hasNext()) {
                string solicitud = actual->solicitud;
                actual = actual->siguiente;
                return solicitud;
            }
            throw std::out_of_range("No hay más elementos en la pila.");
        }

    private:
        NodoPilaSolicitudes* actual;
    };

    Iterador obtenerIterador() const {
        return Iterador(tope);
    }

};
