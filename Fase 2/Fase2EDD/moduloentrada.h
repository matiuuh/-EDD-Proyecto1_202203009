#ifndef MODULOENTRADA_H
#define MODULOENTRADA_H

#include <QDockWidget>

namespace Ui {
class ModuloEntrada;
}

class ModuloEntrada : public QDockWidget
{
    Q_OBJECT

public:
    explicit ModuloEntrada(QWidget *parent = nullptr);
    ~ModuloEntrada();

private:
    Ui::ModuloEntrada *ui;
};

#endif // MODULOENTRADA_H
