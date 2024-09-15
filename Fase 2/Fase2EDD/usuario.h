#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "pila.h"
#include "listasimple.h"
#include "listadoble.h"
#include "bstpublicaciones.h"

class Usuario {
public:
    Usuario(const std::string& nombre, const std::string& apellidos, const std::string& fechaNacimiento, const std::string& correo, const std::string& contrasenia);

    // Métodos para interactuar con las estructuras de datos
    void recibirSolicitud(const std::string& remitente);
    void enviarSolicitud(const std::string& destinatario);
    void agregarPublicacion(const std::string& contenido, const std::string& fecha, const std::string& hora);
    void mostrarPublicaciones();
    void buscarPublicacionesPorFecha(const std::string& fecha);
    bool existeSolicitudPendiente(const Usuario& usuarioDestino);

    // Datos del usuario
    std::string getNombre() const;
    std::string getCorreo() const;
    std::string getContrasenia() const;

    Pila& getPilaSolicitudes() { return solicitudesRecibidas; }
    ListaSimple& getListaSolicitudesEnviadas() { return solicitudesEnviadas; }


private:
    std::string nombre;
    std::string apellidos;
    std::string fechaNacimiento;
    std::string correo;
    std::string contrasenia;

    // Estructuras de datos asociadas
    Pila solicitudesRecibidas;                 // Pila de solicitudes recibidas
    ListaSimple solicitudesEnviadas;           // Lista simple para solicitudes enviadas
    ListaDoble publicacionesPropias;           // Lista doble para publicaciones propias
    BSTPublicaciones publicacionesAmigos;      // Árbol binario de búsqueda para publicaciones de amigos
};

#endif // USUARIO_H
