#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <ctime> // Para obtener la fecha y hora actual
#include <functional>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <regex>


using json = nlohmann::json;
using namespace std;

class Relacion {
public:
    std::string usuario1;
    std::string usuario2;

    Relacion(const std::string& u1, const std::string& u2)
        : usuario1(u1), usuario2(u2) {}
};

class NodoRelacion {
public:
    Relacion relacion;
    NodoRelacion* siguiente;

    NodoRelacion(const Relacion& r)
        : relacion(r), siguiente(nullptr) {}
};

class ListaRelacionesCompleto {
private:
    NodoRelacion* cabeza;
    NodoRelacion* cola;

public:
    ListaRelacionesCompleto() : cabeza(nullptr), cola(nullptr) {}

    // Método para agregar una relación a la lista
    void agregarRelacion(const std::string& usuario1, const std::string& usuario2) {
        Relacion nuevaRelacion(usuario1, usuario2);
        NodoRelacion* nuevoNodo = new NodoRelacion(nuevaRelacion);

        if (!cabeza) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            cola = nuevoNodo;
        }
    }

    // Método para recorrer la lista y aplicar una función a cada nodo
    void paraCadaRelacion(const std::function<void(const Relacion&)>& accion) const {
        NodoRelacion* actual = cabeza;
        while (actual) {
            accion(actual->relacion);
            actual = actual->siguiente;
        }
    }

    // Destructor para liberar memoria
    ~ListaRelacionesCompleto() {
        NodoRelacion* actual = cabeza;
        while (actual) {
            NodoRelacion* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
};

//ListaDoblePublicacionesGlobal listaPublicacionesGlobal;
ListaRelacionesCompleto listaRelaciones;

// Clase ListaEnlazadaAmigos para almacenar los correos de los amigos
class ListaEnlazadaAmigos {
private:
    struct Nodo {
        string correo;
        unique_ptr<Nodo> siguiente;
        Nodo(const string& correo) : correo(correo), siguiente(nullptr) {}
    };

    unique_ptr<Nodo> cabeza;

public:
    ListaEnlazadaAmigos() : cabeza(nullptr) {}

    // Método para agregar un amigo a la lista
    void agregarAmigo(const string& correo) {
        unique_ptr<Nodo> nuevoNodo = make_unique<Nodo>(correo);
        if (!cabeza) {
            cabeza = move(nuevoNodo);
        } else {
            Nodo* temp = cabeza.get();
            while (temp->siguiente) {
                temp = temp->siguiente.get();
            }
            temp->siguiente = move(nuevoNodo);
        }
    }

    // Método para iterar sobre la lista y realizar una acción con cada amigo
    void paraCadaAmigo(const function<void(const string&)>& accion) const {
        Nodo* temp = cabeza.get();
        while (temp) {
            accion(temp->correo);
            temp = temp->siguiente.get();
        }
    }

    bool estaVacia() const {
        return !cabeza;
    }

    // Método para contar el número de amigos en la lista
    int size() const {
        int contador = 0;
        Nodo* actual = cabeza.get();
        while (actual) {
            contador++;
            actual = actual->siguiente.get();
        }
        return contador;
    }
    
    // Método para obtener el primer nodo
    Nodo* getPrimero() const {
        return cabeza.get();
    }

    // Nuevo método para verificar si un amigo está en la lista
    bool existeAmigo(const string& correo) const {
        Nodo* temp = cabeza.get();
        while (temp) {
            if (temp->correo == correo) {
                return true;
            }
            temp = temp->siguiente.get();
        }
        return false;
    }

    // Método para mostrar los amigos en la lista
    void mostrarAmigos() const {
        Nodo* actual = cabeza.get();
        while (actual) {
            cout << actual->correo << endl;
            actual = actual->siguiente.get();
        }
    }
};

class NodoPublicaciones {
public:
    string correoUsuario;
    int numeroPublicaciones;
    unique_ptr<NodoPublicaciones> siguiente;

    NodoPublicaciones(const string& correo, int publicaciones)
        : correoUsuario(correo), numeroPublicaciones(publicaciones), siguiente(nullptr) {}
};

class ListaEnlazadaSimpleMayorPublicaciones {
private:
    unique_ptr<NodoPublicaciones> cabeza;

public:
    ListaEnlazadaSimpleMayorPublicaciones() : cabeza(nullptr) {}

    void agregarUsuario(const string& correo, int publicaciones) {
        auto nuevoNodo = make_unique<NodoPublicaciones>(correo, publicaciones);
        if (!cabeza || publicaciones > cabeza->numeroPublicaciones) {
            nuevoNodo->siguiente = move(cabeza);
            cabeza = move(nuevoNodo);
        } else {
            NodoPublicaciones* actual = cabeza.get();
            while (actual->siguiente && publicaciones <= actual->siguiente->numeroPublicaciones) {
                actual = actual->siguiente.get();
            }
            nuevoNodo->siguiente = move(actual->siguiente);
            actual->siguiente = move(nuevoNodo);
        }
    }

    void mostrarTop5() const {
        cout << "Top 5 usuarios con más publicaciones:" << endl;
        NodoPublicaciones* actual = cabeza.get();
        int count = 0;
        while (actual && count < 5) {
            cout << actual->correoUsuario << " (" << actual->numeroPublicaciones << " publicaciones)" << endl;
            ++count;
            actual = actual->siguiente.get();
        }
        if (count == 0) {
            cout << "No hay suficientes usuarios para mostrar el top 5." << endl;
        }
    }
};

class NodoMenosAmigos {
public:
    string correoUsuario;
    int numeroAmigos;
    unique_ptr<NodoMenosAmigos> siguiente;

    NodoMenosAmigos(const string& correo, int amigos)
        : correoUsuario(correo), numeroAmigos(amigos), siguiente(nullptr) {}
};

class ListaEnlazadaSimpleMenosAmigos {
private:
    unique_ptr<NodoMenosAmigos> cabeza;

public:
    ListaEnlazadaSimpleMenosAmigos() : cabeza(nullptr) {}

    void agregarUsuario(const string& correo, int amigos) {
        auto nuevoNodo = make_unique<NodoMenosAmigos>(correo, amigos);
        if (!cabeza || amigos < cabeza->numeroAmigos) {
            nuevoNodo->siguiente = move(cabeza);
            cabeza = move(nuevoNodo);
        } else {
            NodoMenosAmigos* actual = cabeza.get();
            while (actual->siguiente && amigos >= actual->siguiente->numeroAmigos) {
                actual = actual->siguiente.get();
            }
            nuevoNodo->siguiente = move(actual->siguiente);
            actual->siguiente = move(nuevoNodo);
        }
    }

    void mostrarTop5() const {
        cout << "Top 5 usuarios con menos amigos:" << endl;
        NodoMenosAmigos* actual = cabeza.get();
        int count = 0;
        while (actual && count < 5) {
            cout << actual->correoUsuario << " (" << actual->numeroAmigos << " amigos)" << endl;
            ++count;
            actual = actual->siguiente.get();
        }
        if (count == 0) {
            cout << "No hay suficientes usuarios para mostrar el top 5." << endl;
        }
    }
};

class Publicacion {
private:
    string correoUsuario;
    string contenido;
    string fecha;
    string hora;

public:
    Publicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora)
        : correoUsuario(correo), contenido(contenido), fecha(fecha), hora(hora) {}

    Publicacion(const std::string& correo, const std::string& contenido)
        : correoUsuario(correo), contenido(contenido) {
        // Obtener la fecha y hora actual
        time_t now = time(0);
        tm* ltm = localtime(&now);

        // Formatear la fecha y la hora
        fecha = to_string(1900 + ltm->tm_year) + "-" +
                to_string(1 + ltm->tm_mon) + "-" +
                to_string(ltm->tm_mday);

        hora = to_string(ltm->tm_hour) + ":" +
                to_string(ltm->tm_min) + ":" +
                to_string(ltm->tm_sec);
    }

    // Métodos para obtener los datos de la publicación
    string getCorreoUsuario() const { return correoUsuario; }
    string getContenido() const { return contenido; }
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }

    // Método para mostrar la publicación
    void mostrarPublicacion() const {
        cout << "Correo: " << correoUsuario << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Hora: " << hora << endl;
        cout << "Contenido: " << contenido << endl;
    }

    // Sobrecarga del operador == para comparar dos publicaciones
    bool operator==(const Publicacion& otra) const {
        return correoUsuario == otra.correoUsuario &&
            contenido == otra.contenido &&
            fecha == otra.fecha &&
            hora == otra.hora;
    }
};

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

