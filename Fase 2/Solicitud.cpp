#include <iostream>
#include <string>


using namespace std;

class Solicitud {
public:
    std::string emisor;
    std::string receptor;
    std::string estado;

    Solicitud(const std::string& emisor, const std::string& receptor, const std::string& estado)
        : emisor(emisor), receptor(receptor), estado(estado) {}
};