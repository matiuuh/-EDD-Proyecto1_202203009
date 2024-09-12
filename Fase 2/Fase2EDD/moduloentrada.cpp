#include "moduloentrada.h"
#include "ui_moduloentrada.h"

ModuloEntrada::ModuloEntrada(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ModuloEntrada)
{
    ui->setupUi(this);
}

ModuloEntrada::~ModuloEntrada()
{
    delete ui;
}
