#include "nuevapublicacion.h"
#include "ui_nuevapublicacion.h"
#include "interfazprincipal.h"
#include "Publicaciones/publicacion.h"
#include "usuario.h"
#include "EstructurasAdmin/avlusuarios.h"
#include "EstructurasAdmin/listadoblepublicacionesglobal.h"
#include "listadoble.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTextCursor>
#include <QTextImageFormat>
#include <QDateTime>

NuevaPublicacion::NuevaPublicacion(QWidget *parent, const QString& correoUsuario)
    : QDockWidget(parent)
    , ui(new Ui::NuevaPublicacion)
    , correoConectado(correoUsuario)  // Almacenar el correo del usuario conectado
{
    ui->setupUi(this);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_regresar, &QPushButton::clicked, this, &NuevaPublicacion::regresar);
    connect(ui->btn_publicar, &QPushButton::clicked, this, &NuevaPublicacion::publicar);
    connect(ui->btn_imagen, &QPushButton::clicked, this, &NuevaPublicacion::cargarImagen);
}

NuevaPublicacion::~NuevaPublicacion()
{
    delete ui;
}

// Función para manejar el cierre de sesión
void NuevaPublicacion::regresar()
{
    InterfazPrincipal *salir = new InterfazPrincipal(nullptr, correoConectado);
    salir->show();

    this->close();
}

// Función para cargar una imagen
void NuevaPublicacion::cargarImagen()
{
    QString rutaImagen = QFileDialog::getOpenFileName(this, tr("Cargar Imagen"), "", tr("Imágenes (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (!rutaImagen.isEmpty()) {
        // Insertar la imagen en el QTextEdit como HTML
        QTextCursor cursor = ui->txt_entradaPublicacion->textCursor();
        QTextImageFormat imageFormat;
        imageFormat.setName(rutaImagen);
        cursor.insertImage(imageFormat);

        // Guardar la ruta de la imagen para la publicación
        rutaImagenGuardada = rutaImagen;
    }
}

// Función para crear y almacenar la publicación
void NuevaPublicacion::publicar()
{
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    // Capturar el texto del editor
    QString textoPublicacion = ui->txt_entradaPublicacion->toPlainText();

    // Validar que el campo de texto no esté vacío
    if (textoPublicacion.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "La publicación no puede estar vacía.");
        return;
    }

    // Capturar la fecha y hora actuales
    QDateTime fechaHoraActual = QDateTime::currentDateTime();
    QString fecha = fechaHoraActual.date().toString("dd/MM/yyyy");
    QString hora = fechaHoraActual.time().toString("HH:mm:ss");

    // Crear una nueva publicación y establecer sus propiedades
    Publicacion nuevaPublicacion(correoConectado, textoPublicacion);
    nuevaPublicacion.setFecha(fecha);
    nuevaPublicacion.setHora(hora);

    // Verificar si se cargó una imagen
    if (!rutaImagenGuardada.isEmpty()) {
        nuevaPublicacion.setImagen(rutaImagenGuardada);
    }

    // Ahora almacenamos la publicación en las tres estructuras:

    ListaDoblePublicacionesGlobal& listaPublicacionesGlobal = ListaDoblePublicacionesGlobal::getInstance();

    // Insertar la publicación en la lista global de publicaciones
    listaPublicacionesGlobal.insertar(nuevaPublicacion);
    listaPublicacionesGlobal.mostrar();

    // Insertar la publicación en la lista de publicaciones del usuario conectado
    //usuarioConectado->getListaPublicacionesPropias().insertar(nuevaPublicacion);

    // Ahora almacenamos la publicación en el BST de publicaciones del usuario y amigos
    //usuarioConectado->getBSTPublicacionesAmigos().insertar(nuevaPublicacion);

    // Confirmar que la publicación se ha creado correctamente
    QMessageBox::information(this, "Éxito", "Tu publicación ha sido creada.");

    // Limpiar el formulario o cerrar la ventana
    this->close();
}
