#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <ctime> // Para obtener la fecha y hora actual

using namespace std;

class Publicacion {
private:
    string correoUsuario;
    string contenido;
    string fecha;
    string hora;

public:
    Publicacion(const std::string& correo, const std::string& contenido)
        : correoUsuario(correo), contenido(contenido) {
        // Obtener la fecha y hora actual
        time_t now = time(0);
        tm* ltm = localtime(&now);

        // Formatear la fecha y la hora
        fecha = to_string(1900 + ltm->tm_year) + "-" +
                to_string(1 + ltm->tm_mon) + "-" +
                to_string(ltm->tm_mday);

        hora = to_string(ltm->tm_hour) + ":" +
                to_string(ltm->tm_min) + ":" +
                to_string(ltm->tm_sec);
    }

    // Métodos para obtener los datos de la publicación
    string getCorreoUsuario() const { return correoUsuario; }
    string getContenido() const { return contenido; }
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }

    // Método para mostrar la publicación
    void mostrarPublicacion() const {
        cout << "Correo: " << correoUsuario << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Hora: " << hora << endl;
        cout << "Contenido: " << contenido << endl;
    }
};

class NodoPublicacion {
public:
    shared_ptr<Publicacion> publicacion;
    shared_ptr<NodoPublicacion> siguiente;
    shared_ptr<NodoPublicacion> anterior;

    NodoPublicacion(const shared_ptr<Publicacion>& publicacion)
        : publicacion(publicacion), siguiente(nullptr), anterior(nullptr) {}
};

class ListaDoblePublicaciones {
private:
    shared_ptr<NodoPublicacion> cabeza;
    shared_ptr<NodoPublicacion> cola;

public:
    ListaDoblePublicaciones() : cabeza(nullptr), cola(nullptr) {}

    void agregarPublicacion(const shared_ptr<Publicacion>& publicacion) {
        auto nuevoNodo = make_shared<NodoPublicacion>(publicacion);
        if (!cabeza) {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
    }

    void mostrarPublicaciones() const {
        auto actual = cabeza;
        while (actual) {
            actual->publicacion->mostrarPublicacion();
            cout << "-----------------------" << endl;
            actual = actual->siguiente;
        }
    }
};

// Clase ListaSimpleSolicitudes
class ListaSimpleSolicitudes {
public:
    struct NodoLista {
        string solicitud;
        NodoLista* siguiente;
    };

    NodoLista* cabeza;

    ListaSimpleSolicitudes() : cabeza(nullptr) {}

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

