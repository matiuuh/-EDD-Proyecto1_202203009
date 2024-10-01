#include "interfazprincipal.h"
#include "./ui_interfazprincipal.h"
#include "moduloentrada.h"
#include "EstructurasAdmin/avlusuarios.h"
#include "pila.h"
#include "listasimple.h"
#include "TablasModUsuario/buttondelegatesolicitudes.h"
#include "TablasModUsuario/buttondelegateenviadas.h"
#include "EstructurasUsuario/matrizdispersaamigos.h"
#include "nuevapublicacion.h"
#include "bstpublicaciones.h"
#include "gestorcomentarios.h"
#include "TablasModUsuario/buttondelegateeliminardef.h"

#include <regex>
#include <QStandardItemModel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QMessageBox>  // Para mostrar mensajes de error o éxito
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QLineEdit>
#include <iostream>  // Para utilizar cout
#include <queue>
#include <string>
#include <fstream>

InterfazPrincipal::InterfazPrincipal(QWidget *parent, const QString& correoUsuario)
    : QMainWindow(parent)
    , ui(new Ui::InterfazPrincipal)
    , correoConectado(correoUsuario)  // Almacenar el correo del usuario conectado
{
    ui->setupUi(this);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_cerrar, &QPushButton::clicked, this, &InterfazPrincipal::cerrarSesion);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_crearPublicacion, &QPushButton::clicked, this, &InterfazPrincipal::crearPublicacion);

    //Conectar el botón "Aplicar" para aplicar filtro de fecha
    connect(ui->btn_aplicarFecha, &QPushButton::clicked, this, &InterfazPrincipal::aplicarFiltroFecha);

    //Conectar el botón "Aplicar" para aplicar filtro de fecha
    connect(ui->btn_aplicarRecorridoLimitado, &QPushButton::clicked, this, &InterfazPrincipal::aplicarOrdenLimitado);

    //Conectar el botón "Aplicar" para aplicar filtro de fecha
    connect(ui->btn_modificarDatos, &QPushButton::clicked, this, &InterfazPrincipal::modificarDatosPropios);

    //Conectar el botón "Aplicar" para aplicar filtro de fecha
    connect(ui->btn_eliminarCuenta, &QPushButton::clicked, this, &InterfazPrincipal::eliminarUsuarioConectado);

    //Conectar el botón "Aplicar" para aplicar filtro de fecha
    connect(ui->btn_buscarUsuarioCorreo, &QPushButton::clicked, this, &InterfazPrincipal::buscarUsuarioCorreo);

    //Conectar el botón "Aplicar" para aplicar filtro de fecha
    connect(ui->btn_generarBSTGrafica, &QPushButton::clicked, this, &InterfazPrincipal::generarGraficoBSTPorFecha);

    // Llenar la tabla de usuarios cuando se abre la ventana
    llenarTablaUsuarios();  // Aquí llamamos al método para llenar la tabla
    llenarTablaSolicitudesRecibidas();
    llenarTablaSolicitudesEnviadas();
    mostrarPublicaciones();
    mostrarDatosUsuarioConectado();
    mostrarTopFechasPublicaciones();
    mostrarEliminar();
}

InterfazPrincipal::~InterfazPrincipal()
{
    delete ui;
}

// Función para manejar el cierre de sesión
void InterfazPrincipal::cerrarSesion()
{
    // Crear una nueva instancia del módulo de entrada
    ModuloEntrada *entrada = new ModuloEntrada(nullptr);
    entrada->show();  // Mostrar la ventana del módulo de entrada

    // Cerrar la ventana actual (ModuloAdministrador)
    this->close();  // También podrías usar `delete this` si quieres eliminar esta instancia completamente
}

class ButtonDelegate : public QStyledItemDelegate {
public:
    ButtonDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const override {
        QPushButton *button = new QPushButton(parent);
        button->setText("Enviar Solicitud");
        return button;
    }

    void setEditorData(QWidget *, const QModelIndex &) const override {
        // No es necesario cargar datos para el botón
    }

    void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const override {
        // No es necesario manejar cambios de datos para el botón
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const override {
        editor->setGeometry(option.rect);
    }
};

//*******************************SOLICITUDES***********************************
//----------PARA LA TABLA DE USUARIOS DE ENVIAR SOLICITUD---------------
void InterfazPrincipal::llenarTablaUsuarios() {
    AVLUsuarios& avl = AVLUsuarios::getInstance();
    ListaDobleUsuariosDisponibles listaUsuariosDisponibles;

    avl.obtenerUsuariosDisponibles(listaUsuariosDisponibles, correoConectado.toStdString());

    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels(QStringList() << "Correo de Usuario" << "Acciones");

    std::shared_ptr<NodoUsuario> nodo = listaUsuariosDisponibles.obtenerPrimero();
    while (nodo) {
        QList<QStandardItem*> fila;
        QStandardItem* itemCorreo = new QStandardItem(QString::fromStdString(nodo->correo));
        fila.append(itemCorreo);

        // Insertar un placeholder en la columna de "Acciones" donde irá el botón
        QStandardItem* itemBoton = new QStandardItem();
        itemBoton->setData(QVariant::fromValue(nodo->correo), Qt::UserRole);
        fila.append(itemBoton);

        model->appendRow(fila);
        nodo = nodo->siguiente;
    }

    // Asignar el modelo a la tabla
    ui->tabla_enviarSolicitud->setModel(model);

    // Crear un delegado para la columna 1 (Acciones) que añadirá botones
    ButtonDelegate *delegate = new ButtonDelegate(this);
    ui->tabla_enviarSolicitud->setItemDelegateForColumn(1, delegate);

    // Conectar el botón con la función enviarSolicitud
    connect(ui->tabla_enviarSolicitud, &QTableView::clicked, this, [this](const QModelIndex &index) {
        if (index.column() == 1) {  // Si se hace clic en la columna de "Acciones"
            QString correo = index.sibling(index.row(), 0).data().toString();
            enviarSolicitud(correo, correoConectado.toStdString());
        }
    });

    int totalWidth = 665;
    int columnWidth = totalWidth / 2;  // Dividir el espacio en 2 columnas iguales

    // Establecer el ancho de las columnas
    ui->tabla_enviarSolicitud->setColumnWidth(0, columnWidth);  // Columna "Correo de Usuario"
    ui->tabla_enviarSolicitud->setColumnWidth(1, columnWidth);  // Columna "Acciones"
}

void InterfazPrincipal::enviarSolicitud(const QString& correo, const std::string& correoConectado) {
    // Obtener el usuario conectado mediante su correo
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado);

