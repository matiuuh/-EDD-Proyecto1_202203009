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
#include "listadoble.h"
#include "EstructurasAdmin/listadoblepublicacionesglobal.h"
#include "TablasAdmin/buttondelegatetablaadmin.h"


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

    //*******************************BOTONES IMPORTAR PUBLICACIONES*************************
    // Conectar el botón "Cargar Usuarios" con la función para abrir el explorador de archivos
    connect(ui->btn_cargarPublicaciones, &QPushButton::clicked, this, &ModuloAdministrador::cargarPublicaciones);

    connect(ui->btn_importarPublicaciones, &QPushButton::clicked, this, &ModuloAdministrador::importarPublicaciones);

    //***************************BUSCAR***************************
    connect(ui->btn_buscar, &QPushButton::clicked, this, &ModuloAdministrador::buscarUsuarioPorCorreo);

    //*****************************APLICAR RECORRIDOS EN ORDEN************************
    connect(ui->btn_aplicar, &QPushButton::clicked, this, &ModuloAdministrador::aplicarRecorridos);

    mostrarUsuariosEnTabla();

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
    mostrarUsuariosEnTabla();
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

            // Transferir publicaciones del remitente al BST del receptor
            BSTPublicaciones& bstPublicacionesReceptor = receptor->getBSTPublicacionesAmigos();
            ListaDoble& listaPublicacionesRemitente = emisor->getListaPublicacionesPropias();
            bstPublicacionesReceptor.agregarPublicacionesDeLista(listaPublicacionesRemitente);

            // Transferir publicaciones del receptor al BST del remitente
            BSTPublicaciones& bstPublicacionesRemitente = emisor->getBSTPublicacionesAmigos();
            ListaDoble& listaPublicacionesReceptor = receptor->getListaPublicacionesPropias();
            bstPublicacionesRemitente.agregarPublicacionesDeLista(listaPublicacionesReceptor);

        } else if (estado == "pendiente") {
            std::cout << "Solicitud pendiente entre: " << emisorCorreo << " y " << receptorCorreo << std::endl;
        } else {
            std::cerr << "Error: Estado de solicitud no válido (debe ser 'aceptada' o 'pendiente')." << std::endl;
        }
    }

    std::cout << "Solicitudes importadas exitosamente desde el archivo JSON." << std::endl;
}

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

//------------------------PUBLICACIONES---------------------

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

// Función para seleccionar el archivo JSON y cargar las publicaciones
void ModuloAdministrador::importarPublicaciones() {
    QString archivoPath = QFileDialog::getOpenFileName(this, "Seleccionar archivo JSON", "", "Archivos JSON (*.json)");

    if (archivoPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "No se seleccionó ningún archivo.");
        return;
    }

    std::string rutaArchivoJSON = archivoPath.toStdString();
    btn_importarPublicaciones_Click(rutaArchivoJSON);

    QMessageBox::information(this, "Éxito", "Publicaciones importadas exitosamente.");
}

