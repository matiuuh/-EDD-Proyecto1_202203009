#include "comentario.h"

using namespace std;
#include <iostream>

Comentario::Comentario(const QString& correo, const QString& comentario)
    : correoUsuario(correo), contenido(comentario)
{
    // Obtener la fecha y hora actuales
    QDateTime fechaHoraActual = QDateTime::currentDateTime();//nos ayuda a encontrar la hora y fecha actules
    fecha = fechaHoraActual.date().toString("dd/MM/yyyy");
    hora = fechaHoraActual.time().toString("HH:mm:ss");

    // Depuración
    std::cout << "Comentario creado de: " << correo.toStdString() << " contenido: " << contenido.toStdString() << std::endl;
}

Comentario::Comentario() = default;  // Constructor predeterminado


QString Comentario::getCorreo() const {
    return correoUsuario;
}

QString Comentario::getContenido() const {
    return contenido;
}

QString Comentario::getFecha() const {
    return fecha;
}

QString Comentario::getHora() const {
    return hora;
}

QString Comentario::getFechaHora() const {
    QString fechaHora = fecha + hora;

    std::cout<<fechaHora.toStdString()<<std::endl;
    return fechaHora;
}
