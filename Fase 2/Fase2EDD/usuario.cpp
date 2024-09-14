#include "usuario.h"
#include <iostream>
//#include "/EstructurasAdmin/avlusuarios.h"

using namespace std;

// Constructor
Usuario::Usuario(const std::string& nombre, const std::string& apellidos, const std::string& fechaNacimiento, const std::string& correo, const std::string& contrasenia)
    : nombre(nombre), apellidos(apellidos), fechaNacimiento(fechaNacimiento), correo(correo), contrasenia(contrasenia) {}

// Métodos para interactuar con las estructuras de datos

// Recibir una solicitud de amistad
void Usuario::recibirSolicitud(const std::string& remitente) {
    solicitudesRecibidas.push(correo, remitente);
    cout << "Solicitud de amistad recibida de: " << remitente << endl;
}

// Enviar una solicitud de amistad
void Usuario::enviarSolicitud(const std::string& destinatario) {
    solicitudesEnviadas.agregar(nombre, correo);
    cout << "Solicitud de amistad enviada a: " << destinatario << endl;
}
/*
// Agregar una publicación propia
void Usuario::agregarPublicacion(const std::string& contenido, const std::string& fecha, const std::string& hora) {
    Publicacion nuevaPublicacion(correo, contenido, fecha, hora);
    publicacionesPropias.agregar(nuevaPublicacion);
    cout << "Publicación agregada: " << contenido << " en fecha: " << fecha << " a las: " << hora << endl;
}*/

// Mostrar todas las publicaciones propias
void Usuario::mostrarPublicaciones() {
    cout << "Mostrando publicaciones de: " << nombre << endl;
    publicacionesPropias.mostrar();
}

// Buscar publicaciones por fecha en el BST de publicaciones de amigos
void Usuario::buscarPublicacionesPorFecha(const std::string& fecha) {
    cout << "Buscando publicaciones en la fecha: " << fecha << endl;
    publicacionesAmigos.buscarPorFecha(fecha);
}

// Obtener el nombre del usuario
std::string Usuario::getNombre() const {
    return nombre;
}

// Obtener el correo del usuario
std::string Usuario::getCorreo() const {
    return correo;
}

// Obtener el correo del usuario
std::string Usuario::getContrasenia() const {
    return contrasenia;
}


//----------PARA OBTENER ESTRUCTURAS DE SOLICITUDES-----------------
