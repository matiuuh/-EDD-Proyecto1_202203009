#include "interfazprincipal.h"
#include "./ui_interfazprincipal.h"
#include "moduloentrada.h"
#include "EstructurasAdmin/avlusuarios.h"
#include "pila.h"
#include "listasimple.h"
#include "TablasModUsuario/buttondelegatesolicitudes.h"

#include <QStandardItemModel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QMessageBox>  // Para mostrar mensajes de error o éxito
#include <QStyledItemDelegate>
#include <QModelIndex>

InterfazPrincipal::InterfazPrincipal(QWidget *parent, const QString& correoUsuario)
    : QMainWindow(parent)
    , ui(new Ui::InterfazPrincipal)
    , correoConectado(correoUsuario)  // Almacenar el correo del usuario conectado
{
    ui->setupUi(this);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_cerrar, &QPushButton::clicked, this, &InterfazPrincipal::cerrarSesion);

    // Llenar la tabla de usuarios cuando se abre la ventana
    llenarTablaUsuarios();  // Aquí llamamos al método para llenar la tabla
    llenarTablaSolicitudesRecibidas();
    llenarTablaSolicitudesEnviadas();
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

    // Verificar si el usuario receptor ya tiene una solicitud pendiente del usuario conectado
    Pila& pilaReceptor = usuarioReceptor->getPilaSolicitudes();
    if (pilaReceptor.buscarPorCorreo(correoConectado)) {
        QMessageBox::warning(this, "Solicitud Pendiente", "El usuario ya tiene una solicitud pendiente de ti.");
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

    // Llenar la tabla con las solicitudes recibidas
    while (!pilaSolicitudesRecibidas.estaVacia()) {
        std::unique_ptr<NodoSolicitud> solicitud = pilaSolicitudesRecibidas.pop();
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

    /*
    // Agregar la amistad en ambas direcciones
    usuarioConectado->getListaAmigos().agregar(remitente->getNombre(), remitente->getCorreo());
    remitente->getListaAmigos().agregar(usuarioConectado->getNombre(), usuarioConectado->getCorreo());*/

    // Eliminar la solicitud de la pila de recibidas y de la lista de enviadas
    usuarioConectado->getPilaSolicitudes().eliminarPorCorreo(correoRemitente);
    remitente->getListaSolicitudesEnviadas().eliminarPorCorreo(correoConectado.toStdString());

    // Mostrar mensaje de éxito
    QMessageBox::information(this, "Solicitud Aceptada", "La solicitud ha sido aceptada.");
    llenarTablaSolicitudesRecibidas();  // Actualizar la tabla
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

        // Columna del botón para cancelar la solicitud
        QPushButton* botonCancelar = new QPushButton("Cancelar");
        connect(botonCancelar, &QPushButton::clicked, this, [this, nodo]() {
            // Aquí se podría programar la lógica para cancelar la solicitud
            std::cout << "Cancelando solicitud para: " << nodo->correo << std::endl;
        });
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(widget);
        layout->addWidget(botonCancelar);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setLayout(layout);

        // Agregar el widget del botón a la tabla
        QStandardItem* itemAccion = new QStandardItem();
        ui->tabla_enviadas->setIndexWidget(model->index(model->rowCount(), 2), widget);

        fila.append(itemAccion);
        model->appendRow(fila);

        // Avanzar al siguiente nodo
        nodo = nodo->siguiente;
    }

    // Asignar el modelo a la tabla
    ui->tabla_enviadas->setModel(model);

    int totalWidth = 310;
    int columnWidth = totalWidth / 3;  // Dividir el espacio en 3 columnas iguales

    // Establecer el ancho de las columnas
    ui->tabla_enviadas->setColumnWidth(0, columnWidth);  // Columna "Correo del Receptor"
    ui->tabla_enviadas->setColumnWidth(1, columnWidth);  // Columna "Estado"
    ui->tabla_enviadas->setColumnWidth(2, columnWidth);  // Columna "Acción"
}
