#ifndef AVLUSUARIOS_H
#define AVLUSUARIOS_H

#include <iostream>
#include <string>
#include "../usuario.h"

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

    static AVLUsuarios* instance;  // Instancia única del Singleton
};

#endif // AVLUSUARIOS_H