class NodoPublicacion {
public:
    shared_ptr<Publicacion> publicacion;
    shared_ptr<NodoPublicacion> siguiente;
    shared_ptr<NodoPublicacion> anterior;

    NodoPublicacion(const shared_ptr<Publicacion>& publicacion)
        : publicacion(publicacion), siguiente(nullptr), anterior(nullptr) {}
};

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

class Solicitud {
public:
    std::string emisor;
    std::string receptor;
    std::string estado;

    Solicitud(const std::string& emisor, const std::string& receptor, const std::string& estado)
        : emisor(emisor), receptor(receptor), estado(estado) {}
};

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

class NodoMatriz {
public:
    string nombre;
    NodoMatriz* siguiente;
    ListaEnlazadaAmigos amigos; // Lista de amigos


    NodoMatriz(const string& nombre) : nombre(nombre), siguiente(nullptr) {}

};

class MatrizDispersa {
private:
    NodoMatriz* cabeza;

public:
    MatrizDispersa() : cabeza(nullptr) {}

    void agregarAmistad(const string& correo1, const string& correo2) {
        NodoMatriz* nodo1 = buscarNodo(correo1);
        NodoMatriz* nodo2 = buscarNodo(correo2);

        if (!nodo1) {
            cout << "Nodo para " << correo1 << " no encontrado. Insertando nuevo nodo." << endl;
            insertarNombre(correo1);
            nodo1 = buscarNodo(correo1);
        }
        if (!nodo2) {
            cout << "Nodo para " << correo2 << " no encontrado. Insertando nuevo nodo." << endl;
            insertarNombre(correo2);
            nodo2 = buscarNodo(correo2);
        }

        if (nodo1 && nodo2) {
            nodo1->amigos.agregarAmigo(correo2);
            nodo2->amigos.agregarAmigo(correo1);
            cout << "Amistad entre " << correo1 << " y " << correo2 << " agregada a la matriz dispersa." << endl;
        } else {
            cout << "Error al agregar amistad: uno o ambos nodos no se encontraron." << endl;
        }
    }


    NodoMatriz* buscarNodo(const string nombre) const {
    NodoMatriz* actual = cabeza;
    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            cout << "Nodo encontrado para " << nombre << endl;
            return actual;
        }
        actual = actual->siguiente;
    }
    cout << "Nodo no encontrado para " << nombre << endl;
    return nullptr;
}

    void insertarNombre(const string& correo) {
        if (buscarNodo(correo) == nullptr) {
            NodoMatriz* nuevo = new NodoMatriz(correo);
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
            cout << "Nodo insertado para " << correo << endl;
        } else {
            cout << "Nodo ya existe para " << correo << endl;
        }
    }

    void obtenerAmigos(const string& correoUsuario, ListaEnlazadaAmigos& amigosLista) const {
        NodoMatriz* nodoUsuario = buscarNodo(correoUsuario); // Encuentra el nodo del usuario en la matriz

        if (nodoUsuario) {
            nodoUsuario->amigos.paraCadaAmigo([&](const string& correoAmigo) {
                cout << "Amigo encontrado: " << correoAmigo << endl;
                amigosLista.agregarAmigo(correoAmigo);
            });
        } else {
            cout << "No se encontró el usuario en la matriz dispersa." << endl;
        }
    }

    // Nuevo método para recorrer las relaciones de un usuario específico
    void paraCadaRelacionDelUsuario(const string& correoUsuario, const function<void(const string&, const string&)>& accion) const {
        NodoMatriz* nodoUsuario = buscarNodo(correoUsuario);
        if (nodoUsuario) {
            nodoUsuario->amigos.paraCadaAmigo([&](const string& amigo) {
                accion(correoUsuario, amigo); // Relación entre el usuario conectado y sus amigos
            });
        }
    }

    // Método para verificar si existe una amistad entre dos usuarios
    bool existeAmistad(const string& correo1, const string& correo2) const {
        NodoMatriz* nodo1 = buscarNodo(correo1);
        NodoMatriz* nodo2 = buscarNodo(correo2);

        if (nodo1 && nodo2) {
            // Verificar si correo2 está en la lista de amigos de correo1
            bool amistad1 = nodo1->amigos.existeAmigo(correo2);
            // Verificar si correo1 está en la lista de amigos de correo2
            bool amistad2 = nodo2->amigos.existeAmigo(correo1);

            return amistad1 && amistad2;
        }
        return false;
    }
};

// Declaración anticipada
class ListaEnlazada;//resuelve el problema del orden de las clases

// Clase Usuario
class Usuario {
public:
    Usuario(const string& nombre, const string& apellidos, const string& fechaNacimiento, const string& correo, const string& contrasenia)
        : nombre(nombre), apellidos(apellidos), fechaNacimiento(fechaNacimiento), correo(correo), contrasenia(contrasenia) {}

    string getNombre() const { return nombre; }
    string getApellidos() const { return apellidos; }
    string getFechaNacimiento() const { return fechaNacimiento; }
    string getCorreo() const { return correo; }
    string getContrasenia() const { return contrasenia; }

    ListaDoblePublicaciones publicaciones;

    // Método para mostrar publicaciones
    void mostrarPublicaciones() const {
        if (publicaciones.estaVacia()) {
            std::cout << "No tienes publicaciones." << std::endl;
            return;
        }

        auto actual = publicaciones.obtenerCabeza();
        while (actual) {
            cout << "Fecha: " << actual->publicacion->getFecha() << endl;
            cout << "Hora: " << actual->publicacion->getHora() << endl;
            cout << "Contenido: " << actual->publicacion->getContenido() << endl;
            cout << "---------------------------------" << endl;

            actual = actual->siguiente;
        }
    }

    bool tieneSolicitudPendiente(const string& correo) const {
        return solicitudesEnviadas.buscarSolicitud(correo) || solicitudesRecibidas.buscarSolicitud(correo);
    }

    // Método `enviarSolicitud` debe ser no constante
    void enviarSolicitud(Usuario& emisor, Usuario& receptor) {
        if (!emisor.tieneSolicitudPendiente(receptor.getCorreo()) && !receptor.tieneSolicitudPendiente(emisor.getCorreo())) {
            emisor.solicitudesEnviadas.agregarSolicitud(receptor.getCorreo());
            receptor.solicitudesRecibidas.push(emisor.getCorreo());
            cout<<"solicitud enviada con exito a "<< receptor.correo<<endl;
        } else {
            cout << "Ya existe una solicitud pendiente entre estos usuarios." << endl;
        }
    }

    void mostrarSolicitudesRecibidas() const {
        cout << "Solicitudes recibidas por " << nombre << ":" << endl;

        PilaSolicitudes::Iterador it = solicitudesRecibidas.obtenerIterador();

        while (it.hasNext()) {
            cout << it.next() << endl;
        }
    }

    void aceptarSolicitud(Usuario* receptor, Usuario* emisor, MatrizDispersa& matriz) {
        if (receptor == nullptr || emisor == nullptr) {
            cout << "Error: Los punteros receptor o emisor son nulos." << endl;
            return;
        }

        // Verificar si hay una solicitud pendiente
        if (!receptor->getSolicitudesRecibidas().buscarSolicitud(emisor->getCorreo())) {
            cout << "Error: No hay una solicitud de amistad pendiente de " << emisor->getCorreo() << " a " << receptor->getCorreo() << "." << endl;
            return;
        }

        // Eliminar la solicitud de ambas partes
        receptor->getSolicitudesRecibidas().eliminarSolicitud(emisor->getCorreo());
        receptor->getSolicitudesEnviadas().eliminarSolicitud(emisor->getCorreo());
        emisor->getSolicitudesEnviadas().eliminarSolicitud(receptor->getCorreo());
        emisor->getSolicitudesRecibidas().eliminarSolicitud(receptor->getCorreo());

        // Agregar la amistad a la matriz dispersa
        matriz.agregarAmistad(receptor->getCorreo(), emisor->getCorreo());
        // Agregar la relación a la lista global de relaciones
        listaRelaciones.agregarRelacion(receptor->getCorreo(), emisor->getCorreo());

        cout << "Solicitud aceptada. Ahora son amigos." << endl;
    }

