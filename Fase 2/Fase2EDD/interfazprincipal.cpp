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

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_crearPublicacion, &QPushButton::clicked, this, &InterfazPrincipal::crearPublicacion);

    // Llenar la tabla de usuarios cuando se abre la ventana
    llenarTablaUsuarios();  // Aquí llamamos al método para llenar la tabla
    llenarTablaSolicitudesRecibidas();
    llenarTablaSolicitudesEnviadas();
    mostrarPublicaciones();
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
// Función para manejar el cierre de sesión
void InterfazPrincipal::crearPublicacion()
{
    // Crear una nueva instancia del módulo de entrada
    NuevaPublicacion *crear = new NuevaPublicacion(nullptr, correoConectado);
    crear->show();

    // Cerrar la ventana actual
    this->close();
}

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
    });

    // Establecer el layout de publicaciones en el contenedor de scroll
    ui->scroll_publicaciones->setWidget(contenedorPublicaciones);
    contenedorPublicaciones->setLayout(layoutPublicaciones);
}
