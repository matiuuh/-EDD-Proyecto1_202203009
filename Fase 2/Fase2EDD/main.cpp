#include "interfazprincipal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfazPrincipal w;
    w.show();
    return a.exec();
}
