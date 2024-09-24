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
        std::cout << "publicacionActual es nulo.";
        return;
    }

    // Verificar si el comentario está vacío
    if (contenidoComentario.isEmpty()) {
        QMessageBox::warning(this, "Error", "El comentario no puede estar vacío.");
        return;
    }

    // Verificación: comprobar si se agregó al árbol
    std::cout << "crear nuevo comentario";
    // Asegúrate de que correoConectado esté definido
    std::cout << "Usuario conectado: " << correoConectado.toStdString() << std::endl;


    // Crear un nuevo comentario
    auto comentario = std::make_shared<Comentario>(correoConectado, contenidoComentario);

    std::cout << "crea el objeto" << std::endl;

    // Agregar el comentario al árbol de la publicación actual
    publicacionActual->getArbolComentarios().insertar(comentario); // Cambiado a usar el método insertar

    // Verificación: comprobar si se agregó al árbol
    std::cout << "Árbol de comentarios después de agregar el comentario:" << std::endl;

    // Mostrar el árbol de comentarios en consola para depuración
    publicacionActual->getArbolComentarios().mostrarTodosLosComentarios(); // Aquí se llama a mostrar todos los comentarios

    // Limpiar el campo de texto después de agregar el comentario
    ui->txt_comentario->clear();

    // Informar al usuario que el comentario fue agregado
    QMessageBox::information(this, "Éxito", "Comentario agregado exitosamente.");
}

void GestorComentarios::verComentarios()
{
}

void GestorComentarios::verArbolComentarios()
{
    qDebug() << "Dirección de memoria de publicacionActual en verArbolComentarios(): " << publicacionActual;
}

