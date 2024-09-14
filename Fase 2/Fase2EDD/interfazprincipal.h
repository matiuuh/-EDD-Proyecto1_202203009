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
    void llenarTablaSolicitudesRecibidas();
    void manejarSolicitud(const QModelIndex &index);
    void aceptarSolicitud(const std::string& correoRemitente);
    void rechazarSolicitud(const std::string& correoRemitente);
    //void llenarTablaSolicitudesRecibidas();
    //void aceptarSolicitud(const QString& correo);
    //void rechazarSolicitud(const QString& correo);

private:
    Ui::InterfazPrincipal *ui;
    QString correoConectado; // Variable para almacenar el correo del usuario conectado
};
#endif // INTERFAZPRINCIPAL_H
