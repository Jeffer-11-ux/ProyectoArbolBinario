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

void mostrarAncestros(Nodo *raiz, int id) {
    Nodo *objetivo = buscar(raiz, id);
    if (objetivo == NULL) {
        cout << "No se encontro un nodo con ese ID.\n";
        return;
    }

    if (raiz->id == id) {
        cout << "El nodo seleccionado es la raiz; no tiene ancestros.\n";
        return;
    }

    cout << "Linea de ancestros (desde la raiz): ";
    Nodo *actual = raiz;
    while (actual != NULL && actual->id != id) {
        cout << "[" << actual->id << "] " << actual->nombre << " -> ";
        if (id < actual->id) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }
    cout << "[" << objetivo->id << "] " << objetivo->nombre << " (Seleccionado)\n";
}

void mostrarDescendientes(Nodo *raiz, int id) {
    Nodo *nodo = buscar(raiz, id);
    if (nodo == NULL) {
        cout << "No se encontro un nodo con ese ID.\n";
        return;
    }

    cout << "\nNodo seleccionado: [" << nodo->id << "] " << nodo->nombre << "\n";

    if (nodo->izq == NULL && nodo->der == NULL) {
        cout << "El integrante no tiene descendientes registrados.\n";
        return;
    }

    cout << "--- Descendientes directos ---\n";
    if (nodo->izq != NULL) {
        cout << "Hijo izquierdo: [" << nodo->izq->id << "] " << nodo->izq->nombre << "\n";
    } else {
        cout << "Hijo izquierdo: Ninguno\n";
    }

    if (nodo->der != NULL) {
        cout << "Hijo derecho: [" << nodo->der->id << "] " << nodo->der->nombre << "\n";
    } else {
        cout << "Hijo derecho: Ninguno\n";
    }

    cout << "--- Descendencia completa (directos e indirectos) ---\n";
    preorden(nodo->izq);
    preorden(nodo->der);
}

void liberarArbol(Nodo *nodo) {
    if (nodo != NULL) {
        liberarArbol(nodo->izq);
        liberarArbol(nodo->der);
        delete nodo;
    }
}

int main() {
    Nodo *raiz = NULL;
    int opcion, id;
    string nombre;

    do {
        cout << "\n=== ARBOL GENEALOGICO ===\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Ver padre e hijos de un nodo\n";
        cout << "3. Mostrar linea completa de ancestros\n";
        cout << "4. Mostrar descendientes (directos e indirectos)\n";
        cout << "5. Eliminar miembro\n";
        cout << "6. Recorrido InOrden\n";
        cout << "7. Recorrido PreOrden\n";
        cout << "8. Recorrido PostOrden\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "Ingrese ID: ";
                cin >> id;
                cin.ignore();
                cout << "Ingrese nombre: ";
                getline(cin, nombre);

                if (nombre.empty()) {
                    cout << "Error: El nombre no puede estar vacio.\n";
                } else {
                    bool insertado = false;
                    raiz = insertar(raiz, id, nombre, insertado);
                    if (insertado) {
                        cout << "Miembro agregado.\n";
                    }
                }
                break;
            }

            case 2: {
                if (raiz == NULL) {
                    cout << "El arbol esta vacio. Registre miembros primero.\n";
                    break;
                }
                cout << "Ingrese el ID del nodo a consultar: ";
                cin >> id;
                Nodo *nodo = buscar(raiz, id);

                if (nodo == NULL) {
                    cout << "No se encontro un nodo con ese ID.\n";
                } else {
                    cout << "\nNodo seleccionado: [" << nodo->id << "] " << nodo->nombre << "\n";

                    Nodo *padre = buscarPadre(raiz, id);
                    if (padre != NULL) {
                        cout << "Padre: [" << padre->id << "] " << padre->nombre << "\n";
                    } else {
                        cout << "Padre: Ninguno (es la raiz)\n";
                    }

                    if (nodo->izq != NULL) {
                        cout << "Hijo izquierdo: [" << nodo->izq->id << "] " << nodo->izq->nombre << "\n";
                    } else {
                        cout << "Hijo izquierdo: Ninguno\n";
                    }

                    if (nodo->der != NULL) {
                        cout << "Hijo derecho: [" << nodo->der->id << "] " << nodo->der->nombre << "\n";
                    } else {
                        cout << "Hijo derecho: Ninguno\n";
                    }
                }
                break;
            }

            case 3:
                if (raiz == NULL) {
                    cout << "El arbol esta vacio. Registre miembros primero.\n";
                } else {
                    cout << "Ingrese el ID del nodo a consultar: ";
                    cin >> id;
                    mostrarAncestros(raiz, id);
                }
                break;

            case 4:
                if (raiz == NULL) {
                    cout << "El arbol esta vacio. Registre miembros primero.\n";
                } else {
                    cout << "Ingrese el ID del nodo a consultar: ";
                    cin >> id;
                    mostrarDescendientes(raiz, id);
                }
                break;

            case 5: {
                if (raiz == NULL) {
                    cout << "El arbol esta vacio. Registre miembros primero.\n";
                } else {
                    cout << "Ingrese el ID del miembro a eliminar: ";
                    cin >> id;
                    bool eliminado = false;
                    raiz = eliminarNodo(raiz, id, eliminado);
                    if (eliminado) {
                        cout << "Miembro eliminado correctamente.\n";
                    } else {
                        cout << "No se encontro un nodo con ese ID.\n";
                    }
                }
                break;
            }

            case 6:
                cout << "\n--- Recorrido InOrden ---\n";
                if (raiz == NULL) cout << "El arbol esta vacio.\n";
                else inorden(raiz);
                break;

            case 7:
                cout << "\n--- Recorrido PreOrden ---\n";
                if (raiz == NULL) cout << "El arbol esta vacio.\n";
                else preorden(raiz);
                break;

            case 8:
                cout << "\n--- Recorrido PostOrden ---\n";
                if (raiz == NULL) cout << "El arbol esta vacio.\n";
                else postorden(raiz);
                break;

            case 0:
                liberarArbol(raiz);
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);

    return 0;
}