    if (!usuarioConectado) {
        std::cerr << "Error: No hay un usuario conectado." << std::endl;
        return;
    }

    // Obtener el receptor de la solicitud
    Usuario* usuarioReceptor = avlUsuarios.buscar(correo.toStdString());

    if (!usuarioReceptor) {
        QMessageBox::warning(this, "Error", "El usuario no existe.");
        return;
    }

    // Verificar si el usuario conectado ya tiene una solicitud pendiente del receptor
    Pila& pilaUsuarioConectado = usuarioConectado->getPilaSolicitudes(); // Pila del usuario conectado
    if (pilaUsuarioConectado.buscarPorCorreo(usuarioReceptor->getCorreo())) {
        QMessageBox::warning(this, "Solicitud Pendiente", "Ya tienes una solicitud pendiente de este usuario.");
        return;
    }

    //verifica si el usuario conectado ya es amigo del receptor
    MatrizDispersaAmigos& matrizUsuarioConectado = usuarioConectado->getMatrizAmigos(); // Pila del usuario conectado
    if (matrizUsuarioConectado.buscarAmistad(usuarioReceptor->getCorreo())) {
        QMessageBox::warning(this, "Amistad existente", "Ya son amigos con este usuario.");
        return;
    }

    // Verificar si el usuario receptor ya tiene una solicitud pendiente del usuario conectado
    Pila& pilaReceptor = usuarioReceptor->getPilaSolicitudes();
    if (pilaReceptor.buscarPorCorreo(correoConectado)) {
        QMessageBox::warning(this, "Solicitud Pendiente", "El usuario ya tiene una solicitud pendiente de ti.");
        return;
    }

    // Verificar si el usuario conectado tiene una solicitud pendiente del receptor
    ListaSimple& listaSolicitudesEnviadasReceptor = usuarioReceptor->getListaSolicitudesEnviadas();
    if (listaSolicitudesEnviadasReceptor.solicitudPendiente(correoConectado)) {
        QMessageBox::warning(this, "Solicitud Enviada", "Tienes una solicitud pendiente de este usuario");
        return;
    }

    // Verificar si el usuario conectado ya ha enviado una solicitud al receptor
    ListaSimple& listaSolicitudesEnviadas = usuarioConectado->getListaSolicitudesEnviadas();
    if (listaSolicitudesEnviadas.solicitudPendiente(correo.toStdString())) {
        QMessageBox::warning(this, "Solicitud Enviada", "Ya has enviado una solicitud a este usuario.");
        return;
    }

    // Enviar la solicitud
    pilaReceptor.push(correoConectado, "Solicitud de amistad");
    listaSolicitudesEnviadas.agregar(usuarioReceptor->getNombre(), usuarioReceptor->getCorreo());

    // Mostrar mensaje de éxito
    QMessageBox::information(this, "Solicitud Enviada", "La solicitud de amistad ha sido enviada.");
    llenarTablaSolicitudesRecibidas();
    llenarTablaSolicitudesEnviadas();
}

//--------PARA LAS TABLAS DE SOLICITUDES RECIBIDAS POR EL USUARIO CONECTADO-------------
void InterfazPrincipal::llenarTablaSolicitudesRecibidas() {
    AVLUsuarios& avl = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avl.buscar(correoConectado.toStdString());

    if (!usuarioConectado) {
        std::cerr << "Error: No se encontró el usuario conectado." << std::endl;
        return;
    }

    Pila& pilaSolicitudesRecibidas = usuarioConectado->getPilaSolicitudes();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(3);
    model->setHorizontalHeaderLabels(QStringList() << "Correo del Remitente" << "Aceptar" << "Rechazar");

    // Crear una copia de la pila original para no modificarla
    Pila pilaCopia = pilaSolicitudesRecibidas;

    // Llenar la tabla con las solicitudes recibidas
    while (!pilaCopia.estaVacia()) {
        std::shared_ptr<NodoSolicitud> solicitud = pilaCopia.pop();
        QList<QStandardItem*> fila;

        QStandardItem* itemCorreo = new QStandardItem(QString::fromStdString(solicitud->correo));
        fila.append(itemCorreo);

        // Botón Aceptar
        QStandardItem* itemAceptar = new QStandardItem();
        itemAceptar->setData(QVariant::fromValue(solicitud->correo), Qt::UserRole);
        fila.append(itemAceptar);

        // Botón Rechazar
        QStandardItem* itemRechazar = new QStandardItem();
        itemRechazar->setData(QVariant::fromValue(solicitud->correo), Qt::UserRole);
        fila.append(itemRechazar);

        model->appendRow(fila);
    }

    ui->tabla_recibidas->setModel(model);

    // Crear delegados para las acciones de aceptar y rechazar solicitudes
    ButtonDelegateSolicitudes *delegateAceptar = new ButtonDelegateSolicitudes(this, "Aceptar");
    ButtonDelegateSolicitudes *delegateRechazar = new ButtonDelegateSolicitudes(this, "Rechazar");

    ui->tabla_recibidas->setItemDelegateForColumn(1, delegateAceptar);  // Columna de aceptar
    ui->tabla_recibidas->setItemDelegateForColumn(2, delegateRechazar); // Columna de rechazar

    connect(ui->tabla_recibidas, &QTableView::clicked, this, &InterfazPrincipal::manejarSolicitud);
}

// Manejar la acción cuando se acepta o rechaza una solicitud
void InterfazPrincipal::manejarSolicitud(const QModelIndex &index) {
    if (index.column() == 1) {  // Aceptar solicitud
        QString correo = index.sibling(index.row(), 0).data().toString();
        aceptarSolicitud(correo.toStdString());
    } else if (index.column() == 2) {  // Rechazar solicitud
        QString correo = index.sibling(index.row(), 0).data().toString();
        rechazarSolicitud(correo.toStdString());
    }
}

