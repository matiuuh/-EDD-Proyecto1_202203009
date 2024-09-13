#include "moduloentrada.h"
#include "ui_moduloentrada.h"
#include "moduloadministrador.h"  // Incluir la clase del módulo administrador
#include "registrousuario.h"  // Incluir la clase del módulo administrador
#include <QMessageBox>  // Para mostrar mensajes de error o éxito
#include <iostream>     /* Para mostrar en consola  */
#include <string>       /* Para manejar cadenas de texto */

ModuloEntrada::ModuloEntrada(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ModuloEntrada)
{
    ui->setupUi(this);

    // Conectar el botón "Iniciar" con la función de verificación
    connect(ui->btn_iniciar, &QPushButton::clicked, this, &ModuloEntrada::verificarCredenciales);

    // Conectar el botón "Iniciar" con la función de verificación
    connect(ui->btn_registrar, &QPushButton::clicked, this, &ModuloEntrada::registrarUsuario);

}

ModuloEntrada::~ModuloEntrada()
{
    delete ui;
}

// Función para verificar las credenciales ingresadas por el usuario
void ModuloEntrada::verificarCredenciales()
{
    // Obtener el correo y la contraseña ingresados
    QString correo = ui->txt_correo->toPlainText();
    QString contrasenia = ui->txt_contrasenia->toPlainText();

    // Aquí debes implementar la lógica para verificar el correo y la contraseña.
    // Suponiendo que tienes una lista de usuarios o base de datos:

    if (correo.isEmpty() || contrasenia.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor ingresa tu correo y contraseña.");
        return;
    }else if(correo == "admin" && contrasenia == "admin"){
        // Si las credenciales son de administrador, abrir el módulo de administrador
        ModuloAdministrador *adminWindow = new ModuloAdministrador(nullptr);
        adminWindow->show();  // Mostrar la ventana del módulo administrador
        this->close();  // Cerrar la ventana actual (opcional)
        return;
    }
}

void ModuloEntrada::registrarUsuario(){
    RegistroUsuario *abrirRegistro= new RegistroUsuario(nullptr);
    abrirRegistro->show();  // Mostrar la ventana del módulo administrador
    this->close();  // Cerrar la ventana actual (opcional)
    return;
}
