#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "pila.h"
#include "listasimple.h"
#include "listadoble.h"
#include "bstpublicaciones.h"
#include "EstructurasUsuario/matrizdispersaamigos.h"

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
    std::string getFecha() const;
    std::string getApellidos() const;

    //Setters
    void setContrasenia(const std::string& nuevaContrasenia);
    void setNombre(const std::string& nuevoNombre);
    void setApellidos(const std::string& nuevosApellidos);
    void setCorreo(const std::string& nuevoCorreo);
    void setFechaNacimiento(const std::string& nuevaFecha);

    Pila& getPilaSolicitudes() { return solicitudesRecibidas; }
    ListaSimple& getListaSolicitudesEnviadas() { return solicitudesEnviadas; }
    MatrizDispersaAmigos& getMatrizAmigos() { return matrizAmigos; }  // Método para obtener la matriz dispersa de amigos

    ListaDoble& getListaPublicacionesPropias();
    BSTPublicaciones& getBSTPublicacionesAmigos();


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
    MatrizDispersaAmigos matrizAmigos;          // Matriz dispersa para amistades
};

#endif // USUARIO_H
