#ifndef REGISTROUSUARIO_H
#define REGISTROUSUARIO_H

#include <QDockWidget>
#include <QMessageBox>
#include <regex>
#include "EstructurasAdmin/avlusuarios.h"

namespace Ui {
class RegistroUsuario;
}

class RegistroUsuario : public QDockWidget
{
    Q_OBJECT

public:
    explicit RegistroUsuario(QWidget *parent = nullptr);
    ~RegistroUsuario();

private slots:
    void regresar();  // Asegúrate de que esta línea esté presente
    void registrarUsuario();  // Método para manejar el registro de usuarios

private:
    Ui::RegistroUsuario *ui;
};

#endif // REGISTROUSUARIO_H
