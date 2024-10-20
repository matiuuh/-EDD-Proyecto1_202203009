#include "matrizadyacenteglobal.h"
#include <iostream>
#include <fstream>

#include <queue>
#include <vector>
#include <algorithm>  // Para std::sort

// Inicialización de variables estáticas fuera de la clase
NodoUsuarioe* MatrizAdyacenteGlobal::listaUsuarios = nullptr;
std::vector<std::vector<int>> MatrizAdyacenteGlobal::matrizAdyacencia;
int MatrizAdyacenteGlobal::numUsuarios = 0;

MatrizAdyacenteGlobal::MatrizAdyacenteGlobal() {}

// Agregar un nuevo usuario a la lista enlazada y al grafo
void MatrizAdyacenteGlobal::agregarUsuario(const std::string& correoUsuario) {
    // Verificar si el usuario ya está en la lista enlazada
    if (obtenerIndice(correoUsuario) == -1) {
        NodoUsuarioe* nuevoUsuario = new NodoUsuarioe(correoUsuario, numUsuarios++);

        // Añadir el nuevo usuario al inicio de la lista enlazada
        nuevoUsuario->siguiente = listaUsuarios;
        listaUsuarios = nuevoUsuario;

        // Aumentar el tamaño de la matriz de adyacencia para incluir al nuevo usuario
        matrizAdyacencia.resize(numUsuarios);
        for (int i = 0; i < numUsuarios; ++i) {
            matrizAdyacencia[i].resize(numUsuarios, 0);  // Inicializar con 0 (sin amistad)
        }
    }
}

// Agregar una relación de amistad entre dos usuarios
void MatrizAdyacenteGlobal::agregarRelacion(const std::string& correo1, const std::string& correo2) {
    int indice1 = obtenerIndice(correo1);
    int indice2 = obtenerIndice(correo2);

    if (indice1 != -1 && indice2 != -1) {
        matrizAdyacencia[indice1][indice2] = 1;
        matrizAdyacencia[indice2][indice1] = 1;  // Amistad bidireccional
    }
}

// Eliminar una relación de amistad entre dos usuarios
void MatrizAdyacenteGlobal::eliminarRelacion(const std::string& correo1, const std::string& correo2) {
    int indice1 = obtenerIndice(correo1);
    int indice2 = obtenerIndice(correo2);

    if (indice1 != -1 && indice2 != -1) {
        matrizAdyacencia[indice1][indice2] = 0;
        matrizAdyacencia[indice2][indice1] = 0;  // Eliminar ambas direcciones
    }
}

// Verificar si dos usuarios son amigos
bool MatrizAdyacenteGlobal::sonAmigos(const std::string& correo1, const std::string& correo2) const {
    int indice1 = obtenerIndice(correo1);
    int indice2 = obtenerIndice(correo2);

    if (indice1 != -1 && indice2 != -1) {
        return matrizAdyacencia[indice1][indice2] == 1;
    }
    return false;
}

// Graficar la matriz de adyacencia
void MatrizAdyacenteGlobal::graficarMatriz() const {
    std::ofstream archivo("C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\grafoGlobal.dot");
    archivo << "graph G {\n";

    NodoUsuarioe* actual = listaUsuarios;
    while (actual) {
        NodoUsuarioe* actual2 = listaUsuarios;
        while (actual2) {
            if (matrizAdyacencia[actual->indice][actual2->indice] == 1) {
                archivo << "  \"" << actual->correoUsuario << "\" -- \"" << actual2->correoUsuario << "\";\n";
            }
            actual2 = actual2->siguiente;
        }
        actual = actual->siguiente;
    }

    archivo << "}\n";
    archivo.close();
    std::cout << "Gráfico generado en grafoGlobal.dot\n";

    // Generar la imagen
    std::string command = "dot -Tpng C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\grafoGlobal.dot -o C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\grafoGlobalSinColor.png";
    int result = system(command.c_str());

    if (result != 0) {
        std::cout << "Ocurrió un error al generar la imagen del gráfico global.\n";
    } else {
        std::cout << "La imagen del gráfico global fue generada exitosamente.\n";
    }
}


