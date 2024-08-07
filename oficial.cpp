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

class ListaSimpleSolicitudes {
public:
    struct NodoLista {
        string solicitud;
        NodoLista* siguiente;
    };

    NodoLista* cabeza;

    ListaSimpleSolicitudes() : cabeza(nullptr) {}

    // Destructor para liberar memoria
    ~ListaSimpleSolicitudes() {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            NodoLista* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void agregarSolicitud(const string& solicitud) {
        NodoLista* nuevoNodo = new NodoLista{solicitud, cabeza};
        cabeza = nuevoNodo;
    }

    // Ejemplo de función para eliminar la primera solicitud encontrada
    bool eliminarSolicitud(const string& solicitud) {
        NodoLista* actual = cabeza;
        NodoLista* anterior = nullptr;
        while (actual != nullptr) {
            if (actual->solicitud == solicitud) {
                if (anterior == nullptr) {
                    // El nodo a eliminar es el primero
                    cabeza = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        return false; // No se encontró la solicitud
    }

    // Ejemplo de función para buscar una solicitud
    bool buscarSolicitud(const string& solicitud) const {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            if (actual->solicitud == solicitud) {
                return true; // Se encontró la solicitud
            }
            actual = actual->siguiente;
        }
        return false; // No se encontró la solicitud
    }

    // Ejemplo de función para mostrar todas las solicitudes
    void mostrarSolicitudes() const {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->solicitud << endl;
            actual = actual->siguiente;
        }
    }
};


class Pila {
public:
    struct NodoPila {
        string solicitud;
        NodoPila* siguiente;
    };

    NodoPila* tope;

    Pila() : tope(nullptr) {}

    void push(const string& solicitud) {
        NodoPila* nuevoNodo = new NodoPila{solicitud, tope};
        tope = nuevoNodo;
    }

    void pop() {
        if (tope) {
            NodoPila* nodoAEliminar = tope;
            tope = tope->siguiente;
            delete nodoAEliminar;
        }
    }

    bool estaVacia() const {
        return tope == nullptr;
    }

    string obtenerTope() const {
        return tope ? tope->solicitud : "";
    }
};


// Prototipos
void menu();
void menuUsuario(ListaEnlazada& lista, const Usuario& usuarioConectado);
void iniciarSesion(ListaEnlazada&);
void registro(ListaEnlazada&);
void menuAdmin();
void subMenuPerfil(ListaEnlazada& lista, const Usuario& usuarioConectado);
void subMenuSolicitudes(/*const Usuario& usuarioConectado*/);
void subMenuPublicaciones(const Usuario& usuarioConectado);
void enviarSolicitud(Usuario&, Usuario&);
void aceptarSolicitud(Usuario&);
void eliminarCuenta(ListaEnlazada& lista, const Usuario& usuarioConectado);

int main() {
    // Llamar al menú
    menu();
    //system("pause");
    return 0;
}

//función del menú principal
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

//función para el inicio de sesión
void iniciarSesion(ListaEnlazada& lista) {
    string correo, contrasenia;
    cout << "Ingrese el correo: "; getline(cin, correo);
    cout << "Ingrese la contrasenia: "; getline(cin, contrasenia);

    // Verificar si es el administrador
    if (correo == "admin" && contrasenia == "EDD") {
        cout << "Inicio de sesion como Administrador exitoso. Bienvenido, Administrador!" << endl;
        menuAdmin();
        return; // Salir de la función después de iniciar sesión como administrador
    }

    // Buscar al usuario por correo
    Usuario* usuario = lista.buscarUsuarioPorCorreo(correo);
    if(usuario){
        // Verificar si la contraseña es correcta
        if(usuario->getContrasenia() == contrasenia){
            cout << "Inicio de sesion exitoso. Bienvenido, " << usuario->getNombre() << "!" << endl;
            menuUsuario(lista, *usuario);
        }else{
            cout << "Credenciales incorrectas" << endl;
        }
    }else {
        cout << "Credenciales incorrectas" << endl;
    }
}

//función para crear usuarios
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

//función para mostrar el menú de usuario
void menuUsuario(ListaEnlazada& lista, const Usuario& usuarioConectado){
    int opcion;
    do {
        cout << "\t-----Menu Usuario-----\n";
        cout << "\t1. Perfil" << endl;
        cout << "\t2. Solicitudes" << endl;
        cout << "\t3. Publicaciones" << endl;
        cout << "\t4. Reportes" << endl;
        cout << "\t5. Salir" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        system("cls");
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion) {
            case 1:
            cout<<"---------Perfil---------"<<endl;
                cout << "Usuario Conectado: " << usuarioConectado.getNombre() << " " << usuarioConectado.getApellidos() << endl;
                subMenuPerfil(lista, usuarioConectado);
                cout << "\n";
                system("pause");
                break;
            case 2:
                cout<<"---------Solicitudes---------"<<endl;
                subMenuSolicitudes(/*usuarioConectado*/);
                cout << "\n";
                system("pause");
                break;
            case 3:
                cout << "---------Publicaciones---------" << endl;
                subMenuPublicaciones(usuarioConectado);
                cout << "\n";
                system("pause");
                break;
            case 4:
                cout << "---------Reportes---------" << endl;
                system("pause");
                break;
            case 5:
                cout << "volviendo..." << endl;
                break;
            default:
                cout << "Ingrese una opcion valida." << endl;
                system("pause");
                break;
        }
        system("cls");
    } while (opcion != 5);
}

//función para mostrar el menú del administrador
void menuAdmin(){
    int opcion;
    do {
        cout << "\t-----Menu ADMINISTRADOR-----\n";
        cout << "\t1. Carga de usuarios" << endl;
        cout << "\t2. Carga de relaciones" << endl;
        cout << "\t3. Carga de publicaciones" << endl;
        cout << "\t4. Gestionear usuarios" << endl;
        cout << "\t5. Reportes" << endl;
        cout << "\t6. Salir" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion) {
            case 1:
            cout<<"---------Estamos en la carga de usuarios---------"<<endl;
                //iniciarSesion(listaUsuarios);
                cout << "\n";
                system("pause");
                break;
            case 2:
                cout<<"---------relaciones---------"<<endl;
                cout << "\n";
                system("pause");
                break;
            case 3:
                cout << "---------publicaciones---------" << endl;
                cout << "Carnet: 202203009" << endl;
                cout << "Link del repositorio: https://github.com/matiuuh/-EDD-Proyecto1_202203009.git" << endl;
                cout << "\n";
                system("pause");
                break;
            case 4:
                cout << "---------gestion usuarios---------" << endl;
                system("pause");
                break;
            case 5:
                cout << "----------reportes----------" << endl;
                system("pause");
                break;
            case 6:
                cout << "volviendo..." << endl;
                system("pause");
                break;
            default:
                cout << "Ingrese una opcion valida." << endl;
                system("pause");
                break;
        }
        system("cls");
    } while (opcion != 6);
}