// Aceptar solicitud
void InterfazPrincipal::aceptarSolicitud(const std::string& correoRemitente) {
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());
    Usuario* remitente = avlUsuarios.buscar(correoRemitente);

    if (!usuarioConectado || !remitente) {
        QMessageBox::warning(this, "Error", "Hubo un problema al procesar la solicitud.");
        return;
    }

    // Obtener las instancias de MatrizDispersaAmigos para el usuario conectado y el remitente
    MatrizDispersaAmigos& matrizAmigosUsuarioConectado = usuarioConectado->getMatrizAmigos();
    MatrizDispersaAmigos& matrizAmigosRemitente = remitente->getMatrizAmigos();


    // Agregar la amistad en ambas direcciones
    matrizAmigosUsuarioConectado.agregarAmistad( remitente->getCorreo());
    matrizAmigosRemitente.agregarAmistad(usuarioConectado->getCorreo());

    // Transferir las publicaciones del remitente al BST del usuario conectado
    BSTPublicaciones& bstPublicacionesUsuarioConectado = usuarioConectado->getBSTPublicacionesAmigos();
    ListaDoble& listaPublicacionesRemitente = remitente->getListaPublicacionesPropias();
    bstPublicacionesUsuarioConectado.agregarPublicacionesDeLista(listaPublicacionesRemitente);

    // Transferir las publicaciones del usuario conectado al BST del remitente
    BSTPublicaciones& bstPublicacionesRemitente = remitente->getBSTPublicacionesAmigos();
    ListaDoble& listaPublicacionesUsuarioConectado = usuarioConectado->getListaPublicacionesPropias();
    bstPublicacionesRemitente.agregarPublicacionesDeLista(listaPublicacionesUsuarioConectado);

    //Se agregan las publicaciones al feed (interfaz gráfica)
    mostrarPublicaciones();

    // Imprimir las solicitudes antes de la eliminación
    std::cout << "Solicitudes antes de aceptar:" << std::endl;
    usuarioConectado->getPilaSolicitudes().imprimir();

    // Eliminar la solicitud de la pila de recibidas y de la lista de enviadas
    usuarioConectado->getPilaSolicitudes().eliminarPorCorreo(correoRemitente);
    remitente->getListaSolicitudesEnviadas().eliminarPorCorreo(correoConectado.toStdString());

    // Imprimir las solicitudes después de la eliminación
    std::cout << "Solicitudes después de aceptar:" << std::endl;
    usuarioConectado->getPilaSolicitudes().imprimir();

    // Mostrar mensaje de éxito
    QMessageBox::information(this, "Solicitud Aceptada", "La solicitud ha sido aceptada.");
    llenarTablaSolicitudesRecibidas();  // Actualizar la tabla
    mostrarTopFechasPublicaciones();
}

// Rechazar solicitud
void InterfazPrincipal::rechazarSolicitud(const std::string& correoRemitente) {
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());
    Usuario* remitente = avlUsuarios.buscar(correoRemitente);

    if (!usuarioConectado || !remitente) {
        QMessageBox::warning(this, "Error", "Hubo un problema al procesar la solicitud.");
        return;
    }

    // Eliminar la solicitud de la pila de recibidas y de la lista de enviadas
    usuarioConectado->getPilaSolicitudes().eliminarPorCorreo(correoRemitente);
    remitente->getListaSolicitudesEnviadas().eliminarPorCorreo(correoConectado.toStdString());

    // Mostrar mensaje de éxito
    QMessageBox::information(this, "Solicitud Rechazada", "La solicitud ha sido rechazada.");
    llenarTablaSolicitudesRecibidas();  // Actualizar la tabla
}

//--------PARA LAS TABLAS DE SOLICITUDES ENVIADAS POR EL USUARIO CONECTADO-------------
void InterfazPrincipal::llenarTablaSolicitudesEnviadas() {
    // Obtener la instancia del AVL y buscar el usuario conectado
    AVLUsuarios& avl = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avl.buscar(correoConectado.toStdString());

    if (!usuarioConectado) {
        std::cerr << "Error: No se encontró el usuario conectado." << std::endl;
        return;
    }

    // Obtener la lista de solicitudes enviadas del usuario conectado
    ListaSimple& listaSolicitudesEnviadas = usuarioConectado->getListaSolicitudesEnviadas();
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(3);  // Agregamos una columna extra para el botón
    model->setHorizontalHeaderLabels(QStringList() << "Correo del Receptor" << "Estado" << "Acción");

    // Recorrer las solicitudes enviadas
    NodoSimple* nodo = listaSolicitudesEnviadas.obtenerPrimero();
    while (nodo) {
        QList<QStandardItem*> fila;

        // Columna de correo
        QStandardItem* itemCorreo = new QStandardItem(QString::fromStdString(nodo->correo));
        fila.append(itemCorreo);

        // Columna de estado (pendiente o aceptada)
        QStandardItem* itemEstado = new QStandardItem(QString::fromStdString("Pendiente"));
        fila.append(itemEstado);

        // Columna vacía para el botón (el delegado lo manejará)
        fila.append(new QStandardItem());

        model->appendRow(fila);

        // Avanzar al siguiente nodo
        nodo = nodo->siguiente;
    }

    // Asignar el modelo a la tabla
    ui->tabla_enviadas->setModel(model);

    // Crear el delegado para el botón de cancelar
    ButtonDelegateEnviadas* delegateCancelar = new ButtonDelegateEnviadas(this, "Cancelar");
    ui->tabla_enviadas->setItemDelegateForColumn(2, delegateCancelar); // Columna de "Acción"

    // Conectar la señal del delegado al método de manejar la cancelación
    connect(delegateCancelar, &ButtonDelegateEnviadas::solicitudCancelada, this, &InterfazPrincipal::manejarCancelacionSolicitud);

    // Establecer el ancho de las columnas
    ui->tabla_enviadas->setColumnWidth(0, 150);  // Columna "Correo del Receptor"
    ui->tabla_enviadas->setColumnWidth(1, 100);  // Columna "Estado"
    ui->tabla_enviadas->setColumnWidth(2, 60);   // Columna "Acción"
}

