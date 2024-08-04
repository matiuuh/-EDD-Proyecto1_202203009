#include "Usuario.h"

// Constructor
Usuario::Usuario(string _nombre, string _apellidos, string _fechaNacimiento, string _correo, string _contrasenia)
    : nombre(_nombre), apellidos(_apellidos), fechaNacimiento(_fechaNacimiento), correo(_correo), contrasenia(_contrasenia) {}

// Getters
string Usuario::getNombre() const {
    return nombre;
}

string Usuario::getApellidos() const {
    return apellidos;
}

string Usuario::getFechaNacimiento() const {
    return fechaNacimiento;
}

string Usuario::getCorreo() const {
    return correo;
}

string Usuario::getContrasenia() const {
    return contrasenia;
}

// Setters
void Usuario::setNombre(const string& nombre) {
    this->nombre = nombre;
}

void Usuario::setApellidos(const string& apellidos) {
    this->apellidos = apellidos;
}

void Usuario::setFechaNacimiento(const string& fechaNacimiento) {
    this->fechaNacimiento = fechaNacimiento;
}

void Usuario::setCorreo(const string& correo) {
    this->correo = correo;
}

void Usuario::setContrasenia(const string& contrasenia) {
    this->contrasenia = contrasenia;
}
