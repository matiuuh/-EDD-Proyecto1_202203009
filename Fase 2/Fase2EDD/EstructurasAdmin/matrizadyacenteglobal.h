#ifndef MATRIZADYACENTEGLOBAL_H
#define MATRIZADYACENTEGLOBAL_H

#include <vector>
#include <string>

// Estructura NodoUsuario para la lista enlazada
struct NodoUsuarioe {
    std::string correoUsuario;
    int indice;
    NodoUsuarioe* siguiente;

    NodoUsuarioe(const std::string& correo, int idx) : correoUsuario(correo), indice(idx), siguiente(nullptr) {}

};

class MatrizAdyacenteGlobal
{
public:
    MatrizAdyacenteGlobal();

    // Métodos para gestionar la matriz de adyacencia global
    void agregarUsuario(const std::string& correoUsuario);
    void agregarRelacion(const std::string& correo1, const std::string& correo2);
    void eliminarRelacion(const std::string& correo1, const std::string& correo2);
    bool sonAmigos(const std::string& correo1, const std::string& correo2) const;
    void graficarMatriz() const;

    static MatrizAdyacenteGlobal& getInstancia();  // Método estático para obtener la instancia única

    std::vector<std::string> sugerirAmigos(const std::string& correoUsuario);

    std::vector<int> obtenerSugerenciasAmistad(int indiceUsuarioConectado);
    void graficarMatrizConSugerencias(const std::string& correoUsuarioConectado);

private:
    static NodoUsuarioe* listaUsuarios;                    // Lista enlazada de usuarios
    static std::vector<std::vector<int>> matrizAdyacencia; // Matriz de adyacencia
    static int numUsuarios;

    int obtenerIndice(const std::string& correo) const;

    NodoUsuarioe* obtenerUsuarioPorIndice(int indice) const;
};

#endif // MATRIZADYACENTEGLOBAL_H
