#include <iostream>

using namespace std;

class Publicacion {
private:
    string correoUsuario;
    string contenido;
    string fecha;
    string hora;

public:
    Publicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora)
        : correoUsuario(correo), contenido(contenido), fecha(fecha), hora(hora) {}

    Publicacion(const std::string& correo, const std::string& contenido)
        : correoUsuario(correo), contenido(contenido) {
        // Obtener la fecha y hora actual
        time_t now = time(0);
        tm* ltm = localtime(&now);

        // Formatear la fecha en dd/mm/yyyy
        fecha = (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday) + "/" +
                (1 + ltm->tm_mon < 10 ? "0" : "") + to_string(1 + ltm->tm_mon) + "/" +
                to_string(1900 + ltm->tm_year);

        hora = to_string(ltm->tm_hour) + ":" +
                to_string(ltm->tm_min) + ":" +
                to_string(ltm->tm_sec);
    }

    // Métodos para obtener los datos de la publicación
    string getCorreoUsuario() const { return correoUsuario; }
    string getContenido() const { return contenido; }
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }

    // Método para mostrar la publicación
    void mostrarPublicacion() const {
        cout << "Correo: " << correoUsuario << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Hora: " << hora << endl;
        cout << "Contenido: " << contenido << endl;
    }

    // Sobrecarga del operador == para comparar dos publicaciones
    bool operator==(const Publicacion& otra) const {
        return correoUsuario == otra.correoUsuario &&
            contenido == otra.contenido &&
            fecha == otra.fecha &&
            hora == otra.hora;
    }
};
