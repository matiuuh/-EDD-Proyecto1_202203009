#include "moduloadministrador.h"
#include "ui_moduloadministrador.h"
#include "moduloentrada.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QJsonDocument>  // Incluir para manejar JSON
#include <QJsonObject>
#include <QJsonArray>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
//#include <json/json.h>  // Usando la librería JsonCpp para leer el JSON
#include "EstructurasAdmin/avlusuarios.h"
#include "usuario.h"

ModuloAdministrador::ModuloAdministrador(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ModuloAdministrador)
{
    ui->setupUi(this);

    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_cerrarSesion, &QPushButton::clicked, this, &ModuloAdministrador::cerrarSesion);

    //********************************BOTONES IMPORTAR USUARIO****************************
    // Conectar el botón "Cargar Usuarios" con la función para abrir el explorador de archivos y cargar usuarios
    connect(ui->btn_importarUsuarios, &QPushButton::clicked, this, &ModuloAdministrador::importarUsuarios);

    // Conectar el botón "Cargar Usuarios" con la función para abrir el explorador de archivos
    connect(ui->btn_cargarUsuarios, &QPushButton::clicked, this, &ModuloAdministrador::cargarUsuarios);

    //*******************************BOTONES IMPORTAR SOLICITUDES*************************
    // Conectar el botón "Cerrar Sesión" con la función que manejará el cierre de sesión
    connect(ui->btn_cargarSolicitudes, &QPushButton::clicked, this, &ModuloAdministrador::cargarSolicitudes);

    // Conectar el botón "Cargar Usuarios" con la función para abrir el explorador de archivos
    connect(ui->btn_importarSolicitudes, &QPushButton::clicked, this, &ModuloAdministrador::importarSolicitudes);

    // Conectar el botón "Cargar Usuarios" con la función para abrir el explorador de archivos
    connect(ui->btn_cargarPublicaciones, &QPushButton::clicked, this, &ModuloAdministrador::cargarPublicaciones);



}

ModuloAdministrador::~ModuloAdministrador()
{
    delete ui;
}

// Función para manejar el cierre de sesión
void ModuloAdministrador::cerrarSesion()
{
    // Crear una nueva instancia del módulo de entrada
    ModuloEntrada *entrada = new ModuloEntrada(nullptr);
    entrada->show();  // Mostrar la ventana del módulo de entrada

    // Cerrar la ventana actual (ModuloAdministrador)
    this->close();  // También podrías usar `delete this` si quieres eliminar esta instancia completamente
}

//**************************CARGAS MASIVAS*****************************

// Función para cargar un archivo JSON de solicitudes
void ModuloAdministrador::cargarSolicitudes()
{
    // Abrir un cuadro de diálogo para seleccionar un archivo JSON
    QString archivoPath = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json)");

    if (archivoPath.isEmpty()) {
        // Si el usuario cancela la selección, no hacemos nada
        return;
    }

    // Abrir el archivo seleccionado
    QFile archivo(archivoPath);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    // Leer el contenido del archivo
    QTextStream in(&archivo);
    QString contenidoArchivo = in.readAll();
    archivo.close();

    // Mostrar el contenido en el QTextEdit (txt_cargaUsuarios)
    ui->txt_cargaSolicitudes->setPlainText(contenidoArchivo);
}

// Función para cargar un archivo JSON de publicaciones
void ModuloAdministrador::cargarPublicaciones()
{
    // Abrir un cuadro de diálogo para seleccionar un archivo JSON
    QString archivoPath = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json)");

    if (archivoPath.isEmpty()) {
        // Si el usuario cancela la selección, no hacemos nada
        return;
    }

    // Abrir el archivo seleccionado
    QFile archivo(archivoPath);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    // Leer el contenido del archivo
    QTextStream in(&archivo);
    QString contenidoArchivo = in.readAll();
    archivo.close();

    // Mostrar el contenido en el QTextEdit (txt_cargaUsuarios)
    ui->txt_cargaPublicaciones->setPlainText(contenidoArchivo);
}

//---------------------USUARIOS-------------------------
// Función para importar usuarios desde un archivo JSON
void ModuloAdministrador::importarUsuarios()
{
    QString archivoPath = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json)");

    if (archivoPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "No se seleccionó ningún archivo.");
        return;
    }

    std::string rutaArchivoJSON = archivoPath.toStdString();
    btn_importarUsuarios_Click(rutaArchivoJSON);

    QMessageBox::information(this, "Éxito", "Usuarios importados exitosamente.");
}