    void rechazarSolicitud(Usuario* receptor, Usuario* emisor) {
        if (receptor && emisor) {
            // Verificar y depurar antes de hacer pop en solicitudesRecibidas
            if (!receptor->solicitudesRecibidas.estaVacia()) {
                cout << "Solicitud en el tope (antes de pop): " << receptor->solicitudesRecibidas.obtenerTope() << endl;
                receptor->solicitudesRecibidas.pop();
                cout << "Solicitud eliminada de solicitudesRecibidas." << endl;
            } else {
                cout << "Error: No hay solicitudes recibidas para eliminar en receptor." << endl;
            }

            // Eliminar solicitudes en la lista de enviadas del receptor
            receptor->solicitudesEnviadas.eliminarSolicitud(emisor->getCorreo());

            // Eliminar solicitudes en la lista de enviadas y recibidas del emisor
            emisor->solicitudesEnviadas.eliminarSolicitud(receptor->getCorreo());
            if (!emisor->solicitudesRecibidas.estaVacia()) {
                cout << "Solicitud en el tope (antes de pop): " << emisor->solicitudesRecibidas.obtenerTope() << endl;
                emisor->solicitudesRecibidas.pop();
                cout << "Solicitud eliminada de solicitudesRecibidas." << endl;
            } else {
                cout << "Error: No hay solicitudes recibidas para eliminar en emisor." << endl;
            }

            cout << "Solicitud rechazada." << endl;
        } else {
            cout << "Error: Usuario receptor o emisor no válido." << endl;
        }
    }

    friend void mostrarPublicacionesDeAmigos(const Usuario& usuario, ListaDoblePublicaciones& listaPublicaciones, MatrizDispersa& matrizAmigos, ListaEnlazada& listaUsuarios);

    PilaSolicitudes& getSolicitudesRecibidas() {
        return solicitudesRecibidas;
    }

    ListaSimpleSolicitudes& getSolicitudesEnviadas() {
        return solicitudesEnviadas;
    }

    // Método para mostrar la información del usuario (opcional)
    void mostrarInfo() const {
        std::cout << "Nombre: " << nombre << " " << apellidos << "\n"
                << "Fecha de Nacimiento: " << fechaNacimiento << "\n"
                << "Correo: " << correo << "\n";
    }

private:
    string nombre;
    string apellidos;
    string fechaNacimiento;
    string correo;
    string contrasenia;

    ListaSimpleSolicitudes solicitudesEnviadas;
    PilaSolicitudes solicitudesRecibidas;
};

// Clase Nodo
class Nodo {
public:
    Usuario usuario;
    unique_ptr<Nodo> siguiente;

    Nodo(const Usuario& usuario) : usuario(usuario), siguiente(nullptr) {}
};

// Clase ListaEnlazada
class ListaEnlazada {
public:
    unique_ptr<Nodo> cabeza;

    ListaEnlazada() : cabeza(nullptr) {}

    //funcion para agregar usuarios
    void agregarUsuario(const Usuario& usuario) {
        unique_ptr<Nodo> nuevoNodo = make_unique<Nodo>(usuario);

        if (!cabeza) {
            cabeza = move(nuevoNodo);
        } else {
            Nodo* temp = cabeza.get();
            while (temp->siguiente) {
                temp = temp->siguiente.get();
            }
            temp->siguiente = move(nuevoNodo);
        }
    }

    //función para buscar usuarios según el correo
    Usuario* buscarUsuarioPorCorreo(const string& correo) const {
        Nodo* temp = cabeza.get();
        while (temp) {
            if (temp->usuario.getCorreo() == correo) {
                return &temp->usuario;
            }
            temp = temp->siguiente.get();
        }
        return nullptr; // Si no se encuentra el usuario
    }

    //función para mostrar los usuarios
    void mostrarUsuarios() const {
        Nodo* temp = cabeza.get();
        while (temp) {
            cout << "Nombre: " << temp->usuario.getNombre() << ", Apellidos: " << temp->usuario.getApellidos()
                << ", Fecha de Nacimiento: " << temp->usuario.getFechaNacimiento() << ", Correo: " << temp->usuario.getCorreo()
                << endl;
            temp = temp->siguiente.get();
        }
    }

    // Método para eliminar usuario por correo
    bool eliminarUsuario(const string& correo) {
        if (!cabeza) return false; // Lista vacía

        if (cabeza->usuario.getCorreo() == correo) {
            cabeza = move(cabeza->siguiente);
            return true;
        }

        Nodo* temp = cabeza.get();
        while (temp->siguiente && temp->siguiente->usuario.getCorreo() != correo) {
            temp = temp->siguiente.get();
        }

        if (temp->siguiente) {
            temp->siguiente = move(temp->siguiente->siguiente);
            return true;
        }

        return false; // Usuario no encontrado
    }

    // Método en la clase ListaEnlazada para buscar el nombre a partir del correo
    string buscarNombrePorCorreo(const string& correo) const {
        Nodo* actual = cabeza.get(); // Usar .get() para obtener un puntero crudo desde el unique_ptr
        while (actual) {
            if (actual->usuario.getCorreo() == correo) {
                return actual->usuario.getNombre();
            }
            actual = actual->siguiente.get(); // Obtener el siguiente nodo con .get()
        }
        return ""; // Retornar una cadena vacía si no se encuentra el usuario
    }

    // Método para iterar sobre cada usuario y aplicar una acción
    void paraCadaUsuario(const function<void(Usuario*)>& accion) const {
        Nodo* temp = cabeza.get();
        while (temp) {
            accion(&temp->usuario); // Aplicar la acción al usuario actual
            temp = temp->siguiente.get(); // Mover al siguiente nodo
        }
    }
};

// Método para cargar usuarios desde un archivo JSON
void cargarUsuariosDesdeArchivo(const std::string& archivoJSON, ListaEnlazada& listaUsuarios) {
    // Leer el archivo JSON
    std::ifstream archivo(archivoJSON);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << archivoJSON << std::endl;
        return;
    }

    // Parsear el archivo JSON
    json jsonUsuarios;
    archivo >> jsonUsuarios;

    // Iterar sobre cada usuario en el JSON
    for (const auto& usuarioJSON : jsonUsuarios) {
        // Extraer los datos
        std::string nombre = usuarioJSON["nombres"];
        std::string apellidos = usuarioJSON["apellidos"];
        std::string fechaNacimiento = usuarioJSON["fecha_de_nacimiento"];
        std::string correo = usuarioJSON["correo"];
        std::string password = usuarioJSON["contraseña"];

        // Verificar si el correo ya existe en la lista enlazada
        Usuario* usuarioExistente = listaUsuarios.buscarUsuarioPorCorreo(correo);
        if (usuarioExistente) {
            std::cout << "El usuario con correo " << correo << " ya está registrado en el sistema. Se omitirá esta entrada." << std::endl;
            continue; // Saltar a la siguiente iteración si el correo ya existe
        }

        // Crear un objeto Usuario a partir de los datos JSON
        Usuario nuevoUsuario(nombre, apellidos, fechaNacimiento, correo, password);

        // Agregar el usuario a la lista enlazada
        listaUsuarios.agregarUsuario(nuevoUsuario);
    }

    archivo.close();
    std::cout << "Usuarios cargados con éxito." << std::endl;
}

void cargarPublicacionesDesdeArchivo(const std::string& archivo, ListaEnlazada& listaUsuarios, ListaDoblePublicaciones& listaPublicaciones, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal) {
    // Leer el archivo JSON
    ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        cout << "Error al abrir el archivo: " << archivo << endl;
        return;
    }

    json jsonData;
    archivoEntrada >> jsonData;
    archivoEntrada.close();

    // Recorrer las publicaciones
    for (const auto& publicacionJson : jsonData) {
        string correo = publicacionJson["correo"];
        string contenido = publicacionJson["contenido"];
        string fecha = publicacionJson["fecha"];
        string hora = publicacionJson["hora"];

        // Buscar al usuario por correo
        Usuario* usuario = listaUsuarios.buscarUsuarioPorCorreo(correo);
        if (usuario != nullptr) {
            // Crear la publicación
            auto nuevaPublicacion = std::make_shared<Publicacion>(correo, contenido, fecha, hora);

            // Agregar la publicación a la lista de publicaciones del usuario
            usuario->publicaciones.agregarPublicacion(nuevaPublicacion);

            // Agregar la publicación al feed general (lista circular de publicaciones)
            listaPublicaciones.agregarPublicacion(nuevaPublicacion);

            // Agregar la publicación a la lista global
            listaPublicacionesGlobal.agregarPublicacion(nuevaPublicacion);
        } else {
            // Si no se encontró el correo en la lista de usuarios
            cout << "El correo " << correo << " no existe en el sistema." << endl;
        }
    }
}

void cargarSolicitudesDesdeArchivo(const std::string& archivo, ListaEnlazada& listaUsuarios, ListaSimpleSolicitudes& listaSolicitudes, MatrizDispersa& matriz) {
    // Abrir el archivo
    std::ifstream archivoJSON(archivo);
    if (!archivoJSON.is_open()) {
        std::cerr << "Error al abrir el archivo de solicitudes." << std::endl;
        return;
    }

    // Parsear el archivo JSON
    json solicitudesJSON;
    archivoJSON >> solicitudesJSON;

    // Recorrer cada solicitud en el archivo JSON
    for (const auto& solicitud : solicitudesJSON) {
        std::string emisor = solicitud["emisor"];
        std::string receptor = solicitud["receptor"];
        std::string estado = solicitud["estado"];

        std::cout << "Procesando solicitud: Emisor: " << emisor << ", Receptor: " << receptor << ", Estado: " << estado << std::endl;

        // Verificar si ambos usuarios existen
        Usuario* usuarioEmisor = listaUsuarios.buscarUsuarioPorCorreo(emisor);
        Usuario* usuarioReceptor = listaUsuarios.buscarUsuarioPorCorreo(receptor);

        if (usuarioEmisor == nullptr || usuarioReceptor == nullptr) {
            std::cout << "Solicitud descartada: El emisor o receptor no existe en el sistema." << std::endl;
            continue; // Saltar a la siguiente solicitud
        }

        // Verificar si ya existe una solicitud pendiente entre los usuarios
        bool solicitudPendiente = listaSolicitudes.buscarSolicitud(emisor + "->" + receptor);
        bool solicitudRecibida = usuarioReceptor->getSolicitudesRecibidas().buscarSolicitud(emisor);

        if (estado == "ACEPTADA") {
            if (solicitudPendiente) {
                // Caso 1: Existe una solicitud pendiente
                // Eliminar la solicitud de ambas partes
                listaSolicitudes.eliminarSolicitud(emisor + "->" + receptor);
                usuarioReceptor->getSolicitudesRecibidas().eliminarSolicitud(emisor);
                usuarioEmisor->getSolicitudesEnviadas().eliminarSolicitud(receptor);

                std::cout << "Solicitud aceptada y eliminada de la lista de solicitudes." << std::endl;
            } else {
                // Caso 2: No existe una solicitud pendiente
                std::cout << "Solicitud aceptada no encontrada en la lista de solicitudes." << std::endl;
            }

            // En ambos casos, se agrega la amistad a la matriz dispersa si no existe aún
            if (!matriz.existeAmistad(emisor, receptor)) {
                matriz.agregarAmistad(emisor, receptor);
                matriz.agregarAmistad(receptor, emisor); // Relación bidireccional
            }

            // Agregar la relación a la lista global de relaciones
            listaRelaciones.agregarRelacion(emisor, receptor);

            std::cout << "Ahora " << emisor << " y " << receptor << " son amigos." << std::endl;
        }

            else if (estado == "PENDIENTE") {
            if (!solicitudPendiente && !solicitudRecibida) {
                // Agregar la solicitud a la lista de solicitudes pendientes
                usuarioEmisor->getSolicitudesEnviadas().agregarSolicitud(receptor);
                usuarioReceptor->getSolicitudesRecibidas().push(emisor);

                std::cout << "Solicitud pendiente: " << emisor << " ha enviado una solicitud a " << receptor << "." << std::endl;
            } else {
                std::cout << "Solicitud pendiente ya existente entre " << emisor << " y " << receptor << ". Solicitud descartada." << std::endl;
            }
        }
    }

    std::cout << "Carga de solicitudes completada." << std::endl;
}

void mostrarInformacionUsuario(const Usuario& usuarioConectado) {
    cout << "Nombre: " << usuarioConectado.getNombre() << endl;
    cout << "Correo: " << usuarioConectado.getCorreo() << endl;
    cout << "Fecha de nacimiento: " << usuarioConectado.getFechaNacimiento() << endl;
    // Agregar más información según sea necesario
}

void mostrarAmigos(const MatrizDispersa& matrizAmigos, const Usuario& usuarioConectado) {
    ListaEnlazadaAmigos amigosLista;
    matrizAmigos.obtenerAmigos(usuarioConectado.getCorreo(), amigosLista);

    cout << "Amigos de " << usuarioConectado.getNombre() << ":" << endl;
    amigosLista.mostrarAmigos(); // Asegúrate de que `ListaEnlazadaAmigos` tenga un método `mostrarAmigos`
}

void mostrarPublicaciones(const ListaDoblePublicaciones& listaPublicaciones, const Usuario& usuarioConectado) {
    ListaDoblePublicaciones publicacionesUsuario;
    listaPublicaciones.obtenerPublicaciones(usuarioConectado.getCorreo(), publicacionesUsuario);

    cout << "Publicaciones de " << usuarioConectado.getNombre() << ":" << endl;
    publicacionesUsuario.mostrarPublicaciones(); // Asegúrate de que `ListaDoblePublicaciones` tenga un método `mostrarPublicaciones`
}

// Prototipos
void menu();
void menuUsuario(ListaEnlazada& lista, Usuario& usuarioConectado, MatrizDispersa& matriz, ListaDoblePublicaciones& listaPublicaciones, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal);
void iniciarSesion(ListaEnlazada& lista, MatrizDispersa& matriz, ListaDoblePublicaciones& listaPublicaciones, ListaSimpleSolicitudes& listaSolicitudes, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal);
void registro(ListaEnlazada&);
void menuAdmin(ListaEnlazada& listaUsuarios, MatrizDispersa& matriz, ListaDoblePublicaciones& listaPublicaciones, ListaSimpleSolicitudes& listaSolicitudes, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal);
void subMenuPerfil(ListaEnlazada& lista, const Usuario& usuarioConectado, MatrizDispersa& matrizAmigos, ListaDoblePublicaciones& listaPublicaciones);
void subMenuSolicitudes( Usuario& usuarioConectado, ListaEnlazada& lista, MatrizDispersa& matriz);
void subMenuPublicaciones(Usuario& usuarioConectado, ListaDoblePublicaciones& listaPublicaciones, MatrizDispersa& matrizAmigos, ListaEnlazada& listaUsuarios, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal);
void eliminarCuenta(ListaEnlazada& lista, const Usuario& usuarioConectado);
void mostrarPublicacionesDeAmigos(Usuario& usuarioConectado, ListaDoblePublicaciones& listaPublicaciones, MatrizDispersa& matrizAmigos);
void generarGraficoPilaSolicitudesRecibidas(const PilaSolicitudes& pilaSolicitudes);
void generarGraficoColaSolicitudesEnviadas(const ListaSimpleSolicitudes& listaSolicitudes);
void mostrarListaAmigos(const Usuario& usuarioConectado, MatrizDispersa& matrizAmigos);
void generarGraficoMatrizAmistades(const Usuario& usuarioConectado, MatrizDispersa& matriz, ListaEnlazada& listaUsuarios);
void generarGraficoListaDoble(const ListaDoblePublicaciones& lista);
void mostrarTop5UsuariosConMasPublicaciones(const ListaEnlazada& listaUsuarios, const ListaDoblePublicaciones& listaPublicaciones);
void mostrarTop5UsuariosConMenosAmigos(const ListaEnlazada& listaUsuarios, const MatrizDispersa& matriz);
void generarGraficoListaUsuarios(const ListaEnlazada& listaUsuarios);
string sanearIdentificador(const std::string& id);
void generarGraficoRelacionesAmistad(const ListaRelacionesCompleto& listaRelaciones, const ListaEnlazada& listaUsuarios);
void generarReportePublicacionesGlobal();
void generarReportePublicacionesGlobal(ListaDoblePublicacionesGlobal& listaPublicacionesGlobal) ;


// Definición fuera de la clase Usuario
void mostrarPublicacionesDeAmigos(const Usuario& usuario, ListaDoblePublicaciones& listaPublicaciones, MatrizDispersa& matrizAmigos, ListaEnlazada& listaUsuarios) {
    // Agregar las publicaciones del usuario conectado a la lista circular
    auto nodoPublicacionUsuario = usuario.publicaciones.obtenerCabeza();
    if (nodoPublicacionUsuario) {
        do {
            listaPublicaciones.agregarPublicacion(nodoPublicacionUsuario->publicacion);
            nodoPublicacionUsuario = nodoPublicacionUsuario->siguiente;
        } while (nodoPublicacionUsuario != usuario.publicaciones.obtenerCabeza());
    }

    // Luego, agregar las publicaciones de los amigos
    ListaEnlazadaAmigos amigosLista;
    matrizAmigos.obtenerAmigos(usuario.getCorreo(), amigosLista);

    cout << "Cantidad de amigos: " << amigosLista.size() << endl;

    amigosLista.paraCadaAmigo([&](const string& correoAmigo) {
        Usuario* amigo = listaUsuarios.buscarUsuarioPorCorreo(correoAmigo);
        if (amigo) {
            cout << "Extrayendo publicaciones de " << amigo->getNombre() << ":" << endl;

            auto nodoPublicacion = amigo->publicaciones.obtenerCabeza();
            if (nodoPublicacion) {
                do {
                    listaPublicaciones.agregarPublicacion(nodoPublicacion->publicacion);
                    nodoPublicacion = nodoPublicacion->siguiente;
                } while (nodoPublicacion != amigo->publicaciones.obtenerCabeza());
            }
        } else {
            cout << "No se pudo encontrar el usuario con correo: " << correoAmigo << endl;
        }
    });

    // Mostrar todas las publicaciones almacenadas en la lista circular doblemente enlazada
    cout << "Mostrando publicaciones de los amigos y del usuario:" << endl;
    listaPublicaciones.mostrarPublicaciones();
}


int main() {
    // Instancias de las clases
    ListaRelacionesCompleto listaRelaciones;

    menu();
    //system("pause");
    return 0;
}

//función del menú principal
void menu() {
    int opcion;
    //hago una instancia de listaEnlazada para acceder a sus métodos
    ListaEnlazada listaUsuarios;
    MatrizDispersa matriz;
    ListaDoblePublicaciones listaPublicaciones;
    ListaSimpleSolicitudes listaSolicitudes;
    ListaDoblePublicacionesGlobal listaPublicacionesGlobal;


    do {
        cout << "\t-----Menu-----\n";
        cout << "\t1. Iniciar sesion" << endl;
        cout << "\t2. Registrarse" << endl;
        cout << "\t3. Informacion" << endl;
        cout << "\t4. Salir" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion) {
            case 1:
                iniciarSesion(listaUsuarios, matriz, listaPublicaciones, listaSolicitudes, listaPublicacionesGlobal);
                cout << "\n";
                system("pause");
                break;
            case 2:
                registro(listaUsuarios);
                cout << "\n";
                system("pause");
                break;
            case 3:
                cout << "Nombre: Mateo Estuardo Diego Noriega" << endl;
                cout << "Carnet: 202203009" << endl;
                cout << "Link del repositorio: https://github.com/matiuuh/-EDD-Proyecto1_202203009.git" << endl;
                cout << "\n";
                listaUsuarios.mostrarUsuarios();
                system("pause");
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Ingrese una opcion valida." << endl;
                system("pause");
                break;
        }
        system("cls");
    } while (opcion != 4);
}

//función para el inicio de sesión
void iniciarSesion(ListaEnlazada& lista, MatrizDispersa& matriz, ListaDoblePublicaciones& listaPublicaciones, ListaSimpleSolicitudes& listaSolicitudes, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal) {
    string correo, contrasenia;
    cout << "Ingrese el correo: "; getline(cin, correo);
    cout << "Ingrese la contrasenia: "; getline(cin, contrasenia);

    // Verificar si es el administrador
    if (correo == "admin" && contrasenia == "EDD") {
        cout << "Inicio de sesion como Administrador exitoso. Bienvenido, Administrador!" << endl;
        menuAdmin(lista, matriz, listaPublicaciones, listaSolicitudes, listaPublicacionesGlobal);
        return; // Salir de la función después de iniciar sesión como administrador
    }

    // Buscar al usuario por correo
    Usuario* usuario = lista.buscarUsuarioPorCorreo(correo);
    if(usuario){
        // Verificar si la contraseña es correcta
        if(usuario->getContrasenia() == contrasenia){
            cout << "Inicio de sesion exitoso. Bienvenido, " << usuario->getNombre() << "!" << endl;
            menuUsuario(lista, *usuario, matriz, listaPublicaciones, listaPublicacionesGlobal);
        }else{
            cout << "Credenciales incorrectas" << endl;
        }
    }else {
        cout << "Credenciales incorrectas" << endl;
    }
}

//función para crear usuarios
void registro(ListaEnlazada& lista) {
    string nombre, apellidos, fechaNacimiento, correo, contrasenia;

    cout << "Ingrese el nombre: "; getline(cin, nombre);
    cout << "Ingrese los apellidos: "; getline(cin, apellidos);
    cout << "Ingrese la fecha de nacimiento (DD/MM/YYYY): "; getline(cin, fechaNacimiento);
    cout << "Ingrese el correo: "; getline(cin, correo);
    cout << "Ingrese la contrasenia: "; getline(cin, contrasenia);

    // Verificar si el correo ya existe
    if (lista.buscarUsuarioPorCorreo(correo)) {
        cout << "Error: Ya existe un usuario con este correo." << endl;
        return; // Salir de la función si el correo ya está registrado
    }

    Usuario nuevoUsuario(nombre, apellidos, fechaNacimiento, correo, contrasenia);
    lista.agregarUsuario(nuevoUsuario);

    cout << "Usuario registrado exitosamente." << endl;
}

//función para mostrar el menú de usuario
void menuUsuario(ListaEnlazada& lista, Usuario& usuarioConectado, MatrizDispersa& matriz, ListaDoblePublicaciones& listaPublicaciones, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal){
    int opcion;

    ListaDoblePublicaciones listaPublicacionesTemp;  // Mueve la declaración aquí
    auto nodoPublicacion = std::shared_ptr<NodoPublicacion>();

    do {
        cout << "\t-----Menu Usuario-----\n";
        cout << "\t1. Perfil" << endl;
        cout << "\t2. Solicitudes" << endl;
        cout << "\t3. Publicaciones" << endl;
        cout << "\t4. Reportes" << endl;
        cout << "\t5. Salir" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        system("cls");
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion) {
            case 1:
            cout<<"---------Perfil---------"<<endl;
                cout << "Usuario Conectado: " << usuarioConectado.getNombre() << " " << usuarioConectado.getApellidos() << endl;
                subMenuPerfil(lista, usuarioConectado, matriz, listaPublicaciones);
                cout << "\n";
                system("pause");
                break;
            case 2:
                cout<<"---------Solicitudes---------"<<endl;
                subMenuSolicitudes(usuarioConectado, lista, matriz);
                cout << "\n";
                system("pause");
                break;
            case 3:
                cout << "---------Publicaciones---------" << endl;
                subMenuPublicaciones(usuarioConectado, listaPublicaciones, matriz, lista, listaPublicacionesGlobal);
                cout << "\n";
                break;
            case 4:
                cout << "---------Reportes---------" << endl;

                // 1. Generar gráficos de las solicitudes (Pila y Cola)
                generarGraficoPilaSolicitudesRecibidas(usuarioConectado.getSolicitudesRecibidas());
                generarGraficoColaSolicitudesEnviadas(usuarioConectado.getSolicitudesEnviadas());

                // 2. Mostrar la lista de amigos
                mostrarListaAmigos(usuarioConectado, matriz);

                // 3. Generar gráfico de la matriz de amistades
                generarGraficoMatrizAmistades(usuarioConectado, matriz, lista);

                // 4. Reinicializar la lista temporal antes de llenarla
                listaPublicacionesTemp = ListaDoblePublicaciones();

                // 5. Mostrar las publicaciones de los amigos y agregarlas a listaPublicacionesTemp
                mostrarPublicacionesDeAmigos(usuarioConectado, listaPublicacionesTemp, matriz, lista);

                // 6. Agregar las publicaciones del usuario conectado a listaPublicacionesTemp
                nodoPublicacion = usuarioConectado.publicaciones.obtenerCabeza();

                // 7. Generar el gráfico de la lista doblemente enlazada circular
                generarGraficoListaDoble(listaPublicacionesTemp);

                system("pause");
                break;
            case 5:
                cout << "volviendo..." << endl;
                break;
            default:
                cout << "Ingrese una opcion valida." << endl;
                system("pause");
                break;
        }
        system("cls");
    } while (opcion != 5);
}