// Obtener el índice de un usuario en la matriz desde la lista enlazada
int MatrizAdyacenteGlobal::obtenerIndice(const std::string& correo) const {
    NodoUsuarioe* actual = listaUsuarios;
    while (actual) {
        if (actual->correoUsuario == correo) {
            return actual->indice;
        }
        actual = actual->siguiente;
    }
    return -1;  // No encontrado
}

//-----------------PARA OBTENER LA INSTANCIA GLOBAL-----------
MatrizAdyacenteGlobal& MatrizAdyacenteGlobal::getInstancia() {
    static MatrizAdyacenteGlobal instancia;  // Instancia local estática, segura para hilos
    return instancia;
}

std::vector<std::string> MatrizAdyacenteGlobal::sugerirAmigos(const std::string& correoUsuario) {
    int indiceUsuario = obtenerIndice(correoUsuario);
    if (indiceUsuario == -1) {
        std::cout << "Usuario no encontrado." << std::endl;
        return {};
    }

    std::vector<int> amigosEnComun(numUsuarios, 0);  // Almacena el conteo de amigos en común por cada usuario
    std::queue<int> colaAmigos;  // Cola para almacenar los índices de los amigos directos del usuario

    // Primer salto: Encontrar los amigos directos del usuario
    for (int i = 0; i < numUsuarios; ++i) {
        if (matrizAdyacencia[indiceUsuario][i] == 1) {
            colaAmigos.push(i);  // Guardar en la cola los amigos directos
        }
    }

    // Segundo salto: Encontrar amigos de amigos (usuarios a dos saltos)
    while (!colaAmigos.empty()) {
        int indiceAmigo = colaAmigos.front();
        colaAmigos.pop();

        for (int j = 0; j < numUsuarios; ++j) {
            if (matrizAdyacencia[indiceAmigo][j] == 1 && j != indiceUsuario && matrizAdyacencia[indiceUsuario][j] == 0) {
                // Si es amigo del amigo pero no amigo directo del usuario conectado
                amigosEnComun[j]++;  // Incrementar el contador de amigos en común
            }
        }
    }

    // Vector para almacenar los usuarios sugeridos (índices)
    std::vector<int> sugerencias;

    // Obtener los usuarios con amigos en común
    for (int i = 0; i < numUsuarios; ++i) {
        if (amigosEnComun[i] > 0) {
            sugerencias.push_back(i);  // Agregar los usuarios que tienen amigos en común
        }
    }

    // Ordenar los usuarios sugeridos por la cantidad de amigos en común (mayor a menor)
    std::sort(sugerencias.begin(), sugerencias.end(), [&amigosEnComun](int a, int b) {
        return amigosEnComun[a] > amigosEnComun[b];
    });

    // Limitar el número de sugerencias a 5 usuarios
    std::vector<std::string> topSugerencias;
    for (size_t i = 0; i < std::min(sugerencias.size(), size_t(5)); ++i) {
        NodoUsuarioe* usuarioSugerido = obtenerUsuarioPorIndice(sugerencias[i]);  // Obtener el nodo del usuario por índice
        topSugerencias.push_back(usuarioSugerido->correoUsuario);  // Guardar el correo del usuario sugerido
    }

    return topSugerencias;
}

