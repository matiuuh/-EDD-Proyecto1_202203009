#include "interfazprincipal.h"
//#include "Oficial.cpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfazPrincipal w;
    //ListaRelacionesCompleto listaRelaciones;  // Inicializar tus clases

    w.show();
    return a.exec();
}
