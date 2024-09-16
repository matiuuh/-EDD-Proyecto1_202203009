#include "publicacion.h"

Publicacion::Publicacion(const QString& correo, const QString& contenido)
    : correoUsuario(correo), contenido(contenido)
{
    // Obtener la fecha y hora actuales
    QDateTime fechaHoraActual = QDateTime::currentDateTime();
    fecha = fechaHoraActual.date().toString("dd/MM/yyyy");
    hora = fechaHoraActual.time().toString("HH:mm:ss");
}

QString Publicacion::getCorreo() const {
    return correoUsuario;
}

QString Publicacion::getContenido() const {
    return contenido;
}

QString Publicacion::getFecha() const {
    return fecha;
}

QString Publicacion::getHora() const {
    return hora;
}

void Publicacion::setContenido(const QString& contenido) {
    this->contenido = contenido;
}

void Publicacion::agregarComentario(const Comentario& comentario) {
    arbolComentarios.insertar(comentario);  // Aquí usas el método de tu árbol B
}

// Nuevo método para establecer la imagen
void Publicacion::setImagen(const QString& rutaImagen) {
    this->imagen = rutaImagen;
}

QString Publicacion::getImagen() const {
    return imagen;
}

void Publicacion::setFecha(const QString& fecha) {
    this->fecha = fecha;  // Establecer la fecha manualmente
}

void Publicacion::setHora(const QString& hora) {
    this->hora = hora;  // Establecer la hora manualmente
}
