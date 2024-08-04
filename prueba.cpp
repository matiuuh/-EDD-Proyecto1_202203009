#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Clase Usuario
class Usuario {
public:
    Usuario(const string& nombre, const string& apellidos, const string& fechaNacimiento, const string& correo, const string& contrasenia)
        : nombre(nombre), apellidos(apellidos), fechaNacimiento(fechaNacimiento), correo(correo), contrasenia(contrasenia) {}

    string getNombre() const { return nombre; }
    string getApellidos() const { return apellidos; }
    string getFechaNacimiento() const { return fechaNacimiento; }
    string getCorreo() const { return correo; }
    string getContrasenia() const { return contrasenia; }

private:
    string nombre;
    string apellidos;
    string fechaNacimiento;
    string correo;
    string contrasenia;
};

// Clase Nodo
class Nodo {
public:
    Usuario usuario;
    unique_ptr<Nodo> siguiente;

    Nodo(const Usuario& usuario) : usuario(usuario), siguiente(nullptr) {}
};

// Clase ListaEnlazada
class ListaEnlazada {
public:
    unique_ptr<Nodo> cabeza;

    ListaEnlazada() : cabeza(nullptr) {}

    //funcion para agregar usuarios
    void agregarUsuario(const Usuario& usuario) {
        unique_ptr<Nodo> nuevoNodo = make_unique<Nodo>(usuario);

        if (!cabeza) {
            cabeza = move(nuevoNodo);
        } else {
            Nodo* temp = cabeza.get();
            while (temp->siguiente) {
                temp = temp->siguiente.get();
            }
            temp->siguiente = move(nuevoNodo);
        }
    }

    //función para buscar usuarios según el correo
    Usuario* buscarUsuarioPorCorreo(const string& correo) {
        Nodo* temp = cabeza.get();
        while (temp) {
            if (temp->usuario.getCorreo() == correo) {
                return &temp->usuario;
            }
            temp = temp->siguiente.get();
        }
        return nullptr; // Si no se encuentra el usuario
    }

    //función para mostrar los usuarios
    void mostrarUsuarios() const {
        Nodo* temp = cabeza.get();
        while (temp) {
            cout << "Nombre: " << temp->usuario.getNombre() << ", Apellidos: " << temp->usuario.getApellidos()
                << ", Fecha de Nacimiento: " << temp->usuario.getFechaNacimiento() << ", Correo: " << temp->usuario.getCorreo()
                << endl;
            temp = temp->siguiente.get();
        }
    }
};

// Prototipos
void menu();
void iniciarSesion(ListaEnlazada&);
void registro(ListaEnlazada&);

int main() {
    // Llamar al menú
    menu();

    system("pause");
    return 0;
}

void menu() {
    int opcion;
    //hago una instancia de listaEnlazada para acceder a sus métodos
    ListaEnlazada listaUsuarios;

    do {
        cout << "\t-----Menu-----\n";
        cout << "\t1. Iniciar sesion" << endl;
        cout << "\t2. Registrarse" << endl;
        cout << "\t3. Informacion" << endl;
        cout << "\t4. Salir" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion) {
            case 1:
                iniciarSesion(listaUsuarios);
                cout << "\n";
                system("pause");
                break;
            case 2:
                registro(listaUsuarios);
                cout << "\n";
                system("pause");
                break;
            case 3:
                cout << "Nombre: Mateo Estuardo Diego Noriega" << endl;
                cout << "Carnet: 202203009" << endl;
                cout << "Link del repositorio: https://github.com/matiuuh/-EDD-Proyecto1_202203009.git" << endl;
                cout << "\n";
                listaUsuarios.mostrarUsuarios();
                system("pause");
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Ingrese una opcion valida." << endl;
                system("pause");
                break;
        }
        system("cls");
    } while (opcion != 4);
}

void iniciarSesion(ListaEnlazada& lista) {
    string correo, contrasenia;
    cout << "Ingrese el correo: "; getline(cin, correo);
    cout << "Ingrese la contrasenia: "; getline(cin, contrasenia);

    // Buscar al usuario por correo
    Usuario* usuario = lista.buscarUsuarioPorCorreo(correo);
    if(usuario){
        // Verificar si la contraseña es correcta
        if(usuario->getContrasenia() == contrasenia){
            cout << "Inicio de sesión exitoso. Bienvenido, " << usuario->getNombre() << "!" << endl;
            
        }else{
            cout << "Credenciales incorrectas" << endl;
        }
    }else {
        cout << "Credenciales incorrectas" << endl;
    }
}


void registro(ListaEnlazada& lista) {
    string nombre, apellidos, fechaNacimiento, correo, contrasenia;

    cout << "Ingrese el nombre: "; getline(cin, nombre);
    cout << "Ingrese los apellidos: "; getline(cin, apellidos);
    cout << "Ingrese la fecha de nacimiento (DD/MM/YYYY): "; getline(cin, fechaNacimiento);
    cout << "Ingrese el correo: "; getline(cin, correo);
    cout << "Ingrese la contrasenia: "; getline(cin, contrasenia);

    // Verificar si el correo ya existe
    if (lista.buscarUsuarioPorCorreo(correo)) {
        cout << "Error: Ya existe un usuario con este correo." << endl;
        return; // Salir de la función si el correo ya está registrado
    }

    Usuario nuevoUsuario(nombre, apellidos, fechaNacimiento, correo, contrasenia);
    lista.agregarUsuario(nuevoUsuario);

    cout << "Usuario registrado exitosamente." << endl;
}
