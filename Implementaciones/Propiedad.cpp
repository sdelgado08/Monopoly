#include "Propiedad.h"
#include <iostream>

Propiedad crearPropiedad(const string &nombre, const string &color, int precio, int renta){
    Propiedad p;
    p.nombre = nombre;
    p.color = color;
    p.precio = precio;
    p.renta = renta;
    p.tieneDueno = false;
    p.dueno = nullptr;
    return p;
}

void mostrarPropiedad(const Propiedad &p){
    cout << "-------------------------------" << endl;
    cout << "Propiedad: " << p.nombre << " (" << p.color << ") "<<endl;
    cout << "Precio: $" << p.precio << endl;
    cout << "Renta: $" << p.renta << endl;

    if(p.tieneDueno && p.dueno != nullptr){
        cout << "Dueno: " << p.dueno->nombre << endl;
    }else{
        cout << "Sin dueno" << endl;
    }
    cout << "-------------------------------" << endl;
}

void asignarDueno(Propiedad &p, Jugador* j){
    if(p.tieneDueno){
        cout << "La propiedad " << p.nombre << " ya tiene dueno." << endl;
        return;
    }
    p.tieneDueno = true;
    p.dueno = j;
    cout << j->nombre << " compro" << p.nombre << " por $" << p.precio << endl;

}

void liberarPropiedad(Propiedad &p){
    if(!p.tieneDueno){
        return;
    }
    cout << "La propiedad " << p.nombre << " vuelve al banco" << endl;
    p.tieneDueno = false;
    p.dueno = nullptr;

}