#include <iostream>
#include <memory>
#include "NodoPublicacion.cpp"
#include <memory>


using namespace std;

class ListaDoblePublicaciones {
private:
    shared_ptr<NodoPublicacion> cabeza;
    shared_ptr<NodoPublicacion> cola;
    shared_ptr<NodoPublicacion> actual; // Nodo actual para navegación

public:
    ListaDoblePublicaciones() : cabeza(nullptr), cola(nullptr), actual(nullptr) {}

    void agregarPublicacion(const shared_ptr<Publicacion>& publicacion) {
        auto nuevoNodo = make_shared<NodoPublicacion>(publicacion);
        if (!cabeza) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
            cabeza->siguiente = cabeza; // Hacer circular
            cabeza->anterior = cola;    // Hacer circular
            actual = nuevoNodo; // El primer nodo es el actual
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            nuevoNodo->siguiente = cabeza; // Conectar al inicio para hacer circular
            cabeza->anterior = nuevoNodo;  // Conectar al final para hacer circular
            cola = nuevoNodo;
        }
    }

    void mostrarPublicacionActual() const {
        if (actual) {
            actual->publicacion->mostrarPublicacion();
        } else {
            cout << "No hay publicaciones para mostrar." << endl;
        }
    }

    void irSiguiente() {
        if (actual) {
            actual = actual->siguiente; // Ahora es circular, siempre habrá un siguiente
            mostrarPublicacionActual();
        }
    }

    void irAnterior() {
        if (actual) {
            actual = actual->anterior; // Ahora es circular, siempre habrá un anterior
            mostrarPublicacionActual();
        }
    }

    void reiniciar() {
        actual = cabeza; // Volver al inicio de la lista
    }

    int size() const {
        if (!cabeza) return 0;

        int count = 1;
        auto temp = cabeza;
        while (temp->siguiente != cabeza) {
            count++;
            temp = temp->siguiente;
        }
        return count;
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }

    shared_ptr<NodoPublicacion> obtenerCabeza() const {
        return cabeza;
    }

    void mostrarPublicaciones() const {
        if (!cabeza) {
            cout << "No hay publicaciones para mostrar." << endl;
            return;
        }

        int indice = 1;
        auto actual = cabeza;
        do {
            cout << indice << ". ";
            actual->publicacion->mostrarPublicacion();
            cout << "-----------------------" << endl;
            actual = actual->siguiente;
            indice++;
        } while (actual != cabeza); // Se recorre hasta volver al inicio
    }

    bool eliminarPublicacion(const std::shared_ptr<Publicacion>& publicacion) {
        if (!cabeza) return false; // Lista vacía

        auto actual = cabeza;
        do {
            if (*actual->publicacion == *publicacion) {
                if (actual == cabeza && actual == cola) {
                    // Único nodo en la lista
                    cabeza = nullptr;
                    cola = nullptr;
                } else {
                    if (actual == cabeza) {
                        cabeza = cabeza->siguiente;
                        cabeza->anterior = cola;
                        cola->siguiente = cabeza;
                    } else if (actual == cola) {
                        cola = cola->anterior;
                        cola->siguiente = cabeza;
                        cabeza->anterior = cola;
                    } else {
                        actual->anterior->siguiente = actual->siguiente;
                        actual->siguiente->anterior = actual->anterior;
                    }
                }
                return true; // Publicación eliminada con éxito
            }
            actual = actual->siguiente;
        } while (actual != cabeza); // Recorrer hasta volver al inicio

        return false; // No se encontró la publicación
    }

    // Contar el número de publicaciones asociadas a un correo específico
    int contarPublicaciones(const string& correoUsuario) const {
        int contador = 0;
        if (!cabeza) return contador; // Lista vacía

        auto temp = cabeza;
        do {
            if (temp->publicacion->getCorreoUsuario() == correoUsuario) {
                contador++;
            }
            temp = temp->siguiente;
        } while (temp != cabeza); // Se recorre hasta volver al inicio

        return contador;
    }

    void obtenerPublicaciones(const std::string& correoUsuario, ListaDoblePublicaciones& publicacionesUsuario) const {
    // Primero, asegúrate de que `publicacionesUsuario` esté vacía
    publicacionesUsuario = ListaDoblePublicaciones();

    if (estaVacia()) {
        // Si la lista original está vacía, simplemente salimos
        return;
    }

    auto temp = cabeza;
    do {
        // Verificamos si la publicación pertenece al usuario
        if (temp->publicacion->getCorreoUsuario() == correoUsuario) {
            // Agregamos la publicación a la lista de publicaciones del usuario
            publicacionesUsuario.agregarPublicacion(temp->publicacion);
        }
        temp = temp->siguiente;
    } while (temp != cabeza); // Se recorre hasta volver al inicio
}

};