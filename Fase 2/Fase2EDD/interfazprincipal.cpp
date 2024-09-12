#include "interfazprincipal.h"
#include "./ui_interfazprincipal.h"

InterfazPrincipal::InterfazPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfazPrincipal)
{
    ui->setupUi(this);
}

InterfazPrincipal::~InterfazPrincipal()
{
    delete ui;
}
