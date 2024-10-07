#ifndef NUEVAPUBLICACION_H
#define NUEVAPUBLICACION_H

#include <QDockWidget>

namespace Ui {
class NuevaPublicacion;
}

class NuevaPublicacion : public QDockWidget
{
    Q_OBJECT

public:
    explicit NuevaPublicacion(QWidget *parent = nullptr, const QString& correoUsuario = "");
    ~NuevaPublicacion();

private slots:
    void regresar();  // Declaramos la función aquí
    void publicar();   // Función para crear la publicación
    void cargarImagen(); // Función para cargar una imagen

private:
    Ui::NuevaPublicacion *ui;
    QString correoConectado; // Variable para almacenar el correo del usuario conectado
    QString rutaImagenGuardada;   // Almacena la ruta de la imagen cargada
};

#endif // NUEVAPUBLICACION_H
