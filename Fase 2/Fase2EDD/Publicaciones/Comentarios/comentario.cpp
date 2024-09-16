#include "comentario.h"

Comentario::Comentario(const QString& correo, const QString& comentario)
    : correoUsuario(correo), contenido(comentario)
{
    // Obtener la fecha y hora actuales
    QDateTime fechaHoraActual = QDateTime::currentDateTime();
    fecha = fechaHoraActual.date().toString("dd/MM/yyyy");
    hora = fechaHoraActual.time().toString("HH:mm:ss");
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
