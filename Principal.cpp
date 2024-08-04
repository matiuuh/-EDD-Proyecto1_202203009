#include <iostream>
#include <vector>
#include "Usuario.h"  // Asegúrate de incluir Usuario.h aquí

using namespace std;

// Prototipos
void menu();
void iniciarSesion();
void registro(vector<Usuario>& listaPrueba);

int main() {
    // Llamar al menú
    menu();

    system("pause");
    return 0;
}

void menu() {
    int opcion;
    vector<Usuario> listaPrueba; // Declaramos aquí para usar en otras funciones

    do {
        cout << "\t-----Menu-----\n";
        cout << "\t1. Iniciar sesion" << endl;
        cout << "\t2. Registrarse" << endl;
        cout << "\t3. Informacion" << endl;
        cout << "\t4. Salir" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\n";
                system("pause");
                break;
            case 2:
                registro(listaPrueba);
                cout << "\n";
                system("pause");
                break;
            case 3:
                cout << "Nombre: Mateo Estuardo Diego Noriega" << endl;
                cout << "Carnet: 202203009" << endl;
                cout << "Link del repositorio: https://github.com/matiuuh/-EDD-Proyecto1_202203009.git";
                cout << "\n";
                system("pause");
                break;
            case 4:
                cout << "Saliendo del programa ";
                break;
            default:
                cout << "Ingrese una opcion valida. ";
                system("pause");
                break;
        }
        system("cls");
    } while (opcion != 4);
}

void registro(vector<Usuario>& listaPrueba) {
    std::string nombre, apellidos, fechaNacimiento, correo, contrasenia;

    std::cout << "Ingrese el nombre: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese los apellidos: ";
    std::getline(std::cin, apellidos);

    std::cout << "Ingrese la fecha de nacimiento (DD/MM/YYYY): ";
    std::getline(std::cin, fechaNacimiento);

    std::cout << "Ingrese el correo: ";
    std::getline(std::cin, correo);
    
    std::cout << "Ingrese el contrasenia: ";
    std::getline(std::cin, contrasenia);

    Usuario nuevoUsuario(nombre, apellidos, fechaNacimiento, correo, contrasenia);
    listaPrueba.push_back(nuevoUsuario);
}