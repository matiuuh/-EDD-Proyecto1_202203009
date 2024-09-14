#include "interfazprincipal.h"
#include "./ui_interfazprincipal.h"
#include "moduloentrada.h"
#include "EstructurasAdmin/avlusuarios.h"
#include "pila.h"
#include "listasimple.h"

#include <QStandardItemModel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QMessageBox>  // Para mostrar mensajes de error o éxito
#include <QStyledItemDelegate>

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
