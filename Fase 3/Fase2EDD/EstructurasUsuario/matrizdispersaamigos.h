#ifndef MATRIZDISPERSAAMIGOS_H
#define MATRIZDISPERSAAMIGOS_H

#include <string>
#include <iostream>
#include <memory>  // Para punteros inteligentes

class MatrizDispersaAmigos {
public:
    // Constructor
    MatrizDispersaAmigos();

    // Métodos para manejar la matriz dispersa
    void agregarAmistad(const std::string& correoRemitente);
    bool buscarAmistad(const std::string& correoRemitente);
    void eliminarAmistad(const std::string& correoRemitente);
    void imprimirAmigos(const std::string& correoUsuario) const;

private:
    // Clase interna para los nodos de la matriz
    class NodoMatriz {
    public:
        NodoMatriz(const std::string& correoRemitente)
            : correoRemitente(correoRemitente), abajo(nullptr), derecha(nullptr) {}

        std::string correoRemitente;
        std::shared_ptr<NodoMatriz> abajo;
        std::shared_ptr<NodoMatriz> derecha;
    };

    // Puntero a la cabecera de la matriz
    std::shared_ptr<NodoMatriz> raiz;

    // Métodos auxiliares
    std::shared_ptr<NodoMatriz> buscarNodo(const std::string& correoRemitente) const;

};

#endif // MATRIZDISPERSAAMIGOS_H
