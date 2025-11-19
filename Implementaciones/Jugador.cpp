#include "Jugador.h"
#include "Tablero.h"
#include <iostream>

using namespace std;

/*
Crea un nuevo jugador inicializado con valores por defecto.
El jugador comienza con $1,500 (dinero inicial estándar del Monopoly),
en la casilla de inicio (Go), no en cárcel, sin propiedades y activo.
*/
Jugador crearJugador(const string &nombre, Casilla* inicio){
    Jugador j;
    j.nombre = nombre;
    j.dinero = 1500;  // Dinero inicial estándar del Monopoly
    j.posicion = inicio;  // Comienza en la casilla Go
    j.enCarcel = false;
    j.turnosEnCarcel = 0;
    j.activo = true;  // El jugador está activo al inicio
    return j;
}

/*
Mueve al jugador en el tablero avanzando el número de pasos especificado.
Utiliza la función moverEnTablero para navegar por la lista circular de casillas.
*/
void moverJugador(Jugador &j, int pasos){
    j.posicion = moverEnTablero(j.posicion, pasos);
}

/*
Resta dinero del jugador (pago).
Muestra un mensaje indicando el monto pagado y el dinero restante.
No valida si el jugador tiene suficiente dinero (esa validación debe
hacerse antes de llamar a esta función).
*/
void pagar(Jugador &j, int monto){
    j.dinero -= monto;
    cout << j.nombre << " pago $" << monto << ". Dinero restante: $" << j.dinero << endl;
}

/*
Suma dinero al jugador (cobro).
Muestra un mensaje indicando el monto cobrado y el dinero total.
*/
void cobrar(Jugador &j, int monto){
    j.dinero += monto;
    cout << j.nombre << " cobro $" << monto << ". Dinero total: $" << j.dinero << endl;
}