//función para mostrar el menú del administrador
void menuAdmin(ListaEnlazada& listaUsuarios, MatrizDispersa& matriz, ListaDoblePublicaciones& listaPublicaciones, ListaSimpleSolicitudes& listaSolicitudes, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal){
    int opcion;
    string archivoJSON = "C:/Users/estua/OneDrive/Documentos/Proyecto1EDD/usuarios.json";
    string archivoJSON1 = "C:/Users/estua/OneDrive/Documentos/Proyecto1EDD/publicaciones.json";
    string archivoSolicitudes = "C:/Users/estua/OneDrive/Documentos/Proyecto1EDD/solicitudes.json";

    do {
        cout << "\t-----Menu ADMINISTRADOR-----\n";
        cout << "\t1. Carga de usuarios" << endl;
        cout << "\t2. Carga de relaciones" << endl;
        cout << "\t3. Carga de publicaciones" << endl;
        cout << "\t4. Gestionear usuarios" << endl;
        cout << "\t5. Reportes" << endl;
        cout << "\t6. Salir" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion) {
            case 1:
            cout<<"---------Carga de usuarios---------"<<endl;
                // Llamada a la función para cargar usuarios
                cargarUsuariosDesdeArchivo(archivoJSON, listaUsuarios);
                cout << "\n";
                listaUsuarios.mostrarUsuarios(); // Mostrar usuarios cargados (opcional)
                system("pause");
                break;
            case 2:
                cout<<"---------Carga de relaciones---------"<<endl;
                cargarSolicitudesDesdeArchivo(archivoSolicitudes, listaUsuarios, listaSolicitudes, matriz);
                cout << "\n";
                system("pause");
                break;
            case 3:
                cout << "---------Carga de publicaciones---------" << endl;
                cargarPublicacionesDesdeArchivo(archivoJSON1, listaUsuarios, listaPublicaciones, listaPublicacionesGlobal);
                cout << "\n";
                system("pause");
                break;
            case 4:
                cout << "---------Gestion usuarios---------" << endl;
                system("pause");
                break;
            case 5:
                cout << "----------Reportes----------" << endl;
                generarGraficoListaUsuarios(listaUsuarios);
                mostrarTop5UsuariosConMasPublicaciones(listaUsuarios, listaPublicaciones);
                mostrarTop5UsuariosConMenosAmigos(listaUsuarios, matriz);
                // Aquí llamas al gráfico de la matriz dispersa
                generarGraficoRelacionesAmistad(listaRelaciones, listaUsuarios);
                generarReportePublicacionesGlobal(listaPublicacionesGlobal);
                system("pause");
                break;
            case 6:
                cout << "volviendo..." << endl;
                system("pause");
                break;
            default:
                cout << "Ingrese una opcion valida." << endl;
                system("pause");
                break;
        }
        system("cls");
    } while (opcion != 6);
}

//Se agregan los sub-menús del menú de perfil
void subMenuPerfil(ListaEnlazada& lista, const Usuario& usuarioConectado, MatrizDispersa& matrizAmigos, ListaDoblePublicaciones& listaPublicaciones){
    char opcion;
    do{
        cout << "\ta. Ver perfil" << endl;
        cout << "\tb. Eliminar Cuenta" << endl;
        cout << "\tc. Volver" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion){
        case 'a':
            cout << "---------Ver Perfil---------" << endl;
            mostrarInformacionUsuario(usuarioConectado);
            mostrarAmigos(matrizAmigos, usuarioConectado);
            mostrarPublicaciones(listaPublicaciones, usuarioConectado);
            system("pause");
            break;
        case 'b':
            cout << "---------Elimnar Cuenta---------" << endl;
            eliminarCuenta(lista, usuarioConectado);
            break;
        case 'c':
            cout<<"Saliendo del menu... "<<endl;
            break;
        default:
            cout<<"Ingrese una opcion valida... "<<endl;
            system("pause");
            break;
        }
    } while (opcion!='c');
    
}

//sub-menú de solicitudes
void subMenuSolicitudes(Usuario& usuarioConectado, ListaEnlazada& listaUsuarios, MatrizDispersa& matriz) {
    char opcion;
    do {
        cout << "\ta. Ver solicitudes" << endl;
        cout << "\tb. Enviar" << endl;
        cout << "\tc. Aceptar solicitud" << endl;
        cout << "\td. Rechazar solicitud" << endl;
        cout << "\te. Volver" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion) {
            case 'a':
                cout << "---------Ver Solicitudes---------" << endl;
                usuarioConectado.mostrarSolicitudesRecibidas();
                break;
            case 'b':
                {
                cout << "---------Enviar Solicitud---------" << endl;
                string correoReceptor;
                cout << "Ingrese el correo del receptor: ";
                cin >> correoReceptor;
                Usuario* receptor = listaUsuarios.buscarUsuarioPorCorreo(correoReceptor);
                if (receptor) {
                    // Verificar si el usuario conectado intenta enviarse una solicitud a sí mismo
                    if (usuarioConectado.getCorreo() == receptor->getCorreo()) {
                        cout << "No puedes enviarte una solicitud de amistad a ti mismo." << endl;
                    } else {
                        usuarioConectado.enviarSolicitud(usuarioConectado, *receptor);
                        cout << "Solicitud de amistad enviada con éxito." << endl;
                    }
                } else {
                    cout << "Usuario no encontrado." << endl;
                }
                system("pause");
                break;
            }
            case 'c':
                {
                cout << "---------Aceptar Solicitud---------" << endl;
                string correoEmisor;
                cout << "Ingrese el correo del emisor: ";
                cin >> correoEmisor;
                Usuario* emisor = listaUsuarios.buscarUsuarioPorCorreo(correoEmisor);
                if (emisor) {
                    usuarioConectado.aceptarSolicitud(&usuarioConectado, emisor, matriz);
                } else {
                    cout << "Usuario no encontrado." << endl;
                }
                system("pause");
                break;
            }
            case 'd':
                {
                cout << "---------Rechazar Solicitud---------" << endl;
                string correoEmisor;
                cout << "Ingrese el correo del emisor: ";
                cin >> correoEmisor;
                Usuario* emisor = listaUsuarios.buscarUsuarioPorCorreo(correoEmisor);
                if (emisor) {
                    usuarioConectado.rechazarSolicitud(&usuarioConectado, emisor);
                } else {
                    cout << "Usuario no encontrado." << endl;
                }
                system("pause");
                break;
            }
            case 'e':
                cout << "Saliendo del menu..." << endl;
                system("pause");
                break;
            default:
                cout << "Ingrese una opcion valida..." << endl;
                system("pause");
                break;
        }
    } while (opcion != 'e');
}

