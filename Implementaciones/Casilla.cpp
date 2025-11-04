#include "Casilla.h"
#include <iostream>

Casilla* crearCasilla (const string &nombre, const string &tipo, int precio){
    Casilla* nuevaCasilla = new Casilla;
    nuevaCasilla->nombre = nombre;
    nuevaCasilla->tipo = tipo;
    nuevaCasilla->precio = precio;
    nuevaCasilla->siguiente = nullptr;
    nuevaCasilla->anterior = nullptr;
    return nuevaCasilla;
}

void mostrarCasilla (const Casilla* c){
    if (c == nullptr){
        cout << "(Casilla nula)" << endl;
        return;
    }

    cout << c->nombre << " [" << c->tipo << "]";
    if (c->precio > 0){
        cout << " - Precio: $" << c->precio;
    }
    cout << endl;
}

void enlazarCasillas (Casilla* a, Casilla* b){
    if(a == nullptr || b == nullptr){
        return;
    }

    a->siguiente = b;
    b->anterior = a;
}

void eliminarCasilla (Casilla* c){
    if(c != nullptr){
        delete c;
    }
}