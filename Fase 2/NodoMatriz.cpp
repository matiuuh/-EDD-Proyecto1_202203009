#include <iostream>
#include <fstream>
#include <string>
#include "ListaEnlazadaAmigos.cpp" // Incluir el archivo de encabezado para ListaEnlazadaAmigos


using namespace std;

class NodoMatriz {
public:
    string nombre;
    NodoMatriz* siguiente;
    ListaEnlazadaAmigos amigos; // Lista de amigos


    NodoMatriz(const string& nombre) : nombre(nombre), siguiente(nullptr) {}

};