// Método que maneja la importación de publicaciones desde el archivo JSON
void ModuloAdministrador::btn_importarPublicaciones_Click(const std::string& rutaArchivoJSON) {
    std::ifstream archivo(rutaArchivoJSON);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo JSON: " << rutaArchivoJSON << std::endl;
        return;
    }

    nlohmann::json publicacionesJSON;
    archivo >> publicacionesJSON;

    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    ListaDoblePublicacionesGlobal& listaPublicacionesGlobal = ListaDoblePublicacionesGlobal::getInstance();

    for (const auto& publicacionJSON : publicacionesJSON) {
        std::string correoUsuario = publicacionJSON["correo"];
        std::string contenido = publicacionJSON["contenido"];
        std::string fecha = publicacionJSON["fecha"];
        std::string hora = publicacionJSON["hora"];

        // Obtener el usuario que creó la publicación
        Usuario* usuario = avlUsuarios.buscar(correoUsuario);
        if (!usuario) {
            std::cerr << "Error: El usuario " << correoUsuario << " no existe en el sistema." << std::endl;
            continue; // Pasar a la siguiente publicación
        }

        // Crear una nueva publicación
        Publicacion nuevaPublicacion(QString::fromStdString(correoUsuario), QString::fromStdString(contenido));
        nuevaPublicacion.setFecha(QString::fromStdString(fecha));
        nuevaPublicacion.setHora(QString::fromStdString(hora));

        // Verificar si la publicación tiene una imagen
        if (publicacionJSON.contains("imagen")) {
            std::string rutaImagen = publicacionJSON["imagen"];
            nuevaPublicacion.setImagen(QString::fromStdString(rutaImagen));
        }

        // Almacenar la publicación en la lista global de publicaciones
        listaPublicacionesGlobal.insertar(nuevaPublicacion);
        listaPublicacionesGlobal.mostrar();

        // Almacenar la publicación en la lista de publicaciones del usuario
        usuario->getListaPublicacionesPropias().insertar(nuevaPublicacion);
        std::cout << "Mostrando publicaciones propias: " << std::endl;
        usuario->getListaPublicacionesPropias().mostrar();

        // Almacenar la publicación en el BST de publicaciones del usuario y amigos
        usuario->getBSTPublicacionesAmigos().insertar(nuevaPublicacion);

        std::cout << "Mostrando publicaciones del BST: " << std::endl;
        usuario->getBSTPublicacionesAmigos().mostrarPublicaciones();
    }

    std::cout << "Publicaciones importadas exitosamente desde el archivo JSON." << std::endl;
}

//*************************************BUSCAR**************************************
void ModuloAdministrador::buscarUsuarioPorCorreo() {
    // Limpiar la tabla antes de la búsqueda
    ui->tabla_usuariosADMIN->setRowCount(0);

    // Obtener el correo a buscar desde el campo de texto
    QString correoBuscar = ui->txt_correoBuscar->toPlainText();
    if (correoBuscar.isEmpty()) {
        return; // Si el campo está vacío, no hacer nada
    }

    // Buscar al usuario en el AVL
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    Usuario* usuario = avlUsuarios.buscar(correoBuscar.toStdString());

    if (usuario) {
        // Si el usuario existe, mostrarlo en la tabla
        ui->tabla_usuariosADMIN->insertRow(0);

        // Crear el QTableWidgetItem para el correo
        QTableWidgetItem* itemCorreo = new QTableWidgetItem(QString::fromStdString(usuario->getCorreo()));

        // Agregar el item a la tabla (columna 0 para correo)
        ui->tabla_usuariosADMIN->setItem(0, 0, itemCorreo);
    }
}

