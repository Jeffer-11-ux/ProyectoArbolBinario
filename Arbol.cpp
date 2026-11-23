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
