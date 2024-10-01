#ifndef INTERFAZPRINCIPAL_H
#define INTERFAZPRINCIPAL_H
#include <QMainWindow>
#include "Publicaciones/publicacion.h"
#include "bstpublicaciones.h"

#include <queue>

QT_BEGIN_NAMESPACE
namespace Ui {
class InterfazPrincipal;
}
QT_END_NAMESPACE

struct FechaConteo {
    std::string fecha;
    int conteo;

    // Constructor
    FechaConteo(const std::string& fecha) : fecha(fecha), conteo(1) {}
};

class InterfazPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    InterfazPrincipal(QWidget *parent = nullptr, const QString& correoUsuario = "");
    ~InterfazPrincipal();

private slots:
    void cerrarSesion();  // Declaramos la función aquí

    //Solicitudes
    void llenarTablaUsuarios();
    void enviarSolicitud(const QString& correo, const std::string& correoConectado);
    void llenarTablaSolicitudesRecibidas();
    void manejarSolicitud(const QModelIndex &index);
    void aceptarSolicitud(const std::string& correoRemitente);
    void rechazarSolicitud(const std::string& correoRemitente);
    void manejarCancelacionSolicitud(const QModelIndex &index);
    void llenarTablaSolicitudesEnviadas();

    //Publicaciones
    void crearPublicacion();
    void mostrarPublicaciones();
    void aplicarFiltroFecha();
    void mostrarPublicacionesPorFecha(const QString& fechaFiltro);
    void mostrarPublicacionesConOrden(const QString& tipoOrden, int cantidad);
    void aplicarOrdenLimitado();

    //Comentarios
    void mostrarOpcionesPublicacion();

    //Perfil
    void modificarDatosPropios();
    void mostrarDatosUsuarioConectado() const;
    void eliminarUsuarioConectado();

    void buscarUsuarioCorreo();

    //Reportes
    void mostrarTopFechasPublicaciones();
    // Declaraciones de las funciones
    void contarPublicacionesPorFecha(const BSTPublicaciones& bst, std::queue<FechaConteo>& colaConteos);
    void ordenarTop3(std::queue<FechaConteo>& colaConteos);
    void mostrarTopFechas(std::queue<FechaConteo>& colaConteos);

    void generarGraficoBSTPorFecha();

    void eliminarPublicacion(const Publicacion& publicacion);
    void mostrarEliminar();

private:
    Ui::InterfazPrincipal *ui;
    QString correoConectado; // Variable para almacenar el correo del usuario conectado
    Publicacion* publicacionActual;  // Apunta a la publicación seleccionada actualmente
};
#endif // INTERFAZPRINCIPAL_H
