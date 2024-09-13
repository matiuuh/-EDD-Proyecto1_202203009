#include "avlusuarios.h"
#include <windows.h>
#include <algorithm>

// Inicialización de la instancia estática
AVLUsuarios* AVLUsuarios::instance = nullptr;

// Constructor de NodoAVL
NodoAVL::NodoAVL(Usuario* user)
    : usuario(user), izquierda(nullptr), derecha(nullptr), altura(1) {
    std::cout << "NodoAVL creado con usuario: " << user->getCorreo() << std::endl;
}

// Constructor de AVLUsuarios
AVLUsuarios::AVLUsuarios() : raiz(nullptr) {}

// Destructor de AVLUsuarios
AVLUsuarios::~AVLUsuarios() {
    // Aquí se debería liberar la memoria, si es necesario
}

// Obtener la instancia única del Singleton
AVLUsuarios& AVLUsuarios::getInstance() {
    static AVLUsuarios instance;  // Instancia local estática, segura para hilos
    return instance;
}

// Implementaciones de métodos de AVLUsuarios
void AVLUsuarios::insertar(Usuario* usuario) {
    std::cout << "Insertando usuario con correo: " << usuario->getCorreo() << std::endl;
    raiz = insertarRecursivo(raiz, usuario);
}

Usuario* AVLUsuarios::buscar(const std::string& correo) {
    NodoAVL* resultado = buscarRecursivo(raiz, correo);
    if (resultado) {
        return resultado->usuario;
    }
    return nullptr;
}

void AVLUsuarios::mostrarUsuarios() const {
    mostrarRecursivo(raiz);
}

int AVLUsuarios::altura(NodoAVL* nodo) {
    return nodo ? nodo->altura : 0;
}

NodoAVL* AVLUsuarios::rotacionDerecha(NodoAVL* y) {
    std::cout << "Realizando rotación derecha sobre: " << y->usuario->getCorreo() << std::endl;
    NodoAVL* x = y->izquierda;
    NodoAVL* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = std::max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = std::max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

NodoAVL* AVLUsuarios::rotacionIzquierda(NodoAVL* x) {
    std::cout << "Realizando rotación izquierda sobre: " << x->usuario->getCorreo() << std::endl;
    NodoAVL* y = x->derecha;
    NodoAVL* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = std::max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = std::max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}


int AVLUsuarios::obtenerBalance(NodoAVL* nodo) {
    return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
}

NodoAVL* AVLUsuarios::insertarRecursivo(NodoAVL* nodo, Usuario* usuario) {
    if (!nodo) {
        std::cout << "Creando nuevo nodo para el usuario: " << usuario->getCorreo() << std::endl;
        return new NodoAVL(usuario);
    }

    if (usuario->getCorreo() < nodo->usuario->getCorreo()) {
        std::cout << "Insertando en el lado izquierdo de: " << nodo->usuario->getCorreo() << std::endl;
        nodo->izquierda = insertarRecursivo(nodo->izquierda, usuario);
    } else if (usuario->getCorreo() > nodo->usuario->getCorreo()) {
        std::cout << "Insertando en el lado derecho de: " << nodo->usuario->getCorreo() << std::endl;
        nodo->derecha = insertarRecursivo(nodo->derecha, usuario);
    } else {
        std::cout << "El usuario con correo " << usuario->getCorreo() << " ya existe." << std::endl;
        return nodo;  // Correo ya existe
    }

    nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));

    int balance = obtenerBalance(nodo);
    std::cout << "Balance del nodo " << nodo->usuario->getCorreo() << ": " << balance << std::endl;

    // Verificar y aplicar rotaciones
    if (balance > 1 && usuario->getCorreo() < nodo->izquierda->usuario->getCorreo()) {
        std::cout << "Rotación derecha sobre: " << nodo->usuario->getCorreo() << std::endl;
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && usuario->getCorreo() > nodo->derecha->usuario->getCorreo()) {
        std::cout << "Rotación izquierda sobre: " << nodo->usuario->getCorreo() << std::endl;
        return rotacionIzquierda(nodo);
    }

    if (balance > 1 && usuario->getCorreo() > nodo->izquierda->usuario->getCorreo()) {
        std::cout << "Rotación izquierda-derecha sobre: " << nodo->usuario->getCorreo() << std::endl;
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && usuario->getCorreo() < nodo->derecha->usuario->getCorreo()) {
        std::cout << "Rotación derecha-izquierda sobre: " << nodo->usuario->getCorreo() << std::endl;
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

NodoAVL* AVLUsuarios::buscarRecursivo(NodoAVL* nodo, const std::string& correo) const {
    if (!nodo) {
        std::cout << "No se encontró el nodo con correo: " << correo << std::endl;
        return nullptr;
    }

    if (nodo->usuario->getCorreo() == correo) {
        std::cout << "Nodo encontrado: " << correo << std::endl;
        return nodo;
    }

    if (correo < nodo->usuario->getCorreo()) {
        std::cout << "Buscando en el lado izquierdo de: " << nodo->usuario->getCorreo() << std::endl;
        return buscarRecursivo(nodo->izquierda, correo);
    }

    std::cout << "Buscando en el lado derecho de: " << nodo->usuario->getCorreo() << std::endl;
    return buscarRecursivo(nodo->derecha, correo);
}


void AVLUsuarios::mostrarRecursivo(NodoAVL* nodo) const {
    if (nodo) {
        mostrarRecursivo(nodo->izquierda);
        std::cout << "Mostrando usuario: " << nodo->usuario->getNombre() << " - " << nodo->usuario->getCorreo() << std::endl;
        mostrarRecursivo(nodo->derecha);
    }
}

