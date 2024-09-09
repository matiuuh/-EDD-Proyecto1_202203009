#include <iostream>
#include <fstream>
#include "Publicacion.cpp"
#include <memory>

using namespace std;


class ListaDoblePublicacionesGlobal {
private:
    struct Nodo {
        std::shared_ptr<Publicacion> publicacion;
        std::shared_ptr<Nodo> siguiente;
        std::shared_ptr<Nodo> anterior;

        Nodo(std::shared_ptr<Publicacion> pub) : publicacion(pub), siguiente(nullptr), anterior(nullptr) {}
    };

    std::shared_ptr<Nodo> cabeza;
    std::shared_ptr<Nodo> cola;

public:
    ListaDoblePublicacionesGlobal() : cabeza(nullptr), cola(nullptr) {}

    void agregarPublicacion(const std::shared_ptr<Publicacion>& publicacion) {
        auto nuevoNodo = std::make_shared<Nodo>(publicacion);
        if (cabeza == nullptr) {
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
    }

    bool eliminarPublicacion(const std::shared_ptr<Publicacion>& publicacion) {
        auto actual = cabeza;
        while (actual != nullptr) {
            if (*actual->publicacion == *publicacion) {
                // Publicación encontrada, eliminamos el nodo
                if (actual == cabeza && actual == cola) {
                    // Nodo único en la lista
                    cabeza = cola = nullptr;
                } else if (actual == cabeza) {
                    cabeza = cabeza->siguiente;
                    cabeza->anterior = nullptr;
                } else if (actual == cola) {
                    cola = cola->anterior;
                    cola->siguiente = nullptr;
                } else {
                    actual->anterior->siguiente = actual->siguiente;
                    actual->siguiente->anterior = actual->anterior;
                }
                return true; // Publicación eliminada con éxito
            }
            actual = actual->siguiente;
        }
        return false; // No se encontró la publicación
    }

    void generarGrafico(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo + ".dot");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo para generar el gráfico." << std::endl;
            return;
        }

        archivo << "digraph G {" << std::endl;
        archivo << "rankdir=LR;" << std::endl; // Establecer la orientación de izquierda a derecha
        archivo << "node [shape=record];" << std::endl;

        auto nodoActual = cabeza;
        int contador = 0;

        while (nodoActual != nullptr) {
            archivo << "Nodo" << contador << " [label=\"{"
                    << nodoActual->publicacion->getCorreoUsuario() << " | "
                    << nodoActual->publicacion->getContenido() << " | "
                    << nodoActual->publicacion->getFecha() << " | "
                    << nodoActual->publicacion->getHora()
                    << "}\"];" << std::endl;

            if (nodoActual->siguiente != nullptr) {
                archivo << "Nodo" << contador << " -> Nodo" << contador + 1 << " [dir=both];" << std::endl;
            }

            nodoActual = nodoActual->siguiente;
            contador++;
        }

        archivo << "}" << std::endl;
        archivo.close();

        std::cout << "Gráfico generado en " << nombreArchivo << ".dot" << std::endl;

        // Generar la imagen a partir del archivo DOT
        std::string comando = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
        system(comando.c_str());

        std::cout << "Imagen generada en " << nombreArchivo << ".png" << std::endl;
    }


};