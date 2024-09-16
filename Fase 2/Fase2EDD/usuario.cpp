#include "usuario.h"
#include <iostream>
//#include "/EstructurasAdmin/avlusuarios.h"

using namespace std;

// Constructor
Usuario::Usuario(const std::string& nombre, const std::string& apellidos, const std::string& fechaNacimiento, const std::string& correo, const std::string& contrasenia)
    : nombre(nombre), apellidos(apellidos), fechaNacimiento(fechaNacimiento), correo(correo), contrasenia(contrasenia) {}


// Mostrar todas las publicaciones propias
void Usuario::mostrarPublicaciones() {
    cout << "Mostrando publicaciones de: " << nombre << endl;
    publicacionesPropias.mostrar();
}

/*
// Buscar publicaciones por fecha en el BST de publicaciones de amigos
void Usuario::buscarPublicacionesPorFecha(const std::string& fecha) {
    cout << "Buscando publicaciones en la fecha: " << fecha << endl;
    publicacionesAmigos.buscarPorFecha(fecha);
}*/

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

// Método en Usuario para verificar si hay una solicitud pendiente del usuario destino
bool Usuario::existeSolicitudPendiente(const Usuario& usuarioDestino) {
    // Verificar si la pila de solicitudes recibidas contiene una solicitud del usuario destino
    return solicitudesRecibidas.buscarPorCorreo(usuarioDestino.getCorreo());
}

ListaDoble& Usuario::getListaPublicacionesPropias() {
    return publicacionesPropias;
}

BSTPublicaciones& Usuario::getBSTPublicacionesAmigos() {
    return publicacionesAmigos;
}
