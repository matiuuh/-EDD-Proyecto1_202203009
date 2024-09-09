#include <iostream>

using namespace std;

class Relacion {
public:
    string usuario1;
    string usuario2;

    Relacion(const std::string& u1, const std::string& u2)
        : usuario1(u1), usuario2(u2) {}
};