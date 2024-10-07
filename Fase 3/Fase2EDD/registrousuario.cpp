#include "registrousuario.h"
#include "ui_registrousuario.h"
#include "moduloentrada.h"
#include "EstructurasAdmin/avlusuarios.h"

RegistroUsuario::RegistroUsuario(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::RegistroUsuario)
{
    ui->setupUi(this);

    // Acceder a la instancia única del árbol AVL
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_regresar, &QPushButton::clicked, this, &RegistroUsuario::regresar);

    // Conectar el botón "Registrar" con la función que manejará el registro de usuario
    connect(ui->btn_registrar, &QPushButton::clicked, this, &RegistroUsuario::registrarUsuario);

}

RegistroUsuario::~RegistroUsuario()
{
    delete ui;
}

// Función para manejar el cierre de sesión
void RegistroUsuario::regresar()
{
    // Crear una nueva instancia del módulo de entrada
    ModuloEntrada *salir = new ModuloEntrada(nullptr);
    salir->show();  // Mostrar la ventana del módulo de entrada

    // Cerrar la ventana actual (ModuloAdministrador)
    this->close();
}

void RegistroUsuario::registrarUsuario()
{
    // Obtener el texto de los campos
    QString nombre = ui->txt_nombre->toPlainText();
    QString apellido = ui->txt_apellido->toPlainText();
    QString fechaNacimiento = ui->txt_fecha->toPlainText();
    QString correo = ui->txt_correo->toPlainText();
    QString contrasenia = ui->txt_contrasenia->toPlainText();

    // Verificar que todos los campos estén llenos
    if (nombre.isEmpty() || apellido.isEmpty() || fechaNacimiento.isEmpty() ||
        correo.isEmpty() || contrasenia.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos");
        return;
    }

    // Validar el formato de la fecha (dd/mm/yyyy)
    std::regex formatoFecha("^(0?[1-9]|[12][0-9]|3[01])/(0?[1-9]|1[0-2])/\\d{4}$");

    if (!std::regex_match(fechaNacimiento.toStdString(), formatoFecha)) {
        QMessageBox::warning(this, "Error", "La fecha debe tener el formato dd/mm/yyyy");
        return;
    }

    //QMessageBox::warning(this, "Éxito", "antes de verificar");

    // Acceder a la instancia única del árbol AVL
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();

    // Verificar si el correo ya existe en el AVL
    if (avlUsuarios.buscar(correo.toStdString()) != nullptr) {
        QMessageBox::warning(this, "Error", "El correo ya está registrado");
        return;
    }

    //QMessageBox::warning(this, "Éxito", "antes de crear el objeto");

    // Crear un nuevo objeto Usuario (suponiendo que tienes una clase Usuario)
    Usuario* nuevoUsuario = new Usuario(nombre.toStdString(), apellido.toStdString(),
                                        fechaNacimiento.toStdString(), correo.toStdString(),
                                        contrasenia.toStdString());

    //QMessageBox::warning(this, "Éxito", "estamos antes de insertar");

    // Insertar el nuevo usuario en el árbol AVL
    avlUsuarios.insertar(nuevoUsuario);

    QMessageBox::information(this, "Éxito", "Usuario registrado correctamente");
}