void crearPublicacion(Usuario& usuarioConectado, ListaDoblePublicaciones& listaPublicaciones, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal) {
    string contenido;
    cout << "Ingrese el contenido de la publicacion: "; //cin.ignore();
    getline(cin, contenido);

    // Crear una nueva publicación
    auto nuevaPublicacion = std::make_shared<Publicacion>(usuarioConectado.getCorreo(), contenido);

    // Agregar la publicación a la lista del usuario
    usuarioConectado.publicaciones.agregarPublicacion(nuevaPublicacion);

    // Agregar la publicación al feed de amigos
    // Supongamos que tienes una lista circular de publicaciones para el feed
    listaPublicaciones.agregarPublicacion(nuevaPublicacion);

    // Agregar la publicación a la lista global
    listaPublicacionesGlobal.agregarPublicacion(nuevaPublicacion);

    cout << "Publicacion creada exitosamente." << endl;
    //system("pause");
}

//sub-menú de publicaciones
void subMenuPublicaciones(Usuario& usuarioConectado, ListaDoblePublicaciones& listaPublicaciones, MatrizDispersa& matrizAmigos, ListaEnlazada& listaUsuarios, ListaDoblePublicacionesGlobal& listaPublicacionesGlobal){
    char opcion;
    do{
        cout << "\ta. Ver todas" << endl;
        cout << "\tb. Crear" << endl;
        cout << "\tc. Eliminar" << endl;
        cout << "\td. Volver" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion){
        case 'a':
            cout << "---------Ver Todas---------" << endl;
            
            // Limpiar la lista de publicaciones antes de agregar nuevas
            listaPublicaciones = ListaDoblePublicaciones(); // Reinicializar la lista

            if (usuarioConectado.publicaciones.estaVacia()) {
                cout << "No tienes publicaciones." << endl;
            } else {
                usuarioConectado.publicaciones.mostrarPublicaciones();
            }
            // Mostrar todas las publicaciones en la lista circular doblemente enlazada
            mostrarPublicacionesDeAmigos(usuarioConectado, listaPublicaciones, matrizAmigos, listaUsuarios);
            //listaPublicaciones.mostrarPublicaciones();
            //cout<<"esto es una prubea "<<endl;
            //usuarioConectado.mostrarPublicaciones();
            // Reiniciar la lista para empezar desde el principio
            listaPublicaciones.reiniciar();

            char opcion;
            do {
                cout << "Selecciona una opción: (s)iguiente, (a)nterior, (q)uit" << endl;
                cin >> opcion;

                switch (opcion) {
                    case 's':
                        listaPublicaciones.irSiguiente();
                        break;
                    case 'a':
                        listaPublicaciones.irAnterior();
                        break;
                    case 'q':
                        cout << "Saliendo del visualizador de publicaciones." << endl;
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                }
            } while (opcion != 'q');
            break;
        case 'b':
            cout << "---------Crear---------" << endl;
            crearPublicacion(usuarioConectado, listaPublicaciones, listaPublicacionesGlobal);
            break;
        case 'c':
            cout << "---------Eliminar---------" << endl;
            usuarioConectado.publicaciones.mostrarPublicaciones(); // Mostrar todas las publicaciones del usuario

            cout << "Ingrese el número de la publicación que desea eliminar: ";
            int indice;
            cin >> indice;

            // Verificamos que el índice sea válido
            if (indice > 0 && indice <= usuarioConectado.publicaciones.size()) {
                auto actual = usuarioConectado.publicaciones.obtenerCabeza();

                // Avanzamos hasta la publicación correspondiente al índice
                for (int i = 1; i < indice; ++i) {
                    if (actual) {
                        actual = actual->siguiente;
                    }
                }

                if (actual && usuarioConectado.publicaciones.eliminarPublicacion(actual->publicacion)) {
                    // Elimina la publicación de la lista global
                    if (listaPublicacionesGlobal.eliminarPublicacion(actual->publicacion)) {
                        cout << "Publicación eliminada con éxito." << endl;
                    } else {
                        cout << "No se pudo eliminar la publicación de la lista global." << endl;
                    }
                } else {
                    cout << "No se pudo eliminar la publicación." << endl;
                }
            } else {
                cout << "Índice no válido." << endl;
            }
            break;
        case 'd':
            cout<<"Saliendo del menu... "<<endl;
            system("pause");
            break;
        default:
            cout<<"Ingrese una opcion valida... "<<endl;
            system("pause");
            break;
        }
    } while (opcion!='d');
}

void eliminarCuenta(ListaEnlazada& lista, const Usuario& usuarioConectado) {
    cout << "¿Estas seguro de que deseas eliminar tu cuenta? Esta accion es irreversible. (si/no): ";
    string confirmacion; cin >> confirmacion;

    if (confirmacion == "si") {
        // Lógica para eliminar la cuenta del usuarioConectado
        bool eliminado = lista.eliminarUsuario(usuarioConectado.getCorreo());

        if (eliminado) {
            cout << "Cuenta de " << usuarioConectado.getNombre() << " eliminada exitosamente." << endl;
            // Aquí puedes agregar lógica para redirigir al menú principal
            return;
        } else {
            cout << "No se encontró la cuenta para eliminar." << endl;
        }

        // Redirigir al menú principal después de eliminar la cuenta
        return;
    } else {
        cout << "Cancelando eliminación de cuenta." << endl;
    }
}

void generarGraficoPilaSolicitudesRecibidas(const PilaSolicitudes& pilaSolicitudes) {
    ofstream archivo("pila_solicitudes_recibidas.dot");
    archivo << "digraph G {" << endl;
    archivo << "    rankdir=TB;" << endl; // Organiza de arriba hacia abajo (estilo de pila)
    archivo << "    node [shape=record];" << endl;

    auto nodoActual = pilaSolicitudes.tope; // Acceder al tope de la pila directamente
    int i = 0;

    while (nodoActual != nullptr) {
        archivo << "    nodo" << i << " [label=\"" << nodoActual->solicitud << "\"];" << endl;
        if (nodoActual->siguiente) {
            archivo << "    nodo" << i << " -> nodo" << i + 1 << ";" << endl;
        }
        nodoActual = nodoActual->siguiente;
        i++;
    }

    archivo << "}" << endl;
    archivo.close();

    // Generar la imagen a partir del archivo DOT
    system("dot -Tpng pila_solicitudes_recibidas.dot -o pila_solicitudes_recibidas.png");
}

void generarGraficoColaSolicitudesEnviadas(const ListaSimpleSolicitudes& listaSolicitudes) {
    ofstream archivo("cola_solicitudes_enviadas.dot");
    archivo << "digraph G {" << endl;
    archivo << "    rankdir=LR;" << endl; // Organiza de izquierda a derecha (estilo de cola)
    archivo << "    node [shape=record];" << endl;

    auto nodoActual = listaSolicitudes.obtenerCabeza(); // Método que te permite obtener la cabeza de la lista
    int i = 0;

    while (nodoActual != nullptr) {
        archivo << "    nodo" << i << " [label=\"" << nodoActual->solicitud << "\"];" << endl;
        if (nodoActual->siguiente) {
            archivo << "    nodo" << i << " -> nodo" << i + 1 << ";" << endl;
        }
        nodoActual = nodoActual->siguiente;
        i++;
    }

    archivo << "}" << endl;
    archivo.close();

    // Generar la imagen a partir del archivo DOT
    system("dot -Tpng cola_solicitudes_enviadas.dot -o cola_solicitudes_enviadas.png");
}

void mostrarListaAmigos(const Usuario& usuarioConectado, MatrizDispersa& matrizAmigos) {
    ListaEnlazadaAmigos listaAmigos;
    matrizAmigos.obtenerAmigos(usuarioConectado.getNombre(), listaAmigos);

    cout << "Lista de amigos de " << usuarioConectado.getNombre() << ":" << endl;
    listaAmigos.paraCadaAmigo([](const string& correo) {
        cout << "- " << correo << endl;
    });
}

