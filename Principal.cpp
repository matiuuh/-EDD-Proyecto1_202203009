
#include <iostream>
#include <stdlib.h>

using namespace std;

//prototipos
void menu();

int main(){
    menu();
    system("pause");
    return 0;
}

void menu(){
    int opcion;

    do{
        cout << "\t-----Menu-----\n";
        cout << "\t1. Iniciar sesion" << endl;
        cout << "\t2. Registrarse" << endl;
        cout << "\t3. Informacion" << endl;
        cout << "\t4. Salir" << endl;
        cout << "\tIngrese opcion: "; cin >> opcion;

        switch (opcion) {
            case 1:
                cout<<"\n";
                system("pause");
                break;
            case 2:
                cout<<"\n";
                system("pause");
                break;
            case 3:
                cout<<"Nombre: Mateo Estuardo Diego Noriega"<<endl;
                cout<<"Carnet: 202203009"<<endl;
                cout<<"Link del repositorio: https://github.com/matiuuh/-EDD-Proyecto1_202203009.git";
                cout<<"\n";
                system("pause");
                break;
            case 4:
                cout<<"saliendo del programa ";
                break;
            default:
                cout << "Ingrese una opcion valida. ";
                system("pause");
                break;
        }
        system("cls");
    }while(opcion!=4);
    
}