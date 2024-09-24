#include "avlusuarios.h"
//#include <windows.h>
#include <algorithm>
//#include "../EstructurasUsuario/listadobleusuariosdisponibles.h"

#include <fstream>  // Para std::ofstream
#include <cstdlib>  // Para system() y comandos externos
#include <iostream>  // Para std::cout


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

//-----------------PARA OBTENER LA INSTANCIA GLOBAL-----------
AVLUsuarios& AVLUsuarios::getInstance() {
    static AVLUsuarios instance;  // Instancia local estática, segura para hilos
    return instance;
}

//-----------------PARA AGREGAR USUARIOS AL SISTEMA-----------
void AVLUsuarios::insertar(Usuario* usuario) {
    std::cout << "Insertando usuario con correo: " << usuario->getCorreo() << std::endl;
    raiz = insertarRecursivo(raiz, usuario);
}
//----------------BUSCAR USUARIO POR CORREO-------------------
Usuario* AVLUsuarios::buscar(const std::string& correo) {
    NodoAVL* resultado = buscarRecursivo(raiz, correo);
    if (resultado) {
        return resultado->usuario;
    }
    return nullptr;
}

//--------------------MOSTRAR USUARIOS--------------------------
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

//---------------VALIDA CREDENCIALES DEL USUARIO--------------------
// Nuevo método para validar las credenciales del usuario
bool AVLUsuarios::validarCredenciales(const std::string& correo, const std::string& contrasenia) {
    // Buscar el nodo del usuario por correo
    Usuario* usuarioEncontrado = buscar(correo);

    if (usuarioEncontrado) {
        // Verificar si la contraseña coincide
        if (usuarioEncontrado->getContrasenia() == contrasenia) {
            return true;  // Credenciales válidas
        } else {
            std::cout << "Contraseña incorrecta para el correo: " << correo << std::endl;
            return false;  // Contraseña incorrecta
        }
    }
    std::cout << "Usuario no encontrado con el correo: " << correo << std::endl;
    return false;  // Usuario no encontrado
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

//-------------------------MÉTODOS PARA OBTENER LA TABLA DE USUARIOS-----------------------
void AVLUsuarios::obtenerUsuariosDisponibles(ListaDobleUsuariosDisponibles& lista, const std::string& correoConectado) {
    obtenerUsuariosRecursivo(raiz, lista, correoConectado);
}

void AVLUsuarios::obtenerUsuariosRecursivo(NodoAVL* nodo, ListaDobleUsuariosDisponibles& lista, const std::string& correoConectado) {
    if (!nodo) return;

    // Recorrer los nodos en orden (izquierda, raíz, derecha)
    obtenerUsuariosRecursivo(nodo->izquierda, lista, correoConectado);

    // Si el correo del nodo no es el del usuario conectado, lo agregamos a la lista
    if (nodo->usuario->getCorreo() != correoConectado) {
        lista.agregarUsuario(nodo->usuario->getNombre(),
                             nodo->usuario->getApellidos(),
                             nodo->usuario->getCorreo(),
                             nodo->usuario->getFecha());
    }

    obtenerUsuariosRecursivo(nodo->derecha, lista, correoConectado);
}

//*********************************MODULO ADMINISTRADOR*************************************
//--------------------OBTENER USUARIOS MODULO ADMINISTRADOR-----------------------------
void AVLUsuarios::obtenerTodosLosUsuarios(ListaDobleUsuariosDisponibles& lista) {
    obtenerTodosLosUsuariosRecursivo(raiz, lista);
}

void AVLUsuarios::obtenerTodosLosUsuariosRecursivo(NodoAVL* nodo, ListaDobleUsuariosDisponibles& lista) {
    if (!nodo) return;

    // Recorrer los nodos en orden (izquierda, raíz, derecha)
    obtenerTodosLosUsuariosRecursivo(nodo->izquierda, lista);

    // Agregar el correo del usuario al listado
    lista.agregarUsuario(nodo->usuario->getNombre(),
                         nodo->usuario->getApellidos(),
                         nodo->usuario->getCorreo(),
                         nodo->usuario->getFecha());

    obtenerTodosLosUsuariosRecursivo(nodo->derecha, lista);
}

//------------------------------RECORRIDOS EN ORDEN----------------------------------
// Recorrido Pre-Orden
void AVLUsuarios::obtenerUsuariosPreOrden(ListaDobleUsuariosDisponibles& lista) {
    obtenerUsuariosPreOrdenRecursivo(raiz, lista);
}

void AVLUsuarios::obtenerUsuariosPreOrdenRecursivo(NodoAVL* nodo, ListaDobleUsuariosDisponibles& lista) {
    if (!nodo) return;

    // Primero el nodo raíz: agregar el usuario completo
    lista.agregarUsuario(nodo->usuario->getNombre(),
                         nodo->usuario->getApellidos(),
                         nodo->usuario->getCorreo(),
                         nodo->usuario->getFecha());

    // Luego recorrer izquierda y derecha
    obtenerUsuariosPreOrdenRecursivo(nodo->izquierda, lista);
    obtenerUsuariosPreOrdenRecursivo(nodo->derecha, lista);
}

// Recorrido In-Orden (ya implementado)
void AVLUsuarios::obtenerUsuariosInOrden(ListaDobleUsuariosDisponibles& lista) {
    obtenerTodosLosUsuariosRecursivo(raiz, lista);  // Este ya lo tienes como "obtenerTodosLosUsuarios"
}

// Recorrido Post-Orden
void AVLUsuarios::obtenerUsuariosPostOrden(ListaDobleUsuariosDisponibles& lista) {
    obtenerUsuariosPostOrdenRecursivo(raiz, lista);
}

void AVLUsuarios::obtenerUsuariosPostOrdenRecursivo(NodoAVL* nodo, ListaDobleUsuariosDisponibles& lista) {
    if (!nodo) return;

    // Primero recorrer izquierda y derecha
    obtenerUsuariosPostOrdenRecursivo(nodo->izquierda, lista);
    obtenerUsuariosPostOrdenRecursivo(nodo->derecha, lista);

    // Luego el nodo raíz
    lista.agregarUsuario(nodo->usuario->getNombre(),
                         nodo->usuario->getApellidos(),
                         nodo->usuario->getCorreo(),
                         nodo->usuario->getFecha());
}

//*******************************MODIFICAR DATOS DEL USUARIO*******************************
// Método para modificar la información de un usuario
void AVLUsuarios::modificarUsuario(Usuario* usuarioConectado, const std::string& nuevoNombre, const std::string& nuevoApellido, const std::string& nuevoCorreo, const std::string& nuevaContrasenia, const std::string& nuevaFecha) {
    // Verificar si el nombre no está vacío y modificarlo
    if (!nuevoNombre.empty()) {
        usuarioConectado->setNombre(nuevoNombre);
    }

    // Verificar si el apellido no está vacío y modificarlo
    if (!nuevoApellido.empty()) {
        usuarioConectado->setApellidos(nuevoApellido);
    }

    // Verificar si el correo no está vacío y modificarlo
    if (!nuevoCorreo.empty()) {
        usuarioConectado->setCorreo(nuevoCorreo);
    }

    // Verificar si la contraseña no está vacía y modificarla
    if (!nuevaContrasenia.empty()) {
        usuarioConectado->setContrasenia(nuevaContrasenia);
    }

    // Verificar si la fecha no está vacía y modificarla
    if (!nuevaFecha.empty()) {
        usuarioConectado->setFechaNacimiento(nuevaFecha);
    }

    // Imprimir mensaje para confirmar cambios
    std::cout << "Datos del usuario modificados exitosamente." << std::endl;
}

void AVLUsuarios::eliminar(const std::string& correo) {
    raiz = eliminarRecursivo(raiz, correo);
}

NodoAVL* AVLUsuarios::eliminarRecursivo(NodoAVL* nodo, const std::string& correo) {
    if (!nodo) return nodo;

    if (correo < nodo->usuario->getCorreo()) {
        nodo->izquierda = eliminarRecursivo(nodo->izquierda, correo);
    } else if (correo > nodo->usuario->getCorreo()) {
        nodo->derecha = eliminarRecursivo(nodo->derecha, correo);
    } else {
        // Nodo con solo un hijo o sin hijos
        if (!nodo->izquierda) {
            NodoAVL* temp = nodo->derecha;
            delete nodo;
            return temp;
        } else if (!nodo->derecha) {
            NodoAVL* temp = nodo->izquierda;
            delete nodo;
            return temp;
        }

        // Nodo con dos hijos
        NodoAVL* temp = encontrarMinimo(nodo->derecha);
        nodo->usuario = temp->usuario;
        nodo->derecha = eliminarRecursivo(nodo->derecha, temp->usuario->getCorreo());
    }

    // Actualizar altura y balance
    nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
    int balance = obtenerBalance(nodo);

    // Rotaciones para mantener el balance del árbol
    if (balance > 1 && obtenerBalance(nodo->izquierda) >= 0) {
        return rotacionDerecha(nodo);
    }

    if (balance > 1 && obtenerBalance(nodo->izquierda) < 0) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && obtenerBalance(nodo->derecha) <= 0) {
        return rotacionIzquierda(nodo);
    }

    if (balance < -1 && obtenerBalance(nodo->derecha) > 0) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

NodoAVL* AVLUsuarios::encontrarMinimo(NodoAVL* nodo) {
    while (nodo && nodo->izquierda) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

void AVLUsuarios::liberarMemoria(NodoAVL* nodo) {
    if (nodo) {
        liberarMemoria(nodo->izquierda);
        liberarMemoria(nodo->derecha);
        delete nodo;
    }
}

//******************************REPORTES ADMINISTRADOR***************************************
//---------------------------GENERAR EL ARBOL DE USUARIO (AVL)---------------------------
void AVLUsuarios::graph() {
    std::ofstream outfile("C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\avl_usuarios.dot");
    outfile << "digraph G {" << std::endl;

    if (raiz != nullptr) {
        graph(raiz, outfile);
    }

    outfile << "}" << std::endl;
    outfile.close();
    int returnCode = system("dot -Tpng \"C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\avl_usuarios.dot\" -o \"C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\avl_usuarios.png\"");

    if (returnCode == 0) {
        std::cout << "Graph generated successfully." << std::endl;
    } else {
        std::cout << "Graph generation failed with return code: " << returnCode << std::endl;
    }
}

void AVLUsuarios::graph(NodoAVL *root, std::ofstream &content) {
    if (root != nullptr) {
        content << "Nodo" << root << "[label = \"" << root->usuario->getCorreo() << "\"];" << std::endl;

        if (root->izquierda != nullptr) {
            content << "Nodo" << root << "->Nodo" << root->izquierda << ";" << std::endl;
        }

        if (root->derecha != nullptr) {
            content << "Nodo" << root << "->Nodo" << root->derecha << ";" << std::endl;
        }

        graph(root->izquierda, content);
        graph(root->derecha, content);
    }
}

//---------------------------GENERAR GRAFICO LISTA PUBLICACIONES---------------------------
