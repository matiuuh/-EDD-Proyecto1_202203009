#include "arbolbcomentarios.h"

using namespace std;

ArbolBComentarios::ArbolBComentarios(){
    root = nullptr;
}

void ArbolBComentarios::insertar(shared_ptr<Comentario> comentario) {
    std::cout << "ingresando "<< std::endl;
    if (root == nullptr) {
        std::cout << "root es nulo, inicializando." << std::endl;
        root = new PaginaB(); // Inicializa root si es nulo
    }
    std::cout << "olaoalsa." << std::endl;
    insertar(&root, comentario);
}

void ArbolBComentarios::insertar(PaginaB** root, shared_ptr<Comentario> comentario) {

    // Verifica si root es nulo
    if (*root == nullptr) {
        std::cout << "El root pasado a este método es nulo, inicializando." << std::endl;
        *root = new PaginaB(); // Inicializa si es nulo
    } else {
        std::cout << "Root existente, cuenta actual: " << (*root)->cuenta << std::endl;
    }

    bool goUp = false;
    shared_ptr<Comentario> mediano;
    PaginaB* newPage;
    std::cout << "en el push"<< std:: endl;
    push(*root, comentario, goUp, mediano, &newPage);
    std::cout << "333333333333333333";

    if (goUp) {
        // Crear una nueva página si la raíz se divide
        PaginaB* temp = new PaginaB();
        temp->keys[0] = mediano;
        temp->branches[0] = *root;
        temp->branches[1] = newPage;
        temp->cuenta = 1;
        *root = temp;
    }
}

// Método push: Empujar un comentario a la página
void ArbolBComentarios::push(PaginaB* actualPage, shared_ptr<Comentario> comentario, bool &goUp, shared_ptr<Comentario>& mediano, PaginaB** newPage) {
    int k = 0;
    std::cout << "[INFO] Entrando a push()" << std::endl;

    if(actualPage == nullptr){
        std::cout << "[INFO] Página actual es nullptr, subimos el comentario." << std::endl;

        goUp = true;
        mediano = comentario;
        *newPage = nullptr;
    }else{
        std::cout << "[INFO] Buscando comentario en la página actual." << std::endl;

        bool node_repeated = buscarComentarioEnPagina(actualPage, comentario, k);
        if (node_repeated) {
            cout << "Clave Duplicada: " << comentario << endl;
            goUp = false;
            return;
        }
        std::cout << "[INFO] Descendiendo por la rama " << k << std::endl;
        push(actualPage->branches[k], comentario, goUp, mediano, newPage);
        /* devuelve control vuelve por el camino de busqueda*/
        if(goUp) {
            std::cout << "[INFO] Volviendo a subir después de insertar en una rama." << std::endl;

            if(actualPage->paginaLlena()){
                std::cout << "[INFO] Página llena, se va a dividir." << std::endl;
                dividir(actualPage, mediano, *newPage, k, mediano, newPage);
            } else {
                std::cout << "[INFO] Insertando comentario mediano en la página actual." << std::endl;

                goUp = false;
                pushNode(actualPage, mediano, *newPage, k);
            }
        }
    }
    std::cout << "[INFO] Saliendo de push()" << std::endl;
}

void ArbolBComentarios::pushNode(PaginaB* current, shared_ptr<Comentario> comentario, PaginaB* rd, int k){
    // move the keys and branches to the right
    std::cout << "[INFO] Insertando comentario en la página." << std::endl;

    for (int i = current->cuenta; i >= k+1; i--)
    {
        cout<<"hola1 "<<endl;
        current->keys[i+1] = current->keys[i];
        cout<<"hola2 "<<endl;
        current->branches[i+1] = current->branches[i];
        cout<<"hola "<<endl;
    }

    current->keys[k+1] = comentario;
    current->branches[k+1] = rd;
    current->cuenta++;
    std::cout << "[INFO] Clave insertada. Nueva cuenta: " << current->cuenta << std::endl;
}

// Método para buscar si un comentario ya existe en la página
bool ArbolBComentarios::buscarComentarioEnPagina(PaginaB* current, shared_ptr<Comentario> comentario, int &k) {
    // Comparar los comentarios por correo y hora
    for (k = 0; k < current->cuenta; k++) {
        if (current->keys[k]->getFecha() == comentario->getFecha() && current->keys[k]->getHora() == comentario->getHora()) {
            return true;  // El comentario ya existe
        }
        if (current->keys[k]->getFecha() > comentario->getFecha() ||
            (current->keys[k]->getFecha() == comentario->getFecha() && current->keys[k]->getHora() > comentario->getHora())) {
            break;  // Encontrar la posición correcta para insertar
        }
    }
    return false;
}

// Método para dividir una página cuando está llena
void ArbolBComentarios::dividir(PaginaB* current, shared_ptr<Comentario> comentario, PaginaB* rd, int k, shared_ptr<Comentario>& mediano, PaginaB** newPage) {
    // Lógica para dividir la página cuando está llena
    int posMedio = ORDEN / 2;
    *newPage = new PaginaB();

    // Mover las claves superiores y ramas a la nueva página
    for (int i = posMedio + 1, j = 0; i < ORDEN; i++, j++) {
        (*newPage)->keys[j] = current->keys[i];
        (*newPage)->branches[j] = current->branches[i];
    }

    // Aquí está la corrección
    (*newPage)->branches[ORDEN - posMedio - 1] = current->branches[current->cuenta];

    current->cuenta = posMedio;
    (*newPage)->cuenta = ORDEN - posMedio - 1;

    // Determinar la clave mediana
    if (k <= posMedio) {
        insertarClave(current, comentario, rd, k);
    } else {
        insertarClave(*newPage, comentario, rd, k - posMedio - 1);
    }

    mediano = current->keys[posMedio];  // Elevar la clave mediana
}


// Método para insertar una clave en la página
void ArbolBComentarios::insertarClave(PaginaB* current, shared_ptr<Comentario> comentario, PaginaB* rd, int k) {
    for (int i = current->cuenta; i > k; i--) {
        current->keys[i] = current->keys[i - 1];
        current->branches[i + 1] = current->branches[i];
    }
    current->keys[k] = comentario;
    current->branches[k + 1] = rd;
    current->cuenta++;
}

void ArbolBComentarios::mostrarTodosLosComentarios() {
    mostrarComentariosDesdePagina(root);
}

void ArbolBComentarios::mostrarComentariosDesdePagina(PaginaB* pagina) {
    if (pagina == nullptr) {
        return; // Si la página es nula, no hay nada que mostrar
    }

    for (int i = 0; i < pagina->cuenta; i++) {
        // Recorrer la rama izquierda
        if (pagina->branches[i] != nullptr) {
            mostrarComentariosDesdePagina(pagina->branches[i]);
        }

        // Mostrar el comentario en la clave
        std::cout << "Comentario de " << pagina->keys[i]->getCorreo().toStdString()
                  << " (Hora: " << pagina->keys[i]->getHora().toStdString() << "): "
                  << pagina->keys[i]->getContenido().toStdString() << std::endl;
    }

    // Recorrer la rama derecha
    if (pagina->branches[pagina->cuenta] != nullptr) {
        mostrarComentariosDesdePagina(pagina->branches[pagina->cuenta]);
    }
}