void InterfazPrincipal::manejarCancelacionSolicitud(const QModelIndex &index) {
    // Obtener el correo del receptor en la fila seleccionada
    QString correo = index.sibling(index.row(), 0).data().toString();
    std::cout << "Cancelar solicitud enviada a: " << correo.toStdString() << std::endl;

    // Lógica para cancelar la solicitud
    AVLUsuarios& avl = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avl.buscar(correoConectado.toStdString());

    if (usuarioConectado) {
        Usuario* destinatario = avl.buscar(correo.toStdString());
        if (destinatario) {
            // Eliminar la solicitud de la pila del destinatario
            bool eliminadaDePila = destinatario->getPilaSolicitudes().eliminarPorCorreo(correoConectado.toStdString());
            if (eliminadaDePila) {
                std::cout << "Solicitud eliminada de la pila de " << correo.toStdString() << std::endl;
            } else {
                std::cerr << "Error: No se encontró la solicitud en la pila del destinatario." << std::endl;
            }
        }

        // Eliminar la solicitud de la lista del usuario conectado
        bool eliminadaDeLista = usuarioConectado->getListaSolicitudesEnviadas().eliminarPorCorreo(correo.toStdString());
        if (eliminadaDeLista) {
            std::cout << "Solicitud eliminada de la lista de " << correoConectado.toStdString() << std::endl;
        }

        // Actualizar la tabla después de la eliminación
        llenarTablaSolicitudesEnviadas();
    } else {
        std::cerr << "Error: No se encontró al usuario conectado." << std::endl;
    }
}

//***************************PUBLICACIONES**********************************
//--------------CREACIÓN DE PUBLICACIÓN----------------------
void InterfazPrincipal::crearPublicacion()
{
    // Crear una nueva instancia del módulo de entrada
    NuevaPublicacion *crear = new NuevaPublicacion(nullptr, correoConectado);
    crear->show();

    // Cerrar la ventana actual
    this->close();
    mostrarEliminar();
}

//--------------MOSTRAR PUBLICACIONES Y APLICAR FILTROS-----------------
void InterfazPrincipal::mostrarPublicaciones() {
    // Obtener el usuario conectado
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    if (!usuarioConectado) {
        std::cerr << "Error: No se encontró el usuario conectado." << std::endl;
        return;
    }

    // Crear un widget contenedor para todas las publicaciones
    QWidget *contenedorPublicaciones = new QWidget();
    QVBoxLayout *layoutPublicaciones = new QVBoxLayout(contenedorPublicaciones);

    // Obtener el BST de publicaciones del usuario conectado
    BSTPublicaciones& bstPublicaciones = usuarioConectado->getBSTPublicacionesAmigos();

    // Recorre el BST de publicaciones usando la función en orden
    bstPublicaciones.recorrerInOrden([this, layoutPublicaciones](const Publicacion& publicacion) {
        // Crear un widget para cada publicación
        QWidget *widgetPublicacion = new QWidget();
        QVBoxLayout *layoutPublicacion = new QVBoxLayout(widgetPublicacion);

        // Crear QLabel para mostrar el nombre del usuario
        QLabel *nombreUsuario = new QLabel(publicacion.getNombreUsuario());
        layoutPublicacion->addWidget(nombreUsuario);

        // Crear QLabel para la fecha de publicación
        QLabel *fechaPublicacion = new QLabel(publicacion.getFecha());
        layoutPublicacion->addWidget(fechaPublicacion);

        // Crear QLabel para mostrar el contenido de la publicación
        QLabel *contenidoPublicacion = new QLabel(publicacion.getContenido());
        layoutPublicacion->addWidget(contenidoPublicacion);

        // Crear QLabel para mostrar la imagen, si existe
        QString rutaImagen = publicacion.getImagen();  // Obtén la ruta de la imagen
        if (!rutaImagen.isEmpty()) {  // Verifica que la ruta no esté vacía
            QLabel *imagenPublicacion = new QLabel();
            QPixmap imagen(rutaImagen);  // Carga la imagen desde la ruta
            imagenPublicacion->setPixmap(imagen.scaled(200, 200, Qt::KeepAspectRatio));  // Ajusta el tamaño
            layoutPublicacion->addWidget(imagenPublicacion);  // Añade el QLabel de la imagen al layout
        }

        // Añadir botones debajo del contenido
        QHBoxLayout *layoutBotones = new QHBoxLayout();
        QPushButton *btnOpcionesPublicacion = new QPushButton("Opciones Publicación");

        layoutBotones->addWidget(btnOpcionesPublicacion);

        // Botón de Eliminar Publicación
        QPushButton *btnEliminarPublicacion = new QPushButton("Eliminar Publicación");
        layoutBotones->addWidget(btnEliminarPublicacion);

        layoutPublicacion->addLayout(layoutBotones);

        // Añadir el widget de la publicación al layout de todas las publicaciones
        layoutPublicaciones->addWidget(widgetPublicacion);

        // Conectar botón a la función que abrirá la nueva interfaz de opciones
        connect(btnOpcionesPublicacion, &QPushButton::clicked, this, [this, &publicacion]() {
            publicacionActual = const_cast<Publicacion*>(&publicacion);
            mostrarOpcionesPublicacion();
        });


        // Conectar el botón de eliminar a la función que eliminará la publicación
        connect(btnEliminarPublicacion, &QPushButton::clicked, this, [this, publicacion]() {
            eliminarPublicacion(publicacion);  // Llamar al método auxiliar para eliminar la publicación
        });

    });

    // Establecer el layout de publicaciones en el contenedor de scroll
    ui->scroll_publicaciones->setWidget(contenedorPublicaciones);
    contenedorPublicaciones->setLayout(layoutPublicaciones);
    mostrarEliminar();
}

void InterfazPrincipal::eliminarPublicacion(const Publicacion& publicacion) {
    // Obtener el usuario conectado
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    if (!usuarioConectado) {
        std::cerr << "Error: No se encontró el usuario conectado." << std::endl;
        return;
    }

    // Obtener el BST de publicaciones del usuario conectado
    BSTPublicaciones& bstPublicaciones = usuarioConectado->getBSTPublicacionesAmigos();

    // Eliminar la publicación del BST
    bstPublicaciones.eliminar(publicacion);
    std::cout << "Publicacion eliminada "<< std::endl;
    // Actualizar la vista
    mostrarPublicaciones();
}

void InterfazPrincipal::mostrarEliminar() {
    // Obtener el usuario conectado
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    if (!usuarioConectado) {
        std::cerr << "Error: No se encontró el usuario conectado." << std::endl;
        return;
    }

    // Crear el modelo para la tabla de publicaciones
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(5); // 5 columnas: Correo, Contenido, Imagen, Comentarios, Eliminar
    model->setHorizontalHeaderLabels(QStringList() << "Correo" << "Contenido" << "Imagen" << "Comentarios" << "Eliminar");

    // Obtener el BST de publicaciones del usuario conectado
    BSTPublicaciones& bstPublicaciones = usuarioConectado->getBSTPublicacionesAmigos();

    // Recorre el BST de publicaciones usando la función en orden
    bstPublicaciones.recorrerInOrden([this, model](const Publicacion& publicacion) {
        QList<QStandardItem*> fila;

        // Convertir el correo y contenido a QString
        QStandardItem* itemCorreo = new QStandardItem(publicacion.getCorreo());
        QStandardItem* itemContenido = new QStandardItem(publicacion.getContenido());

        // Añadir los elementos a la fila
        fila.append(itemCorreo);
        fila.append(itemContenido);

        // Procesar la imagen si existe
        QString rutaImagen = publicacion.getImagen();
        QStandardItem* itemImagen = new QStandardItem();
        if (!rutaImagen.isEmpty()) {
            QPixmap imagen(rutaImagen);
            itemImagen->setIcon(QIcon(imagen.scaled(50, 50, Qt::KeepAspectRatio)));  // Ajustar el tamaño
        }
        fila.append(itemImagen);

        // Botón de comentarios
        QStandardItem* itemComentarios = new QStandardItem("Comentarios");
        fila.append(itemComentarios);

        // Botón de eliminar
        QStandardItem* itemEliminar = new QStandardItem("Eliminar");
        itemEliminar->setData(QVariant::fromValue(publicacion), Qt::UserRole); // Guardar referencia a la publicación
        fila.append(itemEliminar);

        // Agregar la fila al modelo
        model->appendRow(fila);
    });

    // Asignar el modelo a la tabla
    ui->tbl_publicacionesEliminar->setModel(model);

    // Crear un delegado para las columnas de comentarios y eliminar
    ButtonDelegateEliminarDef *delegateComentarios = new ButtonDelegateEliminarDef(this, "Comentarios");
    ButtonDelegateEliminarDef *delegateEliminar = new ButtonDelegateEliminarDef(this, "Eliminar");

    ui->tbl_publicacionesEliminar->setItemDelegateForColumn(3, delegateComentarios); // Comentarios
    ui->tbl_publicacionesEliminar->setItemDelegateForColumn(4, delegateEliminar); // Eliminar

    // Conectar las señales de los botones
    connect(delegateEliminar, &ButtonDelegateEliminarDef::publicacionEliminada, this, [this, model](const QModelIndex &index) {
        //Publicacion publicacion = index.data(Qt::UserRole).value<Publicacion>();

        // Aquí eliminarías la publicación del BST del usuario
        // usuarioConectado->getBSTPublicacionesAmigos().eliminar(publicacion);

        // Eliminar la fila del modelo
        model->removeRow(index.row());
        QMessageBox::information(this, "Eliminar", "Publicación eliminada.");
    });

    connect(delegateComentarios, &ButtonDelegateEliminarDef::mostrarComentarios, this, [](const QModelIndex &index) {
        QMessageBox::information(nullptr, "Comentarios", "Botón de comentarios presionado.");
    });

    // Ajustar el ancho de las columnas si es necesario
    ui->tbl_publicacionesEliminar->setColumnWidth(0, 175); // Columna "Correo"
    ui->tbl_publicacionesEliminar->setColumnWidth(1, 210); // Columna "Contenido"
    ui->tbl_publicacionesEliminar->setColumnWidth(2, 100); // Columna "Imagen"
    ui->tbl_publicacionesEliminar->setColumnWidth(3, 100); // Columna "Comentarios"
    ui->tbl_publicacionesEliminar->setColumnWidth(4, 100); // Columna "Eliminar"
}


// Método para validar el formato de la fecha
bool validarFecha(const QString& fecha) {
    // Validar el formato de la fecha (dd/mm/yyyy)
    std::regex formatoFecha("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}$");
    return std::regex_match(fecha.toStdString(), formatoFecha);
}

// Método para manejar el clic en btn_aplicarFecha
void InterfazPrincipal::aplicarFiltroFecha() {
    QString fechaFiltro = ui->txt_fechaFiltro->toPlainText();

    if (!validarFecha(fechaFiltro)) {
        QMessageBox::warning(this, "Formato de Fecha Inválido", "El formato de la fecha debe ser dd/mm/yyyy.");
        return;
    }

    // Mostrar publicaciones filtradas por la fecha
    mostrarPublicacionesPorFecha(fechaFiltro);
}

