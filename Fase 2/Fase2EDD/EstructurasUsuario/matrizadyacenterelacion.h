#ifndef MATRIZADYACENTERELACION_H
#define MATRIZADYACENTERELACION_H

#include <iostream>
#include <memory>
#include <string>

class Vecino {
public:
    std::string correo;
    std::shared_ptr<Vecino> siguiente;

    Vecino(const std::string& correo);
};

class Nodo {
public:
    std::string correo;
    std::shared_ptr<Nodo> siguiente;
    std::shared_ptr<Vecino> vecinos;

    Nodo(const std::string& correo);
    void insertarVecino(const std::string& correoAmigo);
};

class MatrizAdyacenteRelacion {
private:
    std::shared_ptr<Nodo> cabeza;

public:
    MatrizAdyacenteRelacion();
    void insertarUsuario(const std::string& correoUsuario);
    void crearRelacion(const std::string& correoUsuario, const std::string& correoAmigo);
    void mostrarRelaciones(const std::string& correoUsuario);
    void graficar(const std::string& filename);  // Generar gráfico con Graphviz (opcional)
};

#endif // MATRIZADYACENTERELACION_H
