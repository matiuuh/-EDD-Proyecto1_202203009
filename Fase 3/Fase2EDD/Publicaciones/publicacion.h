#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <QString>
#include <QDateTime>
#include "Comentarios/arbolbcomentarios.h"   // Aquí deberías tener la implementación del árbol B
//#include "Comentarios/arbolavlcomentarios.h"
#include "Comentarios/listadoblecomentariosaux.h"

class Publicacion
{
public:
    Publicacion(const QString& correo, const QString& contenido);

    // Getters y setters
    QString getCorreo() const;
    QString getContenido() const;
    QString getFecha() const;
    QString getHora() const;
    QString getImagen() const;
    QString getNombreUsuario() const;

    //void agregarComentario(const Comentario& comentario);

    //Publicaciones
    void setContenido(const QString& contenido);
    void setFecha(const QString& fecha);  // Método para establecer la fecha
    void setHora(const QString& hora);    // Método para establecer la hora
    void setImagen(const QString& rutaImagen);

    void listarComentarios();
    ArbolBComentarios& getArbolComentarios();
    //const ListaDobleComentariosAux& getListaComentarios() const;
    ListaDobleComentariosAux& getListaComentarios(); // Para modificación

private:
    QString correoUsuario;      // Correo del usuario que crea la publicación
    QString contenido;          // Texto de la publicación
    QString fecha;              // Fecha de creación
    QString hora;               // Hora de creación
    QString imagen;  // Variable miembro para almacenar la ruta de la imagen
    ArbolBComentarios arbolComentarios;  // Árbol B que almacena los comentarios
    ListaDobleComentariosAux listaAux;
};

#endif // PUBLICACION_H