NodoUsuarioe* MatrizAdyacenteGlobal::obtenerUsuarioPorIndice(int indice) const {
    NodoUsuarioe* actual = listaUsuarios;
    while (actual) {
        if (actual->indice == indice) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;  // Si no se encuentra
}

void MatrizAdyacenteGlobal::graficarMatrizConSugerencias(const std::string& correoUsuarioConectado) {
    // Obtener el índice del usuario conectado
    int indiceUsuarioConectado = obtenerIndice(correoUsuarioConectado);
    if (indiceUsuarioConectado == -1) {
        std::cout << "Usuario conectado no encontrado en la matriz." << std::endl;
        return;
    }

    // Vector para almacenar los usuarios sugeridos (amigos de amigos)
    std::vector<int> sugerenciasAmistad = obtenerSugerenciasAmistad(indiceUsuarioConectado);

    // Crear archivo para Graphviz
    std::ofstream archivo("C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\grafoGlobal.dot");
    archivo << "graph G {\n";

    // Graficar relaciones de amistad
    NodoUsuarioe* actual = listaUsuarios;
    while (actual) {
        NodoUsuarioe* actual2 = listaUsuarios;
        while (actual2) {
            if (matrizAdyacencia[actual->indice][actual2->indice] == 1) {
                archivo << "  \"" << actual->correoUsuario << "\" -- \"" << actual2->correoUsuario << "\";\n";
            }
            actual2 = actual2->siguiente;
        }
        actual = actual->siguiente;
    }

    // Colorear el usuario conectado en azul
    archivo << "  \"" << correoUsuarioConectado << "\" [style=filled, color=blue];\n";

    // Colorear los amigos directos del usuario conectado en amarillo
    std::vector<int> amigosDirectos;  // Vector para guardar amigos directos
    for (int i = 0; i < numUsuarios; ++i) {
        if (matrizAdyacencia[indiceUsuarioConectado][i] == 1) {
            NodoUsuarioe* amigo = obtenerUsuarioPorIndice(i);
            archivo << "  \"" << amigo->correoUsuario << "\" [style=filled, color=yellow];\n";
            amigosDirectos.push_back(i);  // Guardar el índice de los amigos directos
        }
    }

    // Colorear los amigos de amigos (sugerencias de amistad) en verde, si no son amigos directos
    for (int indice : sugerenciasAmistad) {
        // Verificar si el "amigo de amigo" no es ya un amigo directo
        bool esAmigoDirecto = false;
        for (int amigoDirecto : amigosDirectos) {
            if (indice == amigoDirecto) {
                esAmigoDirecto = true;
                break;
            }
        }

        // Si no es amigo directo, lo coloreamos de verde
        if (!esAmigoDirecto) {
            NodoUsuarioe* usuarioSugerido = obtenerUsuarioPorIndice(indice);
            archivo << "  \"" << usuarioSugerido->correoUsuario << "\" [style=filled, color=green];\n";
        }
    }

    archivo << "}\n";
    archivo.close();

    std::cout << "Gráfico con sugerencias de amistad generado en grafoGlobal.dot\n";

    // Generar la imagen del gráfico
    std::string command = "dot -Tpng C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\grafoGlobal.dot -o C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\grafoGlobal.png";
    int result = system(command.c_str());

    if (result != 0) {
        std::cout << "Ocurrió un error al generar la imagen del gráfico global.\n";
    } else {
        std::cout << "La imagen del gráfico global con sugerencias fue generada exitosamente.\n";
    }
}


std::vector<int> MatrizAdyacenteGlobal::obtenerSugerenciasAmistad(int indiceUsuarioConectado) {
    std::vector<int> amigosDirectos;  // Lista de amigos directos
    std::vector<int> amigosEnComun(numUsuarios, 0);  // Almacena el conteo de amigos en común
    std::vector<int> sugerencias;  // Usuarios sugeridos

    // Primer paso: encontrar amigos directos
    for (int i = 0; i < numUsuarios; ++i) {
        if (matrizAdyacencia[indiceUsuarioConectado][i] == 1) {
            amigosDirectos.push_back(i);  // Agregar amigo directo a la lista
        }
    }

    // Segundo paso: encontrar amigos de amigos (a dos saltos)
    for (int indiceAmigo : amigosDirectos) {
        // Buscar amigos de este amigo (amigos de amigos)
        for (int j = 0; j < numUsuarios; ++j) {
            if (matrizAdyacencia[indiceAmigo][j] == 1 && j != indiceUsuarioConectado && matrizAdyacencia[indiceUsuarioConectado][j] == 0) {
                // Si es amigo de un amigo, pero no amigo directo del usuario conectado
                amigosEnComun[j]++;  // Incrementar el contador de amigos en común
            }
        }
    }

    // Obtener las sugerencias (usuarios con amigos en común)
    for (int i = 0; i < numUsuarios; ++i) {
        if (amigosEnComun[i] > 0) {
            sugerencias.push_back(i);  // Agregar a la lista de sugerencias
        }
    }

    // Ordenar los usuarios sugeridos por la cantidad de amigos en común (de mayor a menor)
    std::sort(sugerencias.begin(), sugerencias.end(), [&amigosEnComun](int a, int b) {
        return amigosEnComun[a] > amigosEnComun[b];
    });

    return sugerencias;
}

