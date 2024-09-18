#include "gestorcomentarios.h"
#include "ui_gestorcomentarios.h"
#include "interfazprincipal.h"
#include <QDebug>  // Incluye QDebug para imprimir en consola
#include <iostream>
#include <QMessageBox>
#include <QHBoxLayout>

GestorComentarios::GestorComentarios(QWidget *parent, const QString& correoConectado, Publicacion* publicacion)
    : QDockWidget(parent)
    , ui(new Ui::GestorComentarios)
    , correoConectado(correoConectado)  // Inicializar el correo del usuario conectado
    , publicacionActual(publicacion)  // Inicializar la publicación seleccionada
{
    ui->setupUi(this);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_regresar, &QPushButton::clicked, this, &GestorComentarios::regresar);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_comentar, &QPushButton::clicked, this, &GestorComentarios::comentar);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_verComentarios, &QPushButton::clicked, this, &GestorComentarios::verComentarios);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_verArbolComentarios, &QPushButton::clicked, this, &GestorComentarios::verArbolComentarios);

}

GestorComentarios::~GestorComentarios()
{
    delete ui;
}


// Función para manejar el cierre de sesión
void GestorComentarios::regresar()
{
    // Crear una nueva instancia del módulo de entrada
    InterfazPrincipal *salir = new InterfazPrincipal(nullptr, correoConectado);
    salir->show();  // Mostrar la ventana del módulo de entrada

    // Cerrar la ventana actual (ModuloAdministrador)
    this->close();  // También podrías usar `delete this` si quieres eliminar esta instancia completamente
}

void GestorComentarios::comentar()
{
    // Obtener el texto del campo de comentario
    QString contenidoComentario = ui->txt_comentario->toPlainText();

    if (!publicacionActual) {
        qDebug() << "publicacionActual es nulo.";
        return;
    }

    // Verificar si el comentario está vacío
    if (contenidoComentario.isEmpty()) {
        QMessageBox::warning(this, "Error", "El comentario no puede estar vacío.");
        return;
    }

    // Crear un nuevo comentario
    Comentario comentario(correoConectado, contenidoComentario);

    // Agregar el comentario al árbol de la publicación actual
    publicacionActual->agregarComentario(comentario);

    // Verificación: comprobar si se agregó al árbol
    std::cout << "Árbol de comentarios después de agregar el comentario:"<<std::endl;

    // Mostrar el árbol de comentarios en consola para depuración
    publicacionActual->getArbolComentarios().mostrar();
    std::cout << "aqui si sale bro." << std::endl;
    //publicacionActual->getArbolComentarios().mostrarTodosLosComentarios();

    // Limpiar el campo de texto después de agregar el comentario
    ui->txt_comentario->clear();

    // Informar al usuario que el comentario fue agregado
    QMessageBox::information(this, "Éxito", "Comentario agregado exitosamente.");
}

void GestorComentarios::verComentarios()
{
    if (!publicacionActual) {
        QMessageBox::warning(this, "Error", "No hay ninguna publicación seleccionada.");
        return;
    }

    // Depuración: Imprimir la dirección de memoria de publicacionActual
    std::cout << "Instancia de publicacionActual en verComentarios: " << publicacionActual << std::endl;

    // Obtener los comentarios de la publicación
    std::vector<Comentario> comentarios = publicacionActual->getArbolComentarios().listarComentarios();

    // Depuración: Verificar si se obtuvieron los comentarios correctamente
    std::cout << "Cantidad de comentarios obtenidos: " << comentarios.size() << std::endl;


    // Crear un diálogo para mostrar los comentarios
    QDialog dialog(this);
    QVBoxLayout layout(&dialog);

    if (comentarios.empty()) {
        layout.addWidget(new QLabel("No hay comentarios disponibles.", &dialog)); // Mostrar un mensaje si no hay comentarios
    } else {
        for (const Comentario& comentario : comentarios) {
            QString textoComentario = QString("%1: %2")
            .arg(comentario.getCorreo(), comentario.getContenido());
            layout.addWidget(new QLabel(textoComentario, &dialog));
        }
    }

    QPushButton *btnCerrar = new QPushButton("Cerrar", &dialog);
    layout.addWidget(btnCerrar);
    dialog.setLayout(&layout);

    // Conectar el botón "Cerrar" para cerrar el diálogo
    connect(btnCerrar, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();
}

void GestorComentarios::verArbolComentarios()
{
    qDebug() << "Dirección de memoria de publicacionActual en verArbolComentarios(): " << publicacionActual;
}