void ModuloAdministrador::mostrarUsuariosEnTabla() {
    // Limpiar la tabla antes de llenarla nuevamente
    ui->tabla_usuariosADMIN->clearContents();  // Limpia el contenido sin eliminar las cabeceras
    ui->tabla_usuariosADMIN->setRowCount(0);

    // Obtener la instancia del AVL y la lista de usuarios
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    ListaDobleUsuariosDisponibles listaUsuarios;

    // Obtener todos los usuarios del AVL
    avlUsuarios.obtenerTodosLosUsuarios(listaUsuarios);

    // Configurar las cabeceras de la tabla
    ui->tabla_usuariosADMIN->setColumnCount(3);
    QStringList headers;
    headers << "Correo de Usuario" << "Modificar" << "Eliminar";
    ui->tabla_usuariosADMIN->setHorizontalHeaderLabels(headers);

    // Llenar la tabla iterando sobre los correos de la lista
    int fila = 0;
    listaUsuarios.paraCadaCorreo([this, &fila](const std::string& correo) {
        // Insertar una nueva fila en la tabla
        ui->tabla_usuariosADMIN->insertRow(fila);

        // Crear el QTableWidgetItem para el correo
        QTableWidgetItem* itemCorreo = new QTableWidgetItem(QString::fromStdString(correo));
        ui->tabla_usuariosADMIN->setItem(fila, 0, itemCorreo);

        // Crear los items de las acciones como "placeholders"
        QTableWidgetItem* modificarItem = new QTableWidgetItem();
        ui->tabla_usuariosADMIN->setItem(fila, 1, modificarItem);

        QTableWidgetItem* eliminarItem = new QTableWidgetItem();
        ui->tabla_usuariosADMIN->setItem(fila, 2, eliminarItem);

        fila++;
    });

    // Asignar el ButtonDelegateTablaAdmin a las columnas de botones
    ButtonDelegateTablaAdmin* buttonDelegate = new ButtonDelegateTablaAdmin(this);
    ui->tabla_usuariosADMIN->setItemDelegateForColumn(1, buttonDelegate);  // Columna "Modificar"
    ui->tabla_usuariosADMIN->setItemDelegateForColumn(2, buttonDelegate);  // Columna "Eliminar"

    // Ajustar el ancho de las columnas
    int totalWidth = 725;
    int columnWidth = totalWidth / 3;
    ui->tabla_usuariosADMIN->setColumnWidth(0, columnWidth);  // Columna "Correo de Usuario"
    ui->tabla_usuariosADMIN->setColumnWidth(1, columnWidth);  // Columna "Modificar"
    ui->tabla_usuariosADMIN->setColumnWidth(2, columnWidth);  // Columna "Eliminar"
}

void ModuloAdministrador::aplicarRecorridos() {
    // Limpiar la tabla antes de llenarla nuevamente
    ui->tabla_usuariosADMIN->setRowCount(0);

    // Obtener la instancia del AVL y la lista de usuarios
    AVLUsuarios& avlUsuarios = AVLUsuarios::getInstance();
    ListaDobleUsuariosDisponibles listaUsuarios;

    // Determinar el tipo de orden basado en el combo box
    QString ordenSeleccionado = ui->combo_Orden->currentText();

    if (ordenSeleccionado == "Pre-Orden") {
        avlUsuarios.obtenerUsuariosPreOrden(listaUsuarios);
    } else if (ordenSeleccionado == "In-Orden") {
        avlUsuarios.obtenerUsuariosInOrden(listaUsuarios);
    } else if (ordenSeleccionado == "Post-Orden") {
        avlUsuarios.obtenerUsuariosPostOrden(listaUsuarios);
    }

    // Llenar la tabla iterando sobre los correos de la lista
    int fila = 0;
    listaUsuarios.paraCadaCorreo([this, &fila](const std::string& correo) {
        // Insertar una nueva fila en la tabla
        ui->tabla_usuariosADMIN->insertRow(fila);

        // Crear el QTableWidgetItem para el correo
        QTableWidgetItem* itemCorreo = new QTableWidgetItem(QString::fromStdString(correo));
        ui->tabla_usuariosADMIN->setItem(fila, 0, itemCorreo);

        // Crear el botón "Modificar"
        QPushButton* botonModificar = new QPushButton("Modificar");
        // Agregar el botón "Modificar" a la tabla en la columna 1
        ui->tabla_usuariosADMIN->setCellWidget(fila, 1, botonModificar);

        // Crear el botón "Eliminar"
        QPushButton* botonEliminar = new QPushButton("Eliminar");
        // Agregar el botón "Eliminar" a la tabla en la columna 2
        ui->tabla_usuariosADMIN->setCellWidget(fila, 2, botonEliminar);

        fila++;
    });

    // Ajustar el ancho de las columnas como antes
    int totalWidth = 725;
    int columnWidth = totalWidth / 3;

    ui->tabla_usuariosADMIN->setColumnWidth(0, columnWidth);
    ui->tabla_usuariosADMIN->setColumnWidth(1, columnWidth);
    ui->tabla_usuariosADMIN->setColumnWidth(2, columnWidth);
}


