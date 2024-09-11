
#include <iostream>
#include <memory>
#include <string>
#include "NodoMenosAmigos.cpp"

using namespace std;

class ListaEnlazadaSimpleMenosAmigos {
private:
    unique_ptr<NodoMenosAmigos> cabeza;

public:
    ListaEnlazadaSimpleMenosAmigos() : cabeza(nullptr) {}

    void agregarUsuario(const string& correo, int amigos) {
        auto nuevoNodo = make_unique<NodoMenosAmigos>(correo, amigos);
        if (!cabeza || amigos < cabeza->numeroAmigos) {
            nuevoNodo->siguiente = move(cabeza);
            cabeza = move(nuevoNodo);
        } else {
            NodoMenosAmigos* actual = cabeza.get();
            while (actual->siguiente && amigos >= actual->siguiente->numeroAmigos) {
                actual = actual->siguiente.get();
            }
            nuevoNodo->siguiente = move(actual->siguiente);
            actual->siguiente = move(nuevoNodo);
        }
    }

    void mostrarTop5() const {
        cout << "Top 5 usuarios con menos amigos:" << endl;
        NodoMenosAmigos* actual = cabeza.get();
        int count = 0;
        while (actual && count < 5) {
            cout << actual->correoUsuario << " (" << actual->numeroAmigos << " amigos)" << endl;
            ++count;
            actual = actual->siguiente.get();
        }
        if (count == 0) {
            cout << "No hay suficientes usuarios para mostrar el top 5." << endl;
        }
    }
};