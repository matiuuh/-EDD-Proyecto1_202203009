#include "moduloentrada.h"
//#include "Oficial.cpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModuloEntrada w;
    //ListaRelacionesCompleto listaRelaciones;  // Inicializar tus clases

    w.show();
    return a.exec();
}