// Este es el método que estaba causando el error, ahora pertenece a la clase ModuloAdministrador
void ModuloAdministrador::btn_importarUsuarios_Click(const std::string& rutaArchivoJSON) {
    std::ifstream archivo(rutaArchivoJSON);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo JSON: " << rutaArchivoJSON << std::endl;
        return;
    }

    nlohmann::json root;
    archivo >> root;

    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();

    for (const auto& usuarioJson : root) {
        std::string nombres = usuarioJson["nombres"].get<std::string>();
        std::string apellidos = usuarioJson["apellidos"].get<std::string>();
        std::string fechaNacimiento = usuarioJson["fecha_de_nacimiento"].get<std::string>();
        std::string correo = usuarioJson["correo"].get<std::string>();
        std::string contrasenia = usuarioJson["contraseña"].get<std::string>();

        Usuario* nuevoUsuario = new Usuario(nombres, apellidos, fechaNacimiento, correo, contrasenia);
        avlUsuarios.insertar(nuevoUsuario);
    }

    std::cout << "Usuarios importados exitosamente desde el archivo JSON." << std::endl;
}

// Función para cargar un archivo JSON de usuarios
void ModuloAdministrador::cargarUsuarios()
{
    // Abrir un cuadro de diálogo para seleccionar un archivo JSON
    QString archivoPath = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json)");

    if (archivoPath.isEmpty()) {
        // Si el usuario cancela la selección, no hacemos nada
        return;
    }

    // Abrir el archivo seleccionado
    QFile archivo(archivoPath);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    // Leer el contenido del archivo
    QTextStream in(&archivo);
    QString contenidoArchivo = in.readAll();
    archivo.close();

    // Mostrar el contenido en el QTextEdit (txt_cargaUsuarios)
    ui->txt_cargaUsuarios->setPlainText(contenidoArchivo);
}

//---------------------SOLICITUDES-------------------------

void ModuloAdministrador::importarSolicitudes() {
    QString archivoPath = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json)");

    if (archivoPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "No se seleccionó ningún archivo.");
        return;
    }

    std::string rutaArchivoJSON = archivoPath.toStdString();
    btn_importarSolicitudes_Click(rutaArchivoJSON);

    QMessageBox::information(this, "Éxito", "Solicitudes importadas exitosamente.");
}

void ModuloAdministrador::btn_importarSolicitudes_Click(const std::string& rutaArchivoJSON) {
    std::ifstream archivo(rutaArchivoJSON);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo JSON: " << rutaArchivoJSON << std::endl;
        return;
    }

    nlohmann::json solicitudesJSON;
    archivo >> solicitudesJSON;

    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();

    // Iterar sobre cada solicitud en el archivo
    for (const auto& solicitud : solicitudesJSON) {
        std::string emisorCorreo = solicitud["emisor"];
        std::string receptorCorreo = solicitud["receptor"];
        std::string estado = solicitud["estado"];

        // Convertir el estado a minúsculas para aceptar "ACEPTADA", "aceptada", "Aceptada", etc.
        std::transform(estado.begin(), estado.end(), estado.begin(), ::tolower);

        // Obtener los usuarios emisor y receptor
        Usuario* emisor = avlUsuarios.buscar(emisorCorreo);
        Usuario* receptor = avlUsuarios.buscar(receptorCorreo);

        if (!emisor || !receptor) {
            std::cerr << "Error: El emisor o el receptor no existen en el sistema." << std::endl;
            continue; // Pasar a la siguiente solicitud
        }

        // Verificar si la solicitud ya fue enviada
        ListaSimple& listaSolicitudesEnviadas = emisor->getListaSolicitudesEnviadas();
        if (listaSolicitudesEnviadas.solicitudPendiente(receptorCorreo)) {
            std::cerr << "Error: Ya existe una solicitud pendiente entre estos usuarios." << std::endl;
            continue;
        }

        // Verificar si ya son amigos
        MatrizDispersaAmigos& matrizEmisor = emisor->getMatrizAmigos();
        if (matrizEmisor.buscarAmistad(receptorCorreo)) {
            std::cerr << "Error: Ya son amigos." << std::endl;
            continue;
        }

        // Agregar solicitud a la lista del emisor y la pila del receptor
        listaSolicitudesEnviadas.agregar(receptor->getNombre(), receptorCorreo);
        Pila& pilaSolicitudesReceptor = receptor->getPilaSolicitudes();
        pilaSolicitudesReceptor.push(emisorCorreo, "Solicitud de amistad");

        // Manejar el estado de la solicitud (aceptada o pendiente)
        if (estado == "aceptada") {
            matrizEmisor.agregarAmistad(receptorCorreo);
            receptor->getMatrizAmigos().agregarAmistad(emisorCorreo);
            std::cout << "Solicitud aceptada entre: " << emisorCorreo << " y " << receptorCorreo << std::endl;
        } else if (estado == "pendiente") {
            std::cout << "Solicitud pendiente entre: " << emisorCorreo << " y " << receptorCorreo << std::endl;
        } else {
            std::cerr << "Error: Estado de solicitud no válido (debe ser 'aceptada' o 'pendiente')." << std::endl;
        }
    }

    std::cout << "Solicitudes importadas exitosamente desde el archivo JSON." << std::endl;
}

