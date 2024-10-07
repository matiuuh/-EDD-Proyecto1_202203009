#ifndef COMENTARIO_H
#define COMENTARIO_H

#include <QString>
#include <QDateTime>

class Comentario
{
public:
    Comentario(const QString& correo, const QString& comentario);

    Comentario();  // Constructor predeterminado


    // Getters
    QString getCorreo() const;
    QString getContenido() const;
    QString getFecha() const;
    QString getHora() const;
    QString getFechaHora() const;

private:
    QString correoUsuario;    // Correo del usuario que hizo el comentario
    QString contenido;        // Contenido del comentario
    QString fecha;            // Fecha del comentario
    QString hora;             // Hora del comentario
};

#endif // COMENTARIO_H
