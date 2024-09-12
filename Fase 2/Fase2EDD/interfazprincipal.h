#ifndef INTERFAZPRINCIPAL_H
#define INTERFAZPRINCIPAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class InterfazPrincipal;
}
QT_END_NAMESPACE

class InterfazPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    InterfazPrincipal(QWidget *parent = nullptr);
    ~InterfazPrincipal();

private:
    Ui::InterfazPrincipal *ui;
};
#endif // INTERFAZPRINCIPAL_H
