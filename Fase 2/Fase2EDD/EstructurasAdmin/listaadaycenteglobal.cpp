#include "listaadaycenteglobal.h"
#include <vector>  // Para utilizar el vector
#include <fstream>
#include "avlusuarios.h"


// Constructor: Inicializa la lista vacía
ListaAdyacenteGlobal::ListaAdyacenteGlobal() : cabeza(nullptr) {}

// Destructor: Limpia la memoria usada por los nodos de la lista
ListaAdyacenteGlobal::~ListaAdyacenteGlobal() {
    NodoUsuarioo* actual = cabeza;
    while (actual) {
        NodoAmigoo* actualAmigo = actual->listaAmigos;
        // Eliminar la lista de amigos de cada usuario
        while (actualAmigo) {
            NodoAmigoo* tempAmigo = actualAmigo;
            actualAmigo = actualAmigo->siguiente;
            delete tempAmigo;
        }
        // Eliminar el nodo de usuario
        NodoUsuarioo* tempUsuario = actual;
        actual = actual->siguiente;
        delete tempUsuario;
    }
}

// Agregar un usuario a la lista global
void ListaAdyacenteGlobal::agregarUsuario(Usuario* nuevoUsuario) {
    NodoUsuarioo* nuevoNodo = new NodoUsuarioo(nuevoUsuario);
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        NodoUsuarioo* temp = cabeza;
        // Insertar el nuevo nodo al final de la lista de usuarios
        while (temp->siguiente) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

// Agregar una relación de amistad entre dos usuarios
void ListaAdyacenteGlobal::agregarRelacion(Usuario* usuario1, Usuario* usuario2) {
    NodoUsuarioo* nodoUsuario1 = buscarUsuario(usuario1);
    NodoUsuarioo* nodoUsuario2 = buscarUsuario(usuario2);

    if (!nodoUsuario1 || !nodoUsuario2) {
        std::cout << "Uno de los usuarios no existe en la lista global." << std::endl;
        return;
    }

    // Verificar que la relación no exista ya
    if (!existeRelacion(nodoUsuario1, usuario2)) {
        // Agregar a usuario2 como amigo de usuario1
        NodoAmigoo* nuevoAmigo1 = new NodoAmigoo(usuario2);
        nuevoAmigo1->siguiente = nodoUsuario1->listaAmigos;
        nodoUsuario1->listaAmigos = nuevoAmigo1;

        // Agregar a usuario1 como amigo de usuario2
        NodoAmigoo* nuevoAmigo2 = new NodoAmigoo(usuario1);
        nuevoAmigo2->siguiente = nodoUsuario2->listaAmigos;
        nodoUsuario2->listaAmigos = nuevoAmigo2;

        std::cout << "Relación de amistad agregada entre " << usuario1->getCorreo() << " y " << usuario2->getCorreo() << std::endl;
    } else {
        std::cout << "La relación ya existe entre los usuarios." << std::endl;
    }
}

// Buscar un usuario en la lista global
NodoUsuarioo* ListaAdyacenteGlobal::buscarUsuario(Usuario* usuario) {
    NodoUsuarioo* temp = cabeza;
    while (temp) {
        if (temp->usuario == usuario) {
            return temp;
        }
        temp = temp->siguiente;
    }
    return nullptr;  // No se encontró el usuario
}

// Verificar si ya existe una relación de amistad entre dos usuarios
bool ListaAdyacenteGlobal::existeRelacion(NodoUsuarioo* nodoUsuario, Usuario* posibleAmigo) {
    NodoAmigoo* temp = nodoUsuario->listaAmigos;
    while (temp) {
        if (temp->amigo == posibleAmigo) {
            return true;  // Ya son amigos
        }
        temp = temp->siguiente;
    }
    return false;  // No son amigos
}

//-----------------PARA OBTENER LA INSTANCIA GLOBAL-----------
ListaAdyacenteGlobal& ListaAdyacenteGlobal::getInstance() {
    static ListaAdyacenteGlobal instanciaGlobal;  // Instancia local estática, segura para hilos
    return instanciaGlobal;
}

// Método para mostrar el contenido de la lista adyacente y las relaciones de cada usuario
void ListaAdyacenteGlobal::mostrarListaAdyacente() {
    if (!cabeza) {
        std::cout << "La lista adyacente está vacía." << std::endl;
        return;
    }

    NodoUsuarioo* actualUsuario = cabeza;

    // Recorrer cada usuario en la lista
    while (actualUsuario) {
        std::cout << "Usuario: " << actualUsuario->usuario->getCorreo() << std::endl;

        // Recorrer la lista de amigos de este usuario
        NodoAmigoo* actualAmigo = actualUsuario->listaAmigos;
        if (!actualAmigo) {
            std::cout << "  No tiene amigos." << std::endl;
        } else {
            std::cout << "  Amigos: ";
            while (actualAmigo) {
                std::cout << actualAmigo->amigo->getCorreo();
                actualAmigo = actualAmigo->siguiente;
                if (actualAmigo) {
                    std::cout << ", ";  // Para separar los amigos con coma
                }
            }
            std::cout << std::endl;
        }

        actualUsuario = actualUsuario->siguiente;
    }
}

// Método para obtener los amigos de un usuario y devolverlos en un vector para las sugerencias
std::vector<Usuario*> ListaAdyacenteGlobal::obtenerAmigos(Usuario* usuario) {
    std::vector<Usuario*> amigos;

    // Buscar al usuario en la lista global
    NodoUsuarioo* nodoUsuario = buscarUsuario(usuario);
    if (!nodoUsuario) {
        std::cout << "Usuario no encontrado en la lista global." << std::endl;
        return amigos;  // Devolver el vector vacío si no se encontró el usuario
    }

    // Recorrer la lista de amigos de este usuario
    NodoAmigoo* actualAmigo = nodoUsuario->listaAmigos;
    while (actualAmigo) {
        amigos.push_back(actualAmigo->amigo);  // Agregar el amigo al vector
        actualAmigo = actualAmigo->siguiente;
    }

    return amigos;  // Devolver el vector con los amigos
}

// Método para verificar si un usuario ya está en un vector
bool existeEnVector(const std::vector<Usuario*>& lista, Usuario* usuario) {
    for (Usuario* u : lista) {
        if (u == usuario) {
            return true;  // El usuario ya está en la lista
        }
    }
    return false;  // El usuario no está en la lista
}

// Método para obtener las sugerencias de amistad
std::vector<Usuario*> ListaAdyacenteGlobal::obtenerSugerenciasAmistad(Usuario* usuarioConectado) {
    std::vector<Usuario*> amigosConectado = obtenerAmigos(usuarioConectado);  // Obtener amigos del usuario conectado
    std::vector<Usuario*> sugerencias;  // Vector para almacenar sugerencias de amistad

    // Recorrer los amigos del usuario conectado
    for (Usuario* amigo : amigosConectado) {
        // Obtener los amigos de cada amigo (amigos de los amigos)
        std::vector<Usuario*> amigosDeAmigo = obtenerAmigos(amigo);

        // Añadir amigos de los amigos a las sugerencias si cumplen las condiciones
        for (Usuario* posibleSugerencia : amigosDeAmigo) {
            // Excluir el usuario conectado, amigos directos y evitar duplicados
            if (posibleSugerencia != usuarioConectado &&
                !existeEnVector(amigosConectado, posibleSugerencia) &&  // No debe ser un amigo directo
                !existeEnVector(sugerencias, posibleSugerencia)) {  // Evitar duplicados en sugerencias
                sugerencias.push_back(posibleSugerencia);
            }
        }
    }

    return sugerencias;  // Devolver el vector con las sugerencias de amistad
}

// Verificar si un usuario ya está en el vector de sugerencias
bool existeEnVectorSugerencia(const std::vector<Sugerencia>& lista, Usuario* usuario) {
    for (const Sugerencia& s : lista) {
        if (s.usuario == usuario) {
            return true;
        }
    }
    return false;
}


// Método para contar los amigos en común entre el usuario conectado y una sugerencia
int contarAmigosEnComun(Usuario* usuarioConectado, Usuario* sugerencia, const std::vector<Usuario*>& amigosConectado) {
    ListaAdyacenteGlobal& ListaAdyacenteG = ListaAdyacenteGlobal::getInstance();

    std::vector<Usuario*> amigosDeSugerencia = ListaAdyacenteG.obtenerAmigos(sugerencia);  // Obtener los amigos de la sugerencia
    int amigosEnComun = 0;

    // Contar cuántos amigos de la sugerencia están en la lista de amigos del usuario conectado
    for (Usuario* amigoDeSugerencia : amigosDeSugerencia) {
        if (existeEnVector(amigosConectado, amigoDeSugerencia)) {
            amigosEnComun++;  // Incrementar el contador si hay un amigo en común
        }
    }

    return amigosEnComun;
}

// Método para obtener las sugerencias de amistad y la cantidad de amigos en común
std::vector<Sugerencia> ListaAdyacenteGlobal::obtenerSugerenciasConAmigosEnComun(Usuario* usuarioConectado) {
    std::vector<Usuario*> amigosConectado = obtenerAmigos(usuarioConectado);  // Obtener amigos del usuario conectado
    std::vector<Sugerencia> sugerenciasConAmigosEnComun;  // Vector para almacenar sugerencias y amigos en común

    // Recorrer los amigos del usuario conectado
    for (Usuario* amigo : amigosConectado) {
        std::vector<Usuario*> amigosDeAmigo = obtenerAmigos(amigo);  // Obtener amigos de cada amigo

        // Recorrer los amigos de los amigos y agregar sugerencias
        for (Usuario* posibleSugerencia : amigosDeAmigo) {
            if (posibleSugerencia != usuarioConectado &&
                !existeEnVector(amigosConectado, posibleSugerencia) &&  // Usamos el método original aquí
                !existeEnVectorSugerencia(sugerenciasConAmigosEnComun, posibleSugerencia)) {

                // Contar cuántos amigos en común tienen el usuario conectado y la sugerencia
                int amigosEnComun = contarAmigosEnComun(usuarioConectado, posibleSugerencia, amigosConectado);

                // Agregar la sugerencia junto con la cantidad de amigos en común
                sugerenciasConAmigosEnComun.push_back(Sugerencia(posibleSugerencia, amigosEnComun));
            }

        }
    }

    return sugerenciasConAmigosEnComun;
}

void ListaAdyacenteGlobal::graficarListaAdyacente(const std::string& correoUsuario) {
    // Obtener la instancia de AVLUsuarios y buscar el usuario conectado
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoUsuario);

    if (!usuarioConectado) {
        std::cout << "Usuario no encontrado." << std::endl;
        return;
    }

    // Obtener amigos y sugerencias
    std::vector<Usuario*> amigos = obtenerAmigos(usuarioConectado);
    std::vector<Usuario*> sugerencias = obtenerSugerenciasAmistad(usuarioConectado);

    // Crear archivo dot para la representación gráfica
    std::string filename = "C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\listaAdyacenciaGlobal"; // Ruta completa sin extensión
    std::ofstream out(filename + ".dot");
    if (!out) {
        std::cerr << "Error al crear el archivo dot\n";
        return;
    }

    out << "digraph g {\n";
    out << "rankdir=LR;\n";

    // Graficar el usuario conectado
    out << "\"" << correoUsuario << "\" [label=\"" << correoUsuario << "\" style=filled fillcolor=\"lightblue\"];\n";

    // Graficar amigos
    for (Usuario* amigo : amigos) {
        out << "\"" << amigo->getCorreo() << "\" [label=\"" << amigo->getCorreo() << "\" style=filled fillcolor=\"yellow\"];\n";
        out << "\"" << correoUsuario << "\" -> \"" << amigo->getCorreo() << "\";\n"; // Conexión del usuario conectado con sus amigos
    }

    // Graficar sugerencias
    for (Usuario* sugerencia : sugerencias) {
        out << "\"" << sugerencia->getCorreo() << "\" [label=\"" << sugerencia->getCorreo() << "\" style=filled fillcolor=\"lightgreen\"];\n";
        out << "\"" << correoUsuario << "\" -> \"" << sugerencia->getCorreo() << "\" [style=dashed];\n"; // Conexión del usuario conectado con sugerencias
    }

    out << "}\n";
    out.close();

    // Comando para generar la imagen (asegúrate de que Graphviz esté instalado)
    std::string command = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
    int result = system(command.c_str());

    if (result != 0) {
        std::cout << "Ocurrió un error al generar la imagen.\n";
    } else {
        std::cout << "La imagen fue generada exitosamente.\n";
    }
}
