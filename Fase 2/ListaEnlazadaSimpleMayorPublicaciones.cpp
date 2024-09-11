
#include <iostream>
#include <memory>
#include <string>
#include "NodoPublicaciones.cpp"

using namespace std;

class ListaEnlazadaSimpleMayorPublicaciones {
private:
    unique_ptr<NodoPublicaciones> cabeza;

public:
    ListaEnlazadaSimpleMayorPublicaciones() : cabeza(nullptr) {}

    void agregarUsuario(const string& correo, int publicaciones) {
        auto nuevoNodo = make_unique<NodoPublicaciones>(correo, publicaciones);
        if (!cabeza || publicaciones > cabeza->numeroPublicaciones) {
            nuevoNodo->siguiente = move(cabeza);
            cabeza = move(nuevoNodo);
        } else {
            NodoPublicaciones* actual = cabeza.get();
            while (actual->siguiente && publicaciones <= actual->siguiente->numeroPublicaciones) {
                actual = actual->siguiente.get();
            }
            nuevoNodo->siguiente = move(actual->siguiente);
            actual->siguiente = move(nuevoNodo);
        }
    }

    void mostrarTop5() const {
        cout << "Top 5 usuarios con más publicaciones:" << endl;
        NodoPublicaciones* actual = cabeza.get();
        int count = 0;
        while (actual && count < 5) {
            cout << actual->correoUsuario << " (" << actual->numeroPublicaciones << " publicaciones)" << endl;
            ++count;
            actual = actual->siguiente.get();
        }
        if (count == 0) {
            cout << "No hay suficientes usuarios para mostrar el top 5." << endl;
        }
    }
};