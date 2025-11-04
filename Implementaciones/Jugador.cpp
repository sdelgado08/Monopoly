#include "Jugador.h"
#include "Tablero.h"
#include <iostream>

Jugador crearJugador(const string &nombre, Casilla* inicio){
    Jugador j;
    j.nombre = nombre;
    j.dinero = 1500; // Dinero inicial estándar
    j.posicion = inicio;
    j.enCarcel = false;
    return j;
}

void moverJugador(Jugador &j, int pasos){
    j.posicion = moverEnTablero(j.posicion, pasos);
    cout << j.nombre << " se movio a: " << j.posicion->nombre << endl;
}

void pagar(Jugador &j, int monto){
    j.dinero -= monto;
    cout << j.nombre << " pago $" << monto << ". Dinero restante: $" << j.dinero << endl;
}

void cobrar(Jugador &j, int monto){
    j.dinero += monto;
    cout << j.nombre << " cobro $" << monto << ". Dinero total: $" << j.dinero << endl;
}