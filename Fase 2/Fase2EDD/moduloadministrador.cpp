#include "moduloadministrador.h"
#include "ui_moduloadministrador.h"

ModuloAdministrador::ModuloAdministrador(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ModuloAdministrador)
{
    ui->setupUi(this);
}

ModuloAdministrador::~ModuloAdministrador()
{
    delete ui;
}
