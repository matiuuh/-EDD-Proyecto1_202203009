// VentanaEmergente.cpp
#include "VentanaEmergente.h"
#include <QVBoxLayout>

VentanaEmergente::VentanaEmergente(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    lineEditEmail = new QLineEdit(this);
    lineEditEmail->setPlaceholderText("Ingrese el correo electrónico del usuario");

    btnAceptar = new QPushButton("Aceptar", this);
    btnCancelar = new QPushButton("Cancelar", this);

    layout->addWidget(lineEditEmail);
    layout->addWidget(btnAceptar);
    layout->addWidget(btnCancelar);

    connect(btnAceptar, &QPushButton::clicked, this, &VentanaEmergente::accept);
    connect(btnCancelar, &QPushButton::clicked, this, &VentanaEmergente::reject);
}

QString VentanaEmergente::getEmail() const {
    return lineEditEmail->text();
}