//Se agregan los sub-menús del menú de perfil
void subMenuPerfil(ListaEnlazada& lista, const Usuario& usuarioConectado){
    char opcion;
    do{
        cout << "\ta. Ver perfil" << endl;
        cout << "\tb. Eliminar Cuenta" << endl;
        cout << "\tc. Volver" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion){
        case 'a':
            cout << "---------Ver Perfil---------" << endl;
            system("pause");
            break;
        case 'b':
            cout << "---------Elimnar Cuenta---------" << endl;
            eliminarCuenta(lista, usuarioConectado);
            break;
        case 'c':
            cout<<"Saliendo del menu... "<<endl;
            break;
        default:
            cout<<"Ingrese una opcion valida... "<<endl;
            system("pause");
            break;
        }
    } while (opcion!='c');
    
}

//sub-menú de solicitudes
void subMenuSolicitudes(/*const Usuario& usuarioConectado*/){
    char opcion;
    do{
        cout << "\ta. Ver solicitudes" << endl;
        cout << "\tb. Enviar" << endl;
        cout << "\tc. Volver" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion){
        case 'a':
            cout << "---------Ver Solicitudes---------" << endl;
            system("pause");
            break;
        case 'b':
            cout << "---------Enviar---------" << endl;
            //eliminarCuenta(lista, usuarioConectado);
            break;
        case 'c':
            cout<<"Saliendo del menu... "<<endl;
            system("pause");
            break;
        default:
            cout<<"Ingrese una opcion valida... "<<endl;
            system("pause");
            break;
        }
    } while (opcion!='c');
}

//sub-menú de publicaciones
void subMenuPublicaciones(const Usuario& usuarioConectado){
    char opcion;
    do{
        cout << "\ta. Ver todas" << endl;
        cout << "\tb. Crear" << endl;
        cout << "\tc. Eliminar" << endl;
        cout << "\td. Volver" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion){
        case 'a':
            cout << "---------Ver Todas---------" << endl;
            system("pause");
            break;
        case 'b':
            cout << "---------Crear---------" << endl;
            system("pause");
            break;
        case 'c':
            cout << "---------Eliminar---------" << endl;
            //eliminarCuenta(lista, usuarioConectado);//cambiar de lugar esto
            break;
        case 'd':
            cout<<"Saliendo del menu... "<<endl;
            system("pause");
            break;
        default:
            cout<<"Ingrese una opcion valida... "<<endl;
            system("pause");
            break;
        }
    } while (opcion!='d');
}

void eliminarCuenta(ListaEnlazada& lista, const Usuario& usuarioConectado) {
    cout << "¿Estas seguro de que deseas eliminar tu cuenta? Esta accion es irreversible. (si/no): ";
    string confirmacion; cin >> confirmacion;

    if (confirmacion == "si") {
        // Lógica para eliminar la cuenta del usuarioConectado
        // Debemos buscar y eliminar el usuario de la lista
        bool eliminado = false;
        Nodo* actual = lista.cabeza.get();
        Nodo* anterior = nullptr;

        while (actual) {
            if (actual->usuario.getCorreo() == usuarioConectado.getCorreo()) {
                if (anterior) {
                    anterior->siguiente = move(actual->siguiente);
                } else {
                    lista.cabeza = move(actual->siguiente);
                }
                eliminado = true;
                break;
            }
            anterior = actual;
            actual = actual->siguiente.get();
        }

        if (eliminado) {
            cout << "Cuenta de " << usuarioConectado.getNombre() << " eliminada exitosamente." << endl;
        } else {
            cout << "No se encontro la cuenta para eliminar." << endl;
        }

        // Redirigir al menú principal después de eliminar la cuenta
        return;
    } else {
        cout << "Cancelando eliminacion de cuenta." << endl;
    }
}
