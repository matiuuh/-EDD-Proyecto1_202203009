#include "moduloentrada.h"
#include "ui_moduloentrada.h"
#include "moduloadministrador.h"  // Incluir la clase del módulo administrador
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


    // Ejemplo básico de cómo podrías verificar los usuarios.
    // Aquí usarías tu estructura de datos o clase de usuarios para hacer la validación.
    // Supongamos que tienes un método como verificarUsuario(correo, contrasenia)

    bool loginExitoso = false;  // Cambia esto según tu lógica de verificación
    // loginExitoso = verificarUsuario(correo.toStdString(), contrasenia.toStdString());

    // Si el login es exitoso
    if (loginExitoso) {
        QMessageBox::information(this, "Login Exitoso", "¡Bienvenido!");
        // Aquí podrías redirigir a la siguiente ventana o sección de la aplicación
    } else {
        QMessageBox::warning(this, "Error", "Correo o contraseña incorrectos.");
    }
}
