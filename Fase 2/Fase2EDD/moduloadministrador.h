#ifndef MODULOADMINISTRADOR_H
#define MODULOADMINISTRADOR_H

#include <QDockWidget>
#include <QFileDialog>  // Incluir para abrir el explorador de archivos


namespace Ui {
class ModuloAdministrador;
}

class ModuloAdministrador : public QDockWidget
{
    Q_OBJECT

public:
    explicit ModuloAdministrador(QWidget *parent = nullptr);
    ~ModuloAdministrador();

private slots:
    void cerrarSesion();  // Declaramos la función aquí

    //---------------------PUBLICACIONES--------------------
    void cargarPublicaciones();  // Agregar la nueva función para cargar usuarios
    void btn_importarPublicaciones_Click(const std::string& rutaArchivoJSON);
    void importarPublicaciones();

    //-------------USUARIOS----------------
    void importarUsuarios();  // Agregar la nueva función para cargar usuarios
    void cargarUsuarios();  // Agregar la nueva función para cargar usuarios
    void btn_importarUsuarios_Click(const std::string& rutaArchivoJSON);  // Declaración del método

    //--------------SOLICITUDES----------------
    void importarSolicitudes();
    void btn_importarSolicitudes_Click(const std::string& rutaArchivoJSON);
    void cargarSolicitudes();  // Agregar la nueva función para cargar usuarios

    //********************BUSCAR**********************
    void buscarUsuarioPorCorreo();
    //void mostrarUsuariosOrdenados();
    //void setupConnections();
    void mostrarUsuariosEnTabla();

    void aplicarRecorridos();

private:
    Ui::ModuloAdministrador *ui;
};

#endif // MODULOADMINISTRADOR_H
