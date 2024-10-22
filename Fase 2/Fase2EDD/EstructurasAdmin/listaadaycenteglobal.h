#ifndef LISTAADYACENTEGLOBAL_H
#define LISTAADYACENTEGLOBAL_H

#include "../usuario.h"  // Para usar la clase Usuario
#include <iostream>

// Nodo para la lista de amigos de cada usuario
struct NodoAmigoo {
    Usuario* amigo;
    NodoAmigoo* siguiente;

    NodoAmigoo(Usuario* _amigo) : amigo(_amigo), siguiente(nullptr) {}
};

// Nodo para la lista de usuarios en la lista adyacente global
struct NodoUsuarioo {
    Usuario* usuario;
    NodoAmigoo* listaAmigos;  // Lista enlazada de amigos de este usuario
    NodoUsuarioo* siguiente;  // Siguiente usuario en la lista global

    NodoUsuarioo(Usuario* _usuario) : usuario(_usuario), listaAmigos(nullptr), siguiente(nullptr) {}
};

// Estructura para almacenar una sugerencia de amistad y la cantidad de amigos en común
struct Sugerencia {
    Usuario* usuario;
    int amigosEnComun;

    Sugerencia(Usuario* _usuario, int _amigosEnComun) : usuario(_usuario), amigosEnComun(_amigosEnComun) {}
};

// Clase para manejar la lista de adyacencia global
class ListaAdyacenteGlobal {
private:
    NodoUsuarioo* cabeza;  // Apunta al primer usuario en la lista global
    static ListaAdyacenteGlobal* instance;  // Instancia única del Singleton

public:
    // Constructor
    ListaAdyacenteGlobal();

    // Destructor para limpiar la memoria
    ~ListaAdyacenteGlobal();

    // Método para agregar un nuevo usuario a la lista global
    void agregarUsuario(Usuario* nuevoUsuario);

    // Método para agregar una relación de amistad entre dos usuarios
    void agregarRelacion(Usuario* usuario1, Usuario* usuario2);

    // Método para buscar un usuario en la lista global
    NodoUsuarioo* buscarUsuario(Usuario* usuario);

    // Método para verificar si una relación ya existe entre dos usuarios
    bool existeRelacion(NodoUsuarioo* nodoUsuario, Usuario* posibleAmigo);

    // Método para graficar la lista de amigos del usuario conectado (opcional)
    void graficarListaAdyacencia(Usuario* usuarioConectado);

    //Método para verificar las amistades de la lista adyacente
    void mostrarListaAdyacente();

    //Método para obtener los amigos de un usuario en específico
    std::vector<Usuario*> obtenerAmigos(Usuario* usuario);

    std::vector<Usuario*> obtenerSugerenciasAmistad(Usuario* usuarioConectado);

    std::vector<Sugerencia> obtenerSugerenciasConAmigosEnComun(Usuario* usuarioConectado);

    void graficarListaAdyacente(const std::string& correoUsuario);

    static ListaAdyacenteGlobal& getInstance();
};

#endif // LISTAADYACENTEGLOBAL_H
