#ifndef GESTORCOMENTARIOS_H
#define GESTORCOMENTARIOS_H

#include <QDockWidget>
#include "Publicaciones/publicacion.h"

namespace Ui {
class GestorComentarios;
}

class GestorComentarios : public QDockWidget
{
    Q_OBJECT

public:
    explicit GestorComentarios(QWidget *parent = nullptr, const QString& correoConectado = "", Publicacion* publicacion = nullptr);
    ~GestorComentarios();

private slots:
    void regresar();  // Declaramos la función aquí
    void comentar();  // Declaramos la función aquí
    void verComentarios();  // Declaramos la función aquí
    void verArbolComentarios();  // Declaramos la función aquí

private:
    Ui::GestorComentarios *ui;
    QString correoConectado;  // Almacenar el correo del usuario conectado
    Publicacion* publicacionActual;  // Almacenar la publicación seleccionada
};

#endif // GESTORCOMENTARIOS_H