    bool eliminarSolicitud(const string& solicitud) {
        NodoLista* actual = cabeza;
        NodoLista* anterior = nullptr;
        while (actual != nullptr) {
            if (actual->solicitud == solicitud) {
                if (anterior == nullptr) {
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
        return false;
    }

    bool buscarSolicitud(const string& solicitud) const {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            if (actual->solicitud == solicitud) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void mostrarSolicitudes() const {
        NodoLista* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->solicitud << endl;
            actual = actual->siguiente;
        }
    }
};

// Clase PilaSolicitudes
class PilaSolicitudes {
public:
    struct NodoPilaSolicitudes {
        string solicitud;
        NodoPilaSolicitudes* siguiente;
    };

    NodoPilaSolicitudes* tope;

    PilaSolicitudes() : tope(nullptr) {}

    void push(const string& solicitud) {
        NodoPilaSolicitudes* nuevoNodo = new NodoPilaSolicitudes{solicitud, tope};
        tope = nuevoNodo;
    }

    void pop() {
    if (tope) {
        cout << "Solicitud en el tope (dentro de pop): " << tope->solicitud << endl;
        NodoPilaSolicitudes* nodoAEliminar = tope;
        tope = tope->siguiente;
        delete nodoAEliminar;
        cout << "Nodo eliminado correctamente." << endl;
    } else {
        cout << "La pila está vacía, no se puede hacer pop." << endl;
    }
}


    bool estaVacia() const {
        return tope == nullptr;
    }

    string obtenerTope() const {
        return tope ? tope->solicitud : "";
    }

    bool buscarSolicitud(const string& solicitud) const {
        NodoPilaSolicitudes* actual = tope;
        while (actual != nullptr) {
            if (actual->solicitud == solicitud) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void mostrarSolicitudes() const {
        NodoPilaSolicitudes* actual = tope;
        while (actual != nullptr) {
            cout << actual->solicitud << endl;
            actual = actual->siguiente;
        }
    }
};

class NodoMatriz {
public:
    string nombre;
    NodoMatriz* siguiente;

    NodoMatriz(string n) : nombre(n), siguiente(nullptr) {}
};

class MatrizDispersa {
private:
    NodoMatriz* cabeza;

public:
    MatrizDispersa() : cabeza(nullptr) {}

    void agregarAmistad(const string& nombre1, const string& nombre2) {
        insertarNombre(nombre1);
        insertarNombre(nombre2);
        // Aquí puedes implementar la lógica adicional para actualizar la matriz dispersa.
        cout << "Amistad entre " << nombre1 << " y " << nombre2 << " agregada a la matriz dispersa." << endl;
    }

    NodoMatriz* buscarNodo(string nombre) {
        NodoMatriz* actual = cabeza;
        while (actual != nullptr) {
            if (actual->nombre == nombre) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    void insertarNombre(string nombre) {
        if (buscarNodo(nombre) == nullptr) {
            NodoMatriz* nuevo = new NodoMatriz(nombre);
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        }
    }
};

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

    bool tieneSolicitudPendiente(const string& correo) const {
        return solicitudesEnviadas.buscarSolicitud(correo) || solicitudesRecibidas.buscarSolicitud(correo);
    }

    // Método `enviarSolicitud` debe ser no constante
    void enviarSolicitud(Usuario& emisor, Usuario& receptor) {
        if (!emisor.tieneSolicitudPendiente(receptor.getCorreo()) && !receptor.tieneSolicitudPendiente(emisor.getCorreo())) {
            emisor.solicitudesEnviadas.agregarSolicitud(receptor.getCorreo());
            receptor.solicitudesRecibidas.push(emisor.getCorreo());
            cout<<"solicitud enviada con exito a "<< receptor.correo<<endl;
        } else {
            cout << "Ya existe una solicitud pendiente entre estos usuarios." << endl;
        }
    }

    void mostrarSolicitudesRecibidas() const {
        cout << "Solicitudes recibidas por " << nombre << ":" << endl;
        PilaSolicitudes copiaSolicitudesRecibidas = solicitudesRecibidas;  // Crear una copia para no modificar la pila original
        //while (!copiaSolicitudesRecibidas.estaVacia()) {
        cout << copiaSolicitudesRecibidas.obtenerTope() << endl;
            //copiaSolicitudesRecibidas.pop();
       // }
    }

    void aceptarSolicitud(Usuario* receptor, Usuario* emisor, MatrizDispersa& matriz) {
    if (receptor == nullptr) {
        cout << "Error: El puntero receptor es nulo." << endl;
        return;
    }

    if (emisor == nullptr) {
        cout << "Error: El puntero emisor es nulo." << endl;
        return;
    }

    cout << "Receptor: " << receptor->getNombre() << " (" << receptor->getCorreo() << ")" << endl;
    cout << "Emisor: " << emisor->getNombre() << " (" << emisor->getCorreo() << ")" << endl;

    // Verificar el estado de la pila antes de hacer pop
    cout << "Solicitud en el tope de la pila de solicitudes recibidas del receptor (antes de pop, estoy dentro de aceptar solicitud): " << receptor->solicitudesRecibidas.obtenerTope() << endl;

    // Eliminar la solicitud de ambas partes
    receptor->solicitudesRecibidas.pop();
    cout << "Solicitud eliminada de la pila de solicitudes recibidas del receptor." << endl;
    receptor->solicitudesEnviadas.eliminarSolicitud(emisor->getCorreo());

    emisor->solicitudesEnviadas.eliminarSolicitud(receptor->getCorreo());
    emisor->solicitudesRecibidas.pop();
    cout << "Solicitud eliminada de la pila de solicitudes recibidas del emisor." << endl;

    // Agregar la amistad a la matriz dispersa
    matriz.agregarAmistad(receptor->getNombre(), emisor->getNombre());

    cout << "Solicitud aceptada. Ahora son amigos." << endl;
}


    void rechazarSolicitud(Usuario* receptor, Usuario* emisor) {
        if (receptor && emisor) {
            // Verificar y depurar antes de hacer pop en solicitudesRecibidas
            if (!receptor->solicitudesRecibidas.estaVacia()) {
                cout << "Solicitud en el tope (antes de pop): " << receptor->solicitudesRecibidas.obtenerTope() << endl;
                receptor->solicitudesRecibidas.pop();
                cout << "Solicitud eliminada de solicitudesRecibidas." << endl;
            } else {
                cout << "Error: No hay solicitudes recibidas para eliminar en receptor." << endl;
            }

            // Eliminar solicitudes en la lista de enviadas del receptor
            receptor->solicitudesEnviadas.eliminarSolicitud(emisor->getCorreo());

            // Eliminar solicitudes en la lista de enviadas y recibidas del emisor
            emisor->solicitudesEnviadas.eliminarSolicitud(receptor->getCorreo());
            if (!emisor->solicitudesRecibidas.estaVacia()) {
                cout << "Solicitud en el tope (antes de pop): " << emisor->solicitudesRecibidas.obtenerTope() << endl;
                emisor->solicitudesRecibidas.pop();
                cout << "Solicitud eliminada de solicitudesRecibidas." << endl;
            } else {
                cout << "Error: No hay solicitudes recibidas para eliminar en emisor." << endl;
            }

            cout << "Solicitud rechazada." << endl;
        } else {
            cout << "Error: Usuario receptor o emisor no válido." << endl;
        }
    }

private:
    string nombre;
    string apellidos;
    string fechaNacimiento;
    string correo;
    string contrasenia;

    ListaSimpleSolicitudes solicitudesEnviadas;
    PilaSolicitudes solicitudesRecibidas;
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

    // Método para eliminar usuario por correo
    bool eliminarUsuario(const string& correo) {
        if (!cabeza) return false; // Lista vacía

        if (cabeza->usuario.getCorreo() == correo) {
            cabeza = move(cabeza->siguiente);
            return true;
        }

        Nodo* temp = cabeza.get();
        while (temp->siguiente && temp->siguiente->usuario.getCorreo() != correo) {
            temp = temp->siguiente.get();
        }

        if (temp->siguiente) {
            temp->siguiente = move(temp->siguiente->siguiente);
            return true;
        }

        return false; // Usuario no encontrado
    }
};


// Prototipos
void menu();
void menuUsuario(ListaEnlazada& lista, Usuario& usuarioConectado, MatrizDispersa& matriz, ListaDoblePublicaciones& listaPublicaciones);
void iniciarSesion(ListaEnlazada&, MatrizDispersa&, ListaDoblePublicaciones&);
void registro(ListaEnlazada&);
void menuAdmin();
void subMenuPerfil(ListaEnlazada& lista, const Usuario& usuarioConectado);
void subMenuSolicitudes( Usuario& usuarioConectado, ListaEnlazada& lista, MatrizDispersa& matriz);
void subMenuPublicaciones(Usuario& usuarioConectado, ListaDoblePublicaciones& listaPublicaciones);
void eliminarCuenta(ListaEnlazada& lista, const Usuario& usuarioConectado);

int main() {
    // Instancias de las clases
    ListaEnlazada listaUsuarios;
    MatrizDispersa matrizDispersa;
    //ListaDoblePublicaciones listaPublicaciones;

    menu();
    //system("pause");
    return 0;
}

//función del menú principal
void menu() {
    int opcion;
    //hago una instancia de listaEnlazada para acceder a sus métodos
    ListaEnlazada listaUsuarios;
    MatrizDispersa matriz;
    ListaDoblePublicaciones listaPublicaciones;

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
                iniciarSesion(listaUsuarios, matriz, listaPublicaciones);
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
void iniciarSesion(ListaEnlazada& lista, MatrizDispersa& matriz, ListaDoblePublicaciones& listaPublicaciones) {
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
            menuUsuario(lista, *usuario, matriz, listaPublicaciones);
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
void menuUsuario(ListaEnlazada& lista, Usuario& usuarioConectado, MatrizDispersa& matriz, ListaDoblePublicaciones& listaPublicaciones){
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
                subMenuSolicitudes(usuarioConectado, lista, matriz);
                cout << "\n";
                system("pause");
                break;
            case 3:
                cout << "---------Publicaciones---------" << endl;
                subMenuPublicaciones(usuarioConectado, listaPublicaciones);
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
void subMenuSolicitudes(Usuario& usuarioConectado, ListaEnlazada& listaUsuarios, MatrizDispersa& matriz) {
    char opcion;
    do {
        cout << "\ta. Ver solicitudes" << endl;
        cout << "\tb. Enviar" << endl;
        cout << "\tc. Aceptar solicitud" << endl;
        cout << "\td. Rechazar solicitud" << endl;
        cout << "\te. Volver" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion) {
            case 'a':
                cout << "---------Ver Solicitudes---------" << endl;
                usuarioConectado.mostrarSolicitudesRecibidas();
                break;
            case 'b':
                {
                cout << "---------Enviar Solicitud---------" << endl;
                string correoReceptor;
                cout << "Ingrese el correo del receptor: ";
                cin >> correoReceptor;
                Usuario* receptor = listaUsuarios.buscarUsuarioPorCorreo(correoReceptor);
                if (receptor) {
                    usuarioConectado.enviarSolicitud(usuarioConectado, *receptor);
                } else {
                    cout << "Usuario no encontrado." << endl;
                }
                system("pause");
                break;
            }
            case 'c':
                {
                cout << "---------Aceptar Solicitud---------" << endl;
                string correoEmisor;
                cout << "Ingrese el correo del emisor: ";
                cin >> correoEmisor;
                Usuario* emisor = listaUsuarios.buscarUsuarioPorCorreo(correoEmisor);
                if (emisor) {
                    usuarioConectado.aceptarSolicitud(&usuarioConectado, emisor, matriz);
                } else {
                    cout << "Usuario no encontrado." << endl;
                }
                system("pause");
                break;
            }
            case 'd':
                {
                cout << "---------Rechazar Solicitud---------" << endl;
                string correoEmisor;
                cout << "Ingrese el correo del emisor: ";
                cin >> correoEmisor;
                Usuario* emisor = listaUsuarios.buscarUsuarioPorCorreo(correoEmisor);
                if (emisor) {
                    usuarioConectado.rechazarSolicitud(&usuarioConectado, emisor);
                } else {
                    cout << "Usuario no encontrado." << endl;
                }
                system("pause");
                break;
            }
            case 'e':
                cout << "Saliendo del menu..." << endl;
                system("pause");
                break;
            default:
                cout << "Ingrese una opcion valida..." << endl;
                system("pause");
                break;
        }
    } while (opcion != 'e');
}

void crearPublicacion(Usuario& usuarioConectado, ListaDoblePublicaciones& listaPublicaciones) {
    string contenido;
    cout << "Ingrese el contenido de la publicacion: "; //cin.ignore();
    getline(cin, contenido);

    auto nuevaPublicacion = make_shared<Publicacion>(usuarioConectado.getCorreo(), contenido);
    listaPublicaciones.agregarPublicacion(nuevaPublicacion);

    cout << "Publicacion creada exitosamente." << endl;
    system("pause");
}


//sub-menú de publicaciones
void subMenuPublicaciones(Usuario& usuarioConectado, ListaDoblePublicaciones& listaPublicaciones){
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
            listaPublicaciones.mostrarPublicaciones();
            break;
        case 'b':
            cout << "---------Crear---------" << endl;
            crearPublicacion(usuarioConectado, listaPublicaciones);
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
        bool eliminado = lista.eliminarUsuario(usuarioConectado.getCorreo());

        if (eliminado) {
            cout << "Cuenta de " << usuarioConectado.getNombre() << " eliminada exitosamente." << endl;
            // Aquí puedes agregar lógica para redirigir al menú principal
            return;
        } else {
            cout << "No se encontró la cuenta para eliminar." << endl;
        }

        // Redirigir al menú principal después de eliminar la cuenta
        return;
    } else {
        cout << "Cancelando eliminación de cuenta." << endl;
    }
}


