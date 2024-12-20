#ifndef AVLUSUARIOS_H
#define AVLUSUARIOS_H

#include <iostream>
#include <string>
#include "../usuario.h"
#include "../EstructurasUsuario/listadobleusuariosdisponibles.h"

class NodoAVL {
public:
    Usuario* usuario;
    NodoAVL* izquierda;
    NodoAVL* derecha;
    int altura;

    NodoAVL(Usuario* user);
};

class AVLUsuarios {
public:
    static AVLUsuarios& getInstance();  // Método estático para obtener la instancia única

    void insertar(Usuario* usuario);
    Usuario* buscar(const std::string& correo);
    void mostrarUsuarios() const;
    bool validarCredenciales(const std::string& correo, const std::string& contrasenia);
    void obtenerUsuariosDisponibles(ListaDobleUsuariosDisponibles& lista, const std::string& correoConectado);
    void obtenerUsuariosRecursivo(NodoAVL* nodo, ListaDobleUsuariosDisponibles& lista, const std::string& correoConectado);
    void obtenerTodosLosUsuarios(ListaDobleUsuariosDisponibles& lista);
    void obtenerTodosLosUsuariosRecursivo(NodoAVL* nodo, ListaDobleUsuariosDisponibles& lista);
    void obtenerUsuariosPreOrden(ListaDobleUsuariosDisponibles& lista);
    void obtenerUsuariosPreOrdenRecursivo(NodoAVL* nodo, ListaDobleUsuariosDisponibles& lista);
    void obtenerUsuariosInOrden(ListaDobleUsuariosDisponibles& lista);
    void obtenerUsuariosPostOrden(ListaDobleUsuariosDisponibles& lista);
    void obtenerUsuariosPostOrdenRecursivo(NodoAVL* nodo, ListaDobleUsuariosDisponibles& lista);
    void modificarUsuario(Usuario* usuarioConectado, const std::string& nuevoNombre, const std::string& nuevoApellido, const std::string& nuevoCorreo, const std::string& nuevaContrasenia, const std::string& nuevaFecha);

    //Para eliminar
    void eliminar(const std::string& correo);

    void graph();
    void graph(NodoAVL *root, std::ofstream &content);

private:
    AVLUsuarios();  // Constructor privado para evitar instanciación externa
    ~AVLUsuarios(); // Destructor privado

    NodoAVL* raiz;

    int altura(NodoAVL* nodo);
    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    int obtenerBalance(NodoAVL* nodo);
    NodoAVL* insertarRecursivo(NodoAVL* nodo, Usuario* usuario);
    NodoAVL* buscarRecursivo(NodoAVL* nodo, const std::string& correo) const;
    void mostrarRecursivo(NodoAVL* nodo) const;

    //Para eliminar
    NodoAVL* eliminarRecursivo(NodoAVL* nodo, const std::string& correo);
    NodoAVL* encontrarMinimo(NodoAVL* nodo);
    void liberarMemoria(NodoAVL* nodo);

    static AVLUsuarios* instance;  // Instancia única del Singleton
};

#endif // AVLUSUARIOS_H
