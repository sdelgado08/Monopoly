#include "Banco.h"
#include <iostream>

Banco crearBanco(){
    Banco b;
    b.dineroTotal = 20000;  // Dinero inicial del banco
    b.propiedades = {}; // Inicialmente sin propiedades
    return b;
}

void depositarDinero(Banco &b, int monto){
    b.dineroTotal += monto;
    cout << "El banco recibio $" << monto << ". Total actual: $" << b.dineroTotal << endl;
}

void retirarBanco(Banco &b, int monto){
    if(b.dineroTotal < monto){
        cout << "El banco no tiene suficiente dinero" << endl;
        return;
    }
    b.dineroTotal -= monto;
    cout << " El banco retiro $" << monto << ". Total restante: $" << b.dineroTotal << endl;
}

void cobrarBanco(Banco &b, Jugador &j, int monto){
    if(j.dinero < monto){
        cout << j.nombre << " no tiene suficiente dinero para pagar $" << monto << endl;
        return;
    }
    j.dinero -= monto;
    b.dineroTotal += monto;
    cout << j.nombre << " pago $" << monto << " al banco. Dinero restante del jugador: $" << j.dinero << endl;
}

void pagarBanco(Banco &b, Jugador &j, int monto){
    if(b.dineroTotal < monto){
        cout << "El banco no tiene suficiente dinero para pagar" << endl;
        return;
    }
    j.dinero += monto;
    b.dineroTotal -= monto;
    cout << "El banco pago $" << monto << " a" << j.nombre << ". Dinero del jugador: $" << j.dinero << endl;
}

void venderPropiedad(Banco &b, Jugador &j, Propiedad &p){
    if(p.tieneDueno){
        cout << "La propiedad " << p.nombre << " ya tiene dueno." << endl;
        return;
    }
    if(j.dinero < p.precio){
        cout << j.nombre << " no tiene suficiente dinero para comprar " << p.nombre << endl;
        return;
    }
    j.dinero -= p.precio;
    b.dineroTotal += p.precio;
    asignarDueno(p, &j);

    cout << j.nombre << " compro " << p.nombre << " por $" << p.precio << ". Dinero restante: $" << j.dinero << endl;
}