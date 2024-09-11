#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "ListaDoblePublicaciones.cpp"
#include "PilaSolicitudes.cpp"
#include "ListaSimpleSolicitudes.cpp"
#include "MatrizDispersa.cpp"
#include "ListaEnlazada.cpp"
//#include "Nodo.cpp"

using namespace std;

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
