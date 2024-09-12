#include "moduloadministrador.h"
#include "ui_moduloadministrador.h"
#include "moduloentrada.h"

ModuloAdministrador::ModuloAdministrador(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ModuloAdministrador)
{
    ui->setupUi(this);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_cerrarSesion, &QPushButton::clicked, this, &ModuloAdministrador::cerrarSesion);

}

ModuloAdministrador::~ModuloAdministrador()
{
    delete ui;
}

// Función para manejar el cierre de sesión
void ModuloAdministrador::cerrarSesion()
{
    // Crear una nueva instancia del módulo de entrada
    ModuloEntrada *entrada = new ModuloEntrada(nullptr);
    entrada->show();  // Mostrar la ventana del módulo de entrada

    // Cerrar la ventana actual (ModuloAdministrador)
    this->close();  // También podrías usar `delete this` si quieres eliminar esta instancia completamente
}
