#include "ModificarUsuarioDialog.h"

ModificarUsuarioDialog::ModificarUsuarioDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Modificar Usuario");

    // Crear los cuadros de texto para los campos
    nombreLineEdit = new QLineEdit(this);
    apellidoLineEdit = new QLineEdit(this);
    correoLineEdit = new QLineEdit(this);
    contraseniaLineEdit = new QLineEdit(this);
    fechaNacimientoLineEdit = new QLineEdit(this);

    // Botones de Aceptar y Cancelar
    QPushButton *btnAceptar = new QPushButton("Aceptar", this);
    QPushButton *btnCancelar = new QPushButton("Cancelar", this);

    // Conectar los botones a sus funciones
    connect(btnAceptar, &QPushButton::clicked, this, &ModificarUsuarioDialog::onAceptar);
    connect(btnCancelar, &QPushButton::clicked, this, &QDialog::reject);

    // Layout para los campos
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Nombre:", nombreLineEdit);
    formLayout->addRow("Apellido:", apellidoLineEdit);
    formLayout->addRow("Correo:", correoLineEdit);
    formLayout->addRow("Contraseña:", contraseniaLineEdit);
    formLayout->addRow("Fecha de Nacimiento:", fechaNacimientoLineEdit);

    // Layout para los botones
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(btnAceptar);
    buttonLayout->addWidget(btnCancelar);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void ModificarUsuarioDialog::onAceptar() {
    // Aquí puedes realizar las validaciones necesarias antes de aceptar
    accept();  // Cierra el diálogo y regresa el control
}

// Funciones para obtener los valores ingresados
QString ModificarUsuarioDialog::getNombre() const {
    return nombreLineEdit->text();
}

QString ModificarUsuarioDialog::getApellido() const {
    return apellidoLineEdit->text();
}

QString ModificarUsuarioDialog::getCorreo() const {
    return correoLineEdit->text();
}

QString ModificarUsuarioDialog::getContrasenia() const {
    return contraseniaLineEdit->text();
}

QString ModificarUsuarioDialog::getFechaNacimiento() const {
    return fechaNacimientoLineEdit->text();
}
