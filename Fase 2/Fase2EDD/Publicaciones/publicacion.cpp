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
    // Convertir el comentario a shared_ptr
    auto comentarioPtr = std::make_shared<Comentario>(comentario);
    arbolComentarios.insertar(comentarioPtr);  // Aquí usas el método de tu árbol B
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

QString Publicacion::getNombreUsuario() const {
    return correoUsuario; // O el nombre del campo que desees retornar
}

void Publicacion::listarComentarios() {
    arbolComentarios.mostrarTodosLosComentarios();  // Esto debería mostrar todos los comentarios en orden
}

ArbolBComentarios& Publicacion::getArbolComentarios() {
    return arbolComentarios;
}
