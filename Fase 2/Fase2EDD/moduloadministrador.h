#ifndef MODULOADMINISTRADOR_H
#define MODULOADMINISTRADOR_H

#include <QDockWidget>

namespace Ui {
class ModuloAdministrador;
}

class ModuloAdministrador : public QDockWidget
{
    Q_OBJECT

public:
    explicit ModuloAdministrador(QWidget *parent = nullptr);
    ~ModuloAdministrador();

private slots:
    void cerrarSesion();  // Declaramos la función aquí

private:
    Ui::ModuloAdministrador *ui;
};

#endif // MODULOADMINISTRADOR_H
