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
    InterfazPrincipal(QWidget *parent = nullptr, const QString& correoUsuario = "");
    ~InterfazPrincipal();

private slots:
    void cerrarSesion();  // Declaramos la función aquí
    void llenarTablaUsuarios();
    void enviarSolicitud(const QString& correo, const std::string& correoConectado);

private:
    Ui::InterfazPrincipal *ui;
    QString correoConectado; // Variable para almacenar el correo del usuario conectado
};
#endif // INTERFAZPRINCIPAL_H
