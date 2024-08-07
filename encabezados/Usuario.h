
#include <string>

using namespace std;

class Usuario {
    public:
        Usuario(const string& nombre, const string& apellidos, const string& fechaNacimiento, const string& correo, const string& contrasenia);

        string getNombre() const;
        string getApellidos() const;
        string getFechaNacimiento() const;
        string getCorreo() const;
        string getContrasenia() const;
    private:
        string nombre;
        string apellidos;
        string fechaNacimiento;
        string correo;
        string contrasenia;
};
