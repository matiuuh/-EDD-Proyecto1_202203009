#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

class Usuario {
private:
    string nombre;
    string apellidos;
    string fechaNacimiento;
    string correo;
    string contrasenia;

public:
    // Constructor
    Usuario(string nombre, string apellidos, string fechaNacimiento, string correo, string contrasenia);

    // Getters
    string getNombre() const;
    string getApellidos() const;
    string getFechaNacimiento() const;
    string getCorreo() const;
    string getContrasenia() const;

    // Setters
    void setNombre(const string& nombre);
    void setApellidos(const string& apellidos);
    void setFechaNacimiento(const string& fechaNacimiento);
    void setCorreo(const string& correo);
    void setContrasenia(const string& contrasenia);
};

#endif // USUARIO_H
