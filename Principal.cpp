#include <iostream>

using namespace std;

// Prototipos
void menu();
void iniciarSesion();
void registro();
void menuUsuario();
void menuAdmin();
void subMenuPerfil();
void subMenuSolicitudes();
void subMenuPublicaciones();

int main() {
    menu();

    system("pause");
    return 0;
}

void menu() {
    int opcion;

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
                registro();
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

void iniciarSesion(){
    
}

void registro() {
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

}

//función para mostrar el menú de usuario
void menuUsuario(){
    int opcion;
    do {
        cout << "\t-----Menu Usuario-----\n";
        cout << "\t1. Perfil" << endl;
        cout << "\t2. Solicitudes" << endl;
        cout << "\t3. Publicaciones" << endl;
        cout << "\t4. Reportes" << endl;
        cout << "\t5. Salir" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada después de leer un número

        switch (opcion) {
            case 1:
            cout<<"---------Perfil---------"<<endl;
                subMenuPerfil();
                cout << "\n";
                system("pause");
                break;
            case 2:
                cout<<"---------Solicitudes---------"<<endl;
                subMenuSolicitudes();
                cout << "\n";
                system("pause");
                break;
            case 3:
                cout << "---------Publicaciones---------" << endl;
                subMenuPublicaciones();
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
void subMenuPerfil(){
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
            system("pause");
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

//sub-menú de solicitudes
void subMenuSolicitudes(){
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
            system("pause");
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
void subMenuPublicaciones(){
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
            system("pause");
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