void generarGraficoMatrizAmistades(const Usuario& usuarioConectado, MatrizDispersa& matriz, ListaEnlazada& listaUsuarios) {
    ofstream archivo("matriz_amistades.dot");
    archivo << "digraph G {" << endl;
    archivo << "    node [shape=record];" << endl;

    // Recorrer toda la matriz para mostrar las relaciones de amistad del usuario conectado
    matriz.paraCadaRelacionDelUsuario(usuarioConectado.getCorreo(), [&](const string& correoUsuario, const string& correoAmigo) {
        string nombreUsuario = listaUsuarios.buscarNombrePorCorreo(correoUsuario);
        string nombreAmigo = listaUsuarios.buscarNombrePorCorreo(correoAmigo);

        if (!nombreUsuario.empty() && !nombreAmigo.empty()) {
            archivo << "    \"" << nombreUsuario << "\" -> \"" << nombreAmigo << "\";" << endl;
            archivo << "    \"" << nombreAmigo << "\" -> \"" << nombreUsuario << "\";" << endl; // Flecha inversa
        }
    });

    archivo << "}" << endl;
    archivo.close();

    // Generar la imagen a partir del archivo DOT
    system("dot -Tpng matriz_amistades.dot -o matriz_amistades.png");
}

//lista circular
void generarGraficoListaDoble(const ListaDoblePublicaciones& lista) {
    ofstream archivo("lista_doble_publicaciones.dot");
    archivo << "digraph G {" << endl;
    archivo << "    node [shape=box];" << endl;
    archivo << "    rankdir=LR;" << endl;  // Orientación horizontal

    auto nodoActual = lista.obtenerCabeza();
    if (nodoActual) {
        auto nodoCabeza = nodoActual;  // Guardamos la cabeza para cerrar la lista circular
        auto nodoPrevio = nodoActual;  // Nodo previo para manejar el enlace hacia atrás

        do {
            // Crear el nodo con su etiqueta
            archivo << "    \"" << nodoActual << "\" [label=\"" << nodoActual->publicacion->getContenido() << "\"];" << endl;

            // Enlace hacia adelante (siguiente)
            if (nodoActual->siguiente) {
                archivo << "    \"" << nodoActual << "\" -> \"" << nodoActual->siguiente << "\" [dir=both];" << endl;
            }

            // Actualizar nodoPrevio antes de avanzar
            nodoPrevio = nodoActual;
            nodoActual = nodoActual->siguiente;
        } while (nodoActual && nodoActual != nodoCabeza);  // Terminar el ciclo al volver al nodoCabeza

        // Conectar el último nodo de vuelta al primero para cerrar el ciclo
        // Solo agregar una flecha bidireccional
        if (nodoPrevio && nodoCabeza) {
            archivo << "    \"" << nodoPrevio << "\" -> \"" << nodoCabeza << "\" [dir=both];" << endl;
        }
    }

    archivo << "}" << endl;
    archivo.close();

    // Generar la imagen a partir del archivo DOT
    system("dot -Tpng lista_doble_publicaciones.dot -o lista_doble_publicaciones.png");
}

void mostrarTop5UsuariosConMasPublicaciones(const ListaEnlazada& listaUsuarios, const ListaDoblePublicaciones& listaPublicaciones) {
    ListaEnlazadaSimpleMayorPublicaciones listaOrdenada;

    // Recorrer la lista de usuarios y contar las publicaciones
    listaUsuarios.paraCadaUsuario([&](Usuario* usuario) {
        int numeroPublicaciones = listaPublicaciones.contarPublicaciones(usuario->getCorreo());
        listaOrdenada.agregarUsuario(usuario->getCorreo(), numeroPublicaciones);
    });

    // Mostrar los 5 usuarios con más publicaciones
    listaOrdenada.mostrarTop5();
}

void mostrarTop5UsuariosConMenosAmigos(const ListaEnlazada& listaUsuarios, const MatrizDispersa& matriz) {
    ListaEnlazadaSimpleMenosAmigos listaOrdenada;

    // Recorrer la lista de usuarios y contar los amigos
    listaUsuarios.paraCadaUsuario([&](Usuario* usuario) {
        ListaEnlazadaAmigos amigosLista;
        matriz.obtenerAmigos(usuario->getCorreo(), amigosLista);
        int numeroAmigos = amigosLista.size();
        listaOrdenada.agregarUsuario(usuario->getCorreo(), numeroAmigos);
    });

    // Mostrar los 5 usuarios con menos amigos
    listaOrdenada.mostrarTop5();
}

void generarGraficoListaUsuarios(const ListaEnlazada& listaUsuarios) {
    // Abrir el archivo DOT para escritura
    std::ofstream archivoDOT("usuarios.dot");
    if (!archivoDOT.is_open()) {
        std::cerr << "No se pudo abrir el archivo DOT para escritura." << std::endl;
        return;
    }

    // Escribir el encabezado del archivo DOT
    archivoDOT << "digraph ListaUsuarios {\n";
    archivoDOT << "    rankdir=LR;\n"; // Direccionalidad de izquierda a derecha
    archivoDOT << "    node [shape=box];\n"; // Forma de los nodos

    // Usar una variable para rastrear el nodo anterior
    std::string idAnterior;

    listaUsuarios.paraCadaUsuario([&](Usuario* usuario) {
        std::ostringstream nodoID;
        nodoID << "usuario_" << sanearIdentificador(usuario->getCorreo());

        // Escribir el nodo para cada usuario
        archivoDOT << "    " << nodoID.str() << " [label=\"" << usuario->getNombre() << "\"];\n";

        // Conectar el nodo anterior al nodo actual
        if (!idAnterior.empty()) {
            archivoDOT << "    " << idAnterior << " -> " << nodoID.str() << ";\n";
        }

        // Actualizar idAnterior
        idAnterior = nodoID.str();
    });

    // Escribir el pie del archivo DOT
    archivoDOT << "}\n";

    archivoDOT.close();

    // Generar la imagen a partir del archivo DOT
    std::string comando = "dot -Tpng usuarios.dot -o usuarios.png";
    int resultado = std::system(comando.c_str());
    if (resultado != 0) {
        std::cerr << "Error al generar la imagen con Graphviz." << std::endl;
    } else {
        std::cout << "Imagen generada exitosamente como usuarios.png" << std::endl;
    }
}

string sanearIdentificador(const std::string& id) {
    // Reemplazar caracteres no válidos en los identificadores de nodos
    std::string idSaneado = id;
    std::regex caracteresNoValidos("[^a-zA-Z0-9_]"); // Solo caracteres alfanuméricos y guiones bajos
    idSaneado = std::regex_replace(idSaneado, caracteresNoValidos, "_");
    return idSaneado;
}

void generarReportePublicacionesGlobal(ListaDoblePublicacionesGlobal& listaPublicacionesGlobal) {
    listaPublicacionesGlobal.generarGrafico("grafico_publicaciones_global.dot");
}

void generarGraficoRelacionesAmistad(const ListaRelacionesCompleto& listaRelaciones, const ListaEnlazada& listaUsuarios) {
    std::ofstream archivoDOT("matriz_amistades.dot");
    if (!archivoDOT.is_open()) {
        std::cerr << "No se pudo abrir el archivo DOT para escritura." << std::endl;
        return;
    }

    archivoDOT << "digraph MatrizDispersa {\n";
    archivoDOT << "    node [shape=box];\n";
    archivoDOT << "    splines=true;\n"; // Para permitir curvas suaves en las flechas

    // Recorrer cada relación y escribir en el archivo DOT
    listaRelaciones.paraCadaRelacion([&](const Relacion& relacion) {
        // Obtener los nombres de los usuarios a partir de sus correos
        std::string nombre1 = listaUsuarios.buscarNombrePorCorreo(relacion.usuario1);
        std::string nombre2 = listaUsuarios.buscarNombrePorCorreo(relacion.usuario2);

        // Si alguno de los nombres está vacío, se puede registrar una advertencia o manejar el error
        if (nombre1.empty()) nombre1 = "[Desconocido]";
        if (nombre2.empty()) nombre2 = "[Desconocido]";

        // Escribir la relación en el archivo DOT
        archivoDOT << "    \"" << nombre1 << "\" -> \"" << nombre2 << "\" [label=\"\"];\n";
        archivoDOT << "    \"" << nombre2 << "\" -> \"" << nombre1 << "\" [label=\"\"];\n";
    });

    archivoDOT << "}\n";
    archivoDOT.close();

    // Generar la imagen a partir del archivo DOT
    int resultado = system("dot -Tpng matriz_amistades.dot -o matriz_amistades.png");
    if (resultado != 0) {
        std::cerr << "Error al generar la imagen con Graphviz." << std::endl;
    } else {
        std::cout << "Imagen generada exitosamente como matriz_amistades.png" << std::endl;
    }
}

