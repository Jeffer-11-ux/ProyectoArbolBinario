#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    int id;        
    string nombre;   
    Nodo *izq;      
    Nodo *der;       
};

Nodo* nuevoNodo(int id, string nombre) {
    Nodo *nodo = new Nodo();
    nodo->id = id;
    nodo->nombre = nombre;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}  

Nodo* insertar(Nodo *nodo, int id, string nombre, bool &insertado) {
    if (nodo == NULL) {
        insertado = true;
        return nuevoNodo(id, nombre);
    }

    if (id < nodo->id) {
        nodo->izq = insertar(nodo->izq, id, nombre, insertado);
    } else if (id > nodo->id) {
        nodo->der = insertar(nodo->der, id, nombre, insertado);
    } else {
        cout << "Aviso: Ese ID ya existe.\n";
        insertado = false;
    }
    return nodo;
}

Nodo* buscar(Nodo *nodo, int id) {
    if (nodo == NULL || nodo->id == id) {
        return nodo;
    }

    if (id < nodo->id) {
        return buscar(nodo->izq, id);
    }
    return buscar(nodo->der, id);
}

Nodo* buscarPadre(Nodo *actual, int id) {
    if (actual == NULL || actual->id == id) {
        return NULL;
    }

    if ((actual->izq != NULL && actual->izq->id == id) ||
        (actual->der != NULL && actual->der->id == id)) {
        return actual;
    }

    if (id < actual->id) {
        return buscarPadre(actual->izq, id);
    }
    return buscarPadre(actual->der, id);
}

//Jefferson 

Nodo* encontrarMinimo(Nodo *nodo) {
    while (nodo != NULL && nodo->izq != NULL) {
        nodo = nodo->izq;
    }
    return nodo;
}

Nodo* eliminarNodo(Nodo *nodo, int id, bool &eliminado) {
    if (nodo == NULL) {
        eliminado = false;
        return NULL;
    }

    if (id < nodo->id) {
        nodo->izq = eliminarNodo(nodo->izq, id, eliminado);
    } else if (id > nodo->id) {
        nodo->der = eliminarNodo(nodo->der, id, eliminado);
    } else {
        eliminado = true;

        if (nodo->izq == NULL && nodo->der == NULL) {
            delete nodo;
            return NULL;
        }
        else if (nodo->izq == NULL) {
            Nodo *temp = nodo->der;
            delete nodo;
            return temp;
        } else if (nodo->der == NULL) {
            Nodo *temp = nodo->izq;
            delete nodo;
            return temp;
        }
        else {
            Nodo *sucesor = encontrarMinimo(nodo->der);
            nodo->id = sucesor->id;
            nodo->nombre = sucesor->nombre;
            bool aux = false;
            nodo->der = eliminarNodo(nodo->der, sucesor->id, aux);
        }
    }
    return nodo;
}

void preorden(Nodo *nodo) {
    if (nodo != NULL) {
        cout << "  [" << nodo->id << "] " << nodo->nombre << "\n";
        preorden(nodo->izq);
        preorden(nodo->der);
    }
}

void inorden(Nodo *nodo) {
    if (nodo != NULL) {
        inorden(nodo->izq);
        cout << "  [" << nodo->id << "] " << nodo->nombre << "\n";
        inorden(nodo->der);
    }
}

void postorden(Nodo *nodo) {
    if (nodo != NULL) {
        postorden(nodo->izq);
        postorden(nodo->der);
        cout << "  [" << nodo->id << "] " << nodo->nombre << "\n";
    }
}