// Método para mostrar las publicaciones por filtro
void InterfazPrincipal::mostrarPublicacionesPorFecha(const QString& fechaFiltro) {
    // Obtener el usuario conectado
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    if (!usuarioConectado) {
        std::cerr << "Error: No se encontró el usuario conectado." << std::endl;
        return;
    }

    // Limpiar el contenedor de publicaciones
    ui->scroll_publicaciones->takeWidget();

    // Crear un nuevo widget contenedor para las publicaciones filtradas
    QWidget *contenedorPublicaciones = new QWidget();
    QVBoxLayout *layoutPublicaciones = new QVBoxLayout(contenedorPublicaciones);

    // Obtener el BST de publicaciones del usuario conectado
    BSTPublicaciones& bstPublicaciones = usuarioConectado->getBSTPublicacionesAmigos();

    // Recorre el BST de publicaciones usando la función en orden
    bstPublicaciones.recorrerInOrden([this, layoutPublicaciones, fechaFiltro](const Publicacion& publicacion) {
        // Filtrar publicaciones por fecha
        if (publicacion.getFecha() == fechaFiltro) {
            // Crear un widget para cada publicación
            QWidget *widgetPublicacion = new QWidget();
            QVBoxLayout *layoutPublicacion = new QVBoxLayout(widgetPublicacion);

            // Crear QLabel para mostrar el nombre del usuario
            QLabel *nombreUsuario = new QLabel(publicacion.getNombreUsuario());
            layoutPublicacion->addWidget(nombreUsuario);

            // Crear QLabel para la fecha de publicación
            QLabel *fechaPublicacion = new QLabel(publicacion.getFecha());
            layoutPublicacion->addWidget(fechaPublicacion);

            // Crear QLabel para mostrar el contenido de la publicación
            QLabel *contenidoPublicacion = new QLabel(publicacion.getContenido());
            layoutPublicacion->addWidget(contenidoPublicacion);

            // Crear QLabel para mostrar la imagen, si existe
            QString rutaImagen = publicacion.getImagen();  // Obtén la ruta de la imagen
            if (!rutaImagen.isEmpty()) {  // Verifica que la ruta no esté vacía
                QLabel *imagenPublicacion = new QLabel();
                QPixmap imagen(rutaImagen);  // Carga la imagen desde la ruta
                imagenPublicacion->setPixmap(imagen.scaled(200, 200, Qt::KeepAspectRatio));  // Ajusta el tamaño
                layoutPublicacion->addWidget(imagenPublicacion);  // Añade el QLabel de la imagen al layout
            }

            // Añadir botones debajo del contenido
            QHBoxLayout *layoutBotones = new QHBoxLayout();
            QPushButton *btnComentar = new QPushButton("Comentar");
            QPushButton *btnVerComentarios = new QPushButton("Ver Comentarios");
            QPushButton *btnVerArbolComentarios = new QPushButton("Ver Árbol de Comentarios");

            layoutBotones->addWidget(btnComentar);
            layoutBotones->addWidget(btnVerComentarios);
            layoutBotones->addWidget(btnVerArbolComentarios);

            layoutPublicacion->addLayout(layoutBotones);

            // Añadir el widget de la publicación al layout de todas las publicaciones
            layoutPublicaciones->addWidget(widgetPublicacion);
        }
    });

    // Establecer el layout de publicaciones en el contenedor de scroll
    ui->scroll_publicaciones->setWidget(contenedorPublicaciones);
    contenedorPublicaciones->setLayout(layoutPublicaciones);
}

void InterfazPrincipal::aplicarOrdenLimitado(){
    QString tipoOrden = ui->combo_ordenes->currentText();
    QString cantidadTexto = ui->txt_cantidad->toPlainText();  // Obtener el texto del QTextEdit
    bool ok;
    int cantidad = cantidadTexto.toInt(&ok);

    if (!ok || cantidad <= 0) {
        QMessageBox::warning(this, "Error", "Ingrese una cantidad válida.");
        return;
    }

    mostrarPublicacionesConOrden(tipoOrden, cantidad);
}

void InterfazPrincipal::mostrarPublicacionesConOrden(const QString& tipoOrden, int cantidad) {
    // Obtener el usuario conectado
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    if (!usuarioConectado) {
        std::cerr << "Error: No se encontró el usuario conectado." << std::endl;
        return;
    }

    // Crear un widget contenedor para todas las publicaciones
    QWidget *contenedorPublicaciones = new QWidget();
    QVBoxLayout *layoutPublicaciones = new QVBoxLayout(contenedorPublicaciones);

    // Obtener el BST de publicaciones del usuario conectado
    BSTPublicaciones& bstPublicaciones = usuarioConectado->getBSTPublicacionesAmigos();

    // Función lambda para mostrar una publicación
    auto mostrarPublicacion = [this, layoutPublicaciones](const Publicacion& publicacion) {
        QWidget *widgetPublicacion = new QWidget();
        QVBoxLayout *layoutPublicacion = new QVBoxLayout(widgetPublicacion);

        QLabel *nombreUsuario = new QLabel(publicacion.getNombreUsuario());
        layoutPublicacion->addWidget(nombreUsuario);

        QLabel *fechaPublicacion = new QLabel(publicacion.getFecha());
        layoutPublicacion->addWidget(fechaPublicacion);

        QLabel *contenidoPublicacion = new QLabel(publicacion.getContenido());
        layoutPublicacion->addWidget(contenidoPublicacion);

        // Crear QLabel para mostrar la imagen, si existe
        QString rutaImagen = publicacion.getImagen();  // Obtén la ruta de la imagen
        if (!rutaImagen.isEmpty()) {  // Verifica que la ruta no esté vacía
            QLabel *imagenPublicacion = new QLabel();
            QPixmap imagen(rutaImagen);  // Carga la imagen desde la ruta
            imagenPublicacion->setPixmap(imagen.scaled(200, 200, Qt::KeepAspectRatio));  // Ajusta el tamaño
            layoutPublicacion->addWidget(imagenPublicacion);  // Añade el QLabel de la imagen al layout
        }

        QHBoxLayout *layoutBotones = new QHBoxLayout();
        QPushButton *btnComentar = new QPushButton("Comentar");
        QPushButton *btnVerComentarios = new QPushButton("Ver Comentarios");
        QPushButton *btnVerArbolComentarios = new QPushButton("Ver Árbol de Comentarios");

        layoutBotones->addWidget(btnComentar);
        layoutBotones->addWidget(btnVerComentarios);
        layoutBotones->addWidget(btnVerArbolComentarios);

        layoutPublicacion->addLayout(layoutBotones);

        layoutPublicaciones->addWidget(widgetPublicacion);
    };

    // Función para limitar el número de publicaciones mostradas
    int contador = 0;

    auto aplicarRecorrido = [&](const Publicacion& publicacion) {
        if (contador < cantidad) {
            mostrarPublicacion(publicacion);
            contador++;
        }
    };

    // Aplicar el tipo de recorrido especificado
    if (tipoOrden == "Pre-Orden") {
        bstPublicaciones.recorrerPreOrden(aplicarRecorrido);
    } else if (tipoOrden == "In-Orden") {
        bstPublicaciones.recorrerInOrden(aplicarRecorrido);
    } else if (tipoOrden == "Post-Orden") {
        bstPublicaciones.recorrerPostOrden(aplicarRecorrido);
    } else {
        QMessageBox::warning(this, "Error", "Tipo de orden inválido.");
        return;
    }

    // Establecer el layout de publicaciones en el contenedor de scroll
    ui->scroll_publicaciones->setWidget(contenedorPublicaciones);
    contenedorPublicaciones->setLayout(layoutPublicaciones);
}

//****************************COMENTARIOS*****************************

void InterfazPrincipal::mostrarOpcionesPublicacion(){

    if (!publicacionActual) {
        std::cerr << "Error: publicacionActual es nulo." << std::endl;
        return;
    }

    // Crear una nueva instancia de gestor
    GestorComentarios *crear = new GestorComentarios(nullptr, correoConectado, publicacionActual);
    crear->show();

    // Cerrar la ventana actual
    this->close();
}

//************************PERFIL***************************
//------------------MODIFICAR DATOS USUARIO CONECTADO---------------

void InterfazPrincipal::modificarDatosPropios() {
    QString nuevoNombre = ui->txt_nombreObtener->toPlainText();
    QString nuevoApellido = ui->txt_apellidoObtener->toPlainText();
    QString nuevoCorreo = ui->txt_correoObtener->toPlainText();
    QString nuevaContrasenia = ui->txt_contraseniaObtener->toPlainText();
    QString nuevaFecha = ui->txt_fechaObtener->toPlainText();

    // Convertir los QString a std::string
    std::string nuevoNombreStd = nuevoNombre.toStdString();
    std::string nuevoApellidoStd = nuevoApellido.toStdString();
    std::string nuevoCorreoStd = nuevoCorreo.toStdString();
    std::string nuevaContraseniaStd = nuevaContrasenia.toStdString();
    std::string nuevaFechaStd = nuevaFecha.toStdString();

    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    // Llamar al método de modificación con std::string
    avlUsuarios.modificarUsuario(usuarioConectado, nuevoNombreStd, nuevoApellidoStd, nuevoCorreoStd, nuevaContraseniaStd, nuevaFechaStd);

    mostrarDatosUsuarioConectado();
}

void InterfazPrincipal::mostrarDatosUsuarioConectado() const {
    // Obtener el usuario conectado (suponiendo que tienes correoConectado disponible)
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    if (usuarioConectado) {
        // Imprimir los datos del usuario en la consola
        std::cout << "Nombre: " << usuarioConectado->getNombre() << std::endl;
        std::cout << "Apellido: " << usuarioConectado->getApellidos() << std::endl;
        std::cout << "Correo: " << usuarioConectado->getCorreo() << std::endl;
        std::cout << "Contraseña: " << usuarioConectado->getContrasenia() << std::endl;
        std::cout << "Fecha: " << usuarioConectado->getFecha() << std::endl;
    } else {
        std::cout << "No se encontró el usuario conectado." << std::endl;
    }
}

//--------------------ELIMINAR AL USUARIO CONECTADO-------------------
void InterfazPrincipal::eliminarUsuarioConectado() {
    // Obtener el correo del usuario conectado
    std::string correoConectadoStr = correoConectado.toStdString();

    // Obtener la instancia del AVLUsuarios
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();

    // Verificar si el usuario está en el sistema
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectadoStr);
    if (usuarioConectado) {
        // Eliminar el usuario del AVL
        avlUsuarios.eliminar(correoConectadoStr);

        // Cerrar sesión o volver a la pantalla de inicio
        std::cout << "Usuario eliminado exitosamente: " << correoConectadoStr << std::endl;
        // Aquí podrías agregar código para cerrar sesión o redirigir al usuario
        cerrarSesion();
    } else {
        std::cout << "No se encontró el usuario conectado para eliminar." << std::endl;
    }
}

//**************************BUSCAR****************************
//--------------BUSCAR A UN USUARIO POR SU CORREO---------------
void InterfazPrincipal::buscarUsuarioCorreo() {
    // Obtener el correo ingresado por el usuario
    QString correoBuscar = ui->txt_correoBuscar->toPlainText();

    // Convertir el QString a std::string para usarlo con AVLUsuarios
    std::string correoBuscarStd = correoBuscar.toStdString();

    // Obtener una instancia del AVLUsuarios (suponiendo que es singleton o global)
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();

    // Buscar el usuario por correo
    Usuario* usuarioEncontrado = avlUsuarios.buscar(correoBuscarStd);

    // Si se encuentra el usuario, mostrar sus datos en los campos correspondientes
    if (usuarioEncontrado) {
        ui->txt_nombreEncontrado->setText(QString::fromStdString(usuarioEncontrado->getNombre()));
        ui->txt_apellidoEncontrado->setText(QString::fromStdString(usuarioEncontrado->getApellidos()));
        ui->txt_correoEncontrado->setText(QString::fromStdString(usuarioEncontrado->getCorreo()));
        ui->txt_fechaEncontrada->setText(QString::fromStdString(usuarioEncontrado->getFecha()));

        // Bloquear los campos para que no sean editables
        ui->txt_nombreEncontrado->setReadOnly(true);
        ui->txt_apellidoEncontrado->setReadOnly(true);
        ui->txt_correoEncontrado->setReadOnly(true);
        ui->txt_fechaEncontrada->setReadOnly(true);

    } else {
        // Si no se encuentra el usuario, limpiar los campos y mostrar un mensaje
        ui->txt_nombreEncontrado->clear();
        ui->txt_apellidoEncontrado->clear();
        ui->txt_correoEncontrado->clear();
        ui->txt_fechaEncontrada->clear();

        // Mostrar mensaje al usuario
        QMessageBox::warning(this, "Usuario no encontrado", "El correo ingresado no corresponde a ningún usuario.");
    }
}

//*********************************REPORTES**************************************
//----------------------TOP 3 FECHAS CON MÁS PUBLICACIONES-----------------------
void InterfazPrincipal::mostrarTopFechasPublicaciones() {
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    if (!usuarioConectado) {
        std::cerr << "Error: No se encontró el usuario conectado." << std::endl;
        return;
    }

    BSTPublicaciones& bstPublicaciones = usuarioConectado->getBSTPublicacionesAmigos();

    std::queue<FechaConteo> colaConteos;
    std::cout<<"antes de contar publicaciones "<<std::endl;
    contarPublicacionesPorFecha(bstPublicaciones, colaConteos);
    std::cout<<"antes de ordenar "<<std::endl;
    ordenarTop3(colaConteos);

    // Crear un modelo para la tabla
    QStandardItemModel* model = new QStandardItemModel();
    model->setColumnCount(2); // Dos columnas: Fecha y Conteo
    model->setHorizontalHeaderLabels(QStringList() << "Fecha" << "Conteo");

    // Llenar la tabla con el top de fechas
    while (!colaConteos.empty()) {
        const auto& top = colaConteos.front();
        colaConteos.pop();

        QList<QStandardItem*> fila;
        fila.append(new QStandardItem(QString::fromStdString(top.fecha)));
        fila.append(new QStandardItem(QString::number(top.conteo)));

        model->appendRow(fila);
    }

    ui->tbl_fechaMasPublicaciones->setModel(model); // Asignar el modelo a la tabla

    // Opcional: configurar el tamaño de las columnas
    ui->tbl_fechaMasPublicaciones->resizeColumnToContents(0);
    ui->tbl_fechaMasPublicaciones->resizeColumnToContents(1);

    int totalWidth = 336;
    int columnWidth = totalWidth / 2;  // Dividir el espacio en 2 columnas iguales

    // Establecer el ancho de las columnas
    ui->tbl_fechaMasPublicaciones->setColumnWidth(0, columnWidth);  // Columna "Correo de Usuario"
    ui->tbl_fechaMasPublicaciones->setColumnWidth(1, columnWidth);  // Columna "Acciones
}

// Función para contar publicaciones por fecha
void InterfazPrincipal::contarPublicacionesPorFecha(const BSTPublicaciones& bst, std::queue<FechaConteo>& colaConteos) {
    std::queue<FechaConteo> colaTemporal;

    // Contamos las publicaciones
    bst.recorrerInOrden([&colaTemporal](const Publicacion& publicacion) {
        std::string fecha = publicacion.getFecha().toStdString();
        bool encontrado = false;

        // Buscar si la fecha ya existe en la cola temporal
        int size = colaTemporal.size();
        for (int i = 0; i < size; ++i) {
            FechaConteo temp = colaTemporal.front();
            colaTemporal.pop();

            if (temp.fecha == fecha) {
                // Aumentamos el conteo
                temp.conteo++;
                encontrado = true;
            }

            // Volver a agregar el elemento temporal
            colaTemporal.push(temp);
        }

        // Si no se encontró, agregar una nueva entrada con conteo 1
        if (!encontrado) {
            colaTemporal.push(FechaConteo(fecha)); // Usar el constructor actual
        }
    });

    // Transferimos la cola temporal a la cola de conteos
    while (!colaTemporal.empty()) {
        colaConteos.push(colaTemporal.front());
        colaTemporal.pop();
    }
}

// Función para ordenar la cola y mantener solo el top 3
void InterfazPrincipal::ordenarTop3(std::queue<FechaConteo>& colaConteos) {
    std::queue<FechaConteo> colaOrdenada;

    while (!colaConteos.empty()) {
        auto actual = colaConteos.front();
        colaConteos.pop();

        // Insertar en la cola ordenada
        std::queue<FechaConteo> tempQueue;
        while (!colaOrdenada.empty() && colaOrdenada.front().conteo > actual.conteo) {
            tempQueue.push(colaOrdenada.front());
            colaOrdenada.pop();
        }
        colaOrdenada.push(actual);
        while (!tempQueue.empty()) {
            colaOrdenada.push(tempQueue.front());
            tempQueue.pop();
        }
    }

    // Mantener solo el top 3
    while (colaOrdenada.size() > 3) {
        colaOrdenada.pop();
    }

    // Transferimos de nuevo a la cola de conteos
    while (!colaOrdenada.empty()) {
        colaConteos.push(colaOrdenada.front());
        colaOrdenada.pop();
    }
}

// Función para mostrar el top 3 fechas con más publicaciones
void InterfazPrincipal::mostrarTopFechas(std::queue<FechaConteo>& colaConteos) {
    std::cout << "Top 3 fechas con más publicaciones:\n";
    for (int i = 0; i < 3 && !colaConteos.empty(); ++i) {
        const auto& top = colaConteos.front();
        std::cout << top.fecha << ": " << top.conteo << " publicaciones\n";
        colaConteos.pop();
    }
}

//----------------------GRAFICA BST PUBLICACION FECHA ESPECÍFICA-----------------------
void InterfazPrincipal::generarGraficoBSTPorFecha() {
    QString fecha = ui->txt_obtenerFechaBST->toPlainText();

    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuarioConectado = avlUsuarios.buscar(correoConectado.toStdString());

    if (!usuarioConectado) {
        std::cerr << "Error: No se encontró el usuario conectado." << std::endl;
        return;
    }

    BSTPublicaciones& bstPublicaciones = usuarioConectado->getBSTPublicacionesAmigos();

    // Convertir los QString a std::string
    std::string fechastd = fecha.toStdString();

    NodoBST* nodo = bstPublicaciones.buscarPorFechaR(fechastd);

    if (nodo) {
        std::ofstream archivo("archivo.dot");
        archivo << "digraph G {\n";
        bstPublicaciones.generarDot(nodo, archivo);  // Solo graficamos el nodo de la fecha buscada
        archivo << "}\n";
        archivo.close();

        // Generar imagen .png
        std::string rutaImagen = "C:\\Users\\estua\\OneDrive\\Documentos\\Proyecto1EDD\\pruebas\\arbol.png";
        std::string comando = "dot -Tpng archivo.dot -o \"" + rutaImagen + "\"";
        system(comando.c_str());

        // Cargar imagen en el label
        ui->lbl_bstGraficaFecha->clear();
        QPixmap imagen(QString::fromStdString(rutaImagen));
        if (!imagen.isNull()) {
            imagen = imagen.scaled(311, 171, Qt::KeepAspectRatio);
            ui->lbl_bstGraficaFecha->setPixmap(imagen);
        } else {
            std::cerr << "Error: No se pudo cargar la imagen." << std::endl;
        }
    } else {
        std::cerr << "Error: No se encontraron publicaciones en la fecha especificada." << std::endl;
    }
}

