#include "listadoblepublicacionesglobal.h"

#include <iostream>
#include <fstream>  // Para std::ofstream
#include <cstdlib>  // Para system() y comandos externos
#include <iostream>  // Para std::cout

ListaDoblePublicacionesGlobal* ListaDoblePublicacionesGlobal::instance = nullptr;

ListaDoblePublicacionesGlobal& ListaDoblePublicacionesGlobal::getInstance() {
    if (!instance) {
        instance = new ListaDoblePublicacionesGlobal();
    }
    return *instance;
}

ListaDoblePublicacionesGlobal::ListaDoblePublicacionesGlobal() : cabeza(nullptr), cola(nullptr) {}

//***************************REPORTES MÓDULO USUARIO***************************
//------------------------AGREGAR FECHAS Y ACTUALIZAR--------------------
void agregarOActualizarFecha(NodoFecha*& cabeza, const std::string& fecha) {
    NodoFecha* actual = cabeza;

    // Buscar si la fecha ya está en la lista
    while (actual != nullptr) {
        if (actual->fecha == fecha) {
            actual->cantidadPublicaciones++; // Incrementar el contador si la fecha ya existe
            return;
        }
        actual = actual->siguiente;
    }

    // Si no está en la lista, agregar un nuevo nodo al inicio
    NodoFecha* nuevoNodo = new NodoFecha(fecha);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

//--------------------CONTAR FECHAS------------------------
void ListaDoblePublicacionesGlobal::contarFechasPublicaciones(NodoFecha*& listaFechas) {
    NodoListaDoble* actual = cabeza;

    // Recorrer la lista de publicaciones
    while (actual != nullptr) {
        // Agregar o actualizar la fecha de la publicación
        agregarOActualizarFecha(listaFechas, actual->publicacion.getFecha().toStdString());
        actual = actual->siguiente;
    }
}

//-------------------------ORDENAR FECHAS--------------------------
void ordenarListaPorCantidad(NodoFecha*& cabeza) {
    if (!cabeza || !cabeza->siguiente) return;

    bool intercambiado;
    do {
        intercambiado = false;
        NodoFecha* actual = cabeza;
        NodoFecha* anterior = nullptr;

        while (actual->siguiente != nullptr) {
            if (actual->cantidadPublicaciones < actual->siguiente->cantidadPublicaciones) {
                // Intercambiar nodos
                NodoFecha* temp = actual->siguiente;
                actual->siguiente = temp->siguiente;
                temp->siguiente = actual;

                if (anterior == nullptr) {
                    cabeza = temp;
                } else {
                    anterior->siguiente = temp;
                }

                intercambiado = true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
    } while (intercambiado);
}

//-----------------------LIBRERAR MEMORIA---------------------------
void ListaDoblePublicacionesGlobal::liberarListaFechas(NodoFecha*& cabeza) {
    while (cabeza != nullptr) {
        NodoFecha* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

//------------------------MOSTRAR FECHAS EN CONSOLA------------------
void ListaDoblePublicacionesGlobal::mostrarTopFechasPublicaciones() {
    NodoFecha* listaFechas = nullptr;

    // Contar las fechas en la lista de publicaciones
    contarFechasPublicaciones(listaFechas);

    // Ordenar la lista de fechas por cantidad de publicaciones
    ordenarListaPorCantidad(listaFechas);

    // Mostrar las tres fechas con más publicaciones
    NodoFecha* actual = listaFechas;
    int contador = 0;

    std::cout << "Top 3 Fechas con más publicaciones:" << std::endl;
    while (actual != nullptr && contador < 3) {
        std::cout << "Fecha: " << actual->fecha << ", Publicaciones: " << actual->cantidadPublicaciones << std::endl;
        actual = actual->siguiente;
        contador++;
    }

    // Liberar memoria de la lista de fechas
    liberarListaFechas(listaFechas);
}

void ListaDoblePublicacionesGlobal::insertar(const Publicacion& publicacion) {
    NodoListaDoble* nuevoNodo = new NodoListaDoble(publicacion);

    if (!cabeza) {
        // La lista está vacía
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        // La lista no está vacía
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
}

void ListaDoblePublicacionesGlobal::eliminar(const std::string& idPublicacion) {
    // Implementa la lógica para eliminar una publicación (puedes buscar por ID si tu publicación lo tiene)
    NodoListaDoble* actual = cabeza;
    while (actual) {
        // Suponiendo que Publicacion tiene un método getId() para obtener el ID
        if (actual->publicacion.getCorreo().toStdString() == idPublicacion) {
            if (actual == cabeza) {
                cabeza = actual->siguiente;
                if (cabeza) cabeza->anterior = nullptr;
            } else if (actual == cola) {
                cola = actual->anterior;
                if (cola) cola->siguiente = nullptr;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            delete actual;
            return;
        }
        actual = actual->siguiente;
    }
}

void ListaDoblePublicacionesGlobal::mostrar() const {
    NodoListaDoble* actual = cabeza;
    while (actual) {
        // Imprime la publicación, puedes definir cómo mostrar una publicación
        std::cout << "Correo: " << actual->publicacion.getCorreo().toStdString()
                  << ", Contenido: " << actual->publicacion.getContenido().toStdString()
                  << ", Fecha: " << actual->publicacion.getFecha().toStdString()
                  << ", Hora: " << actual->publicacion.getHora().toStdString() << std::endl;
        actual = actual->siguiente;
    }
}

void ListaDoblePublicacionesGlobal::generarGrafico() const {
    std::ofstream archivo("C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\lista_publicaciones.dot");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para generar el gráfico." << std::endl;
        return;
    }

    archivo << "digraph G {" << std::endl;
    archivo << "rankdir=LR;" << std::endl;
    archivo << "node [shape=record];" << std::endl;

    auto nodoActual = cabeza;
    int contador = 0;

    while (nodoActual != nullptr) {
        archivo << "Nodo" << contador << " [label=\"{"
                << nodoActual->publicacion.getCorreo().toStdString() << " | "
                << nodoActual->publicacion.getContenido().toStdString() << " | "
                << nodoActual->publicacion.getFecha().toStdString() << " | "
                << nodoActual->publicacion.getHora().toStdString()
                << "}\"];" << std::endl;

        if (nodoActual->siguiente != nullptr) {
            archivo << "Nodo" << contador << " -> Nodo" << contador + 1 << " [dir=both];" << std::endl;
        }

        nodoActual = nodoActual->siguiente;
        contador++;
    }

    archivo << "}" << std::endl;
    archivo.close();

    int returnCode = system("dot -Tpng \"C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\lista_publicaciones.dot\" -o \"C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\lista_publicaciones.png\"");

    if (returnCode == 0) {
        std::cout << "Graph generated successfully." << std::endl;
    } else {
        std::cout << "Graph generation failed with return code: " << returnCode << std::endl;
    }
}

