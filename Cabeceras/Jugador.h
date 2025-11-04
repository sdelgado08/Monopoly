#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Casilla.h"

struct Jugador{
    string nombre;        // Nombre del jugador
    int dinero;          // Dinero disponible
    Casilla* posicion;   // Puntero a la casilla actual del jugador
    bool enCarcel;     // Indica si el jugador está en la cárcel
};

/*
pre: nombre no vacío
post: jugador inicializado en la casilla de inicio (Go)
*/
Jugador crearJugador(const string &nombre, Casilla* inicio);

/*
pre: jugador válido, pasos >= 0
post: actualiza la posición del jugador en el tablero
*/
void moverJugador(Jugador &j, int pasos);

/*
pre: jugador válido, monto >= 0
post: resta el monto del dinero del jugador
*/
void pagar(Jugador &j, int monto);

/*
pre: jugador válido, monto >= 0
post: suma el monto al dinero del jugador
*/
void cobrar(Jugador &j, int monto);

#endif // JUGADOR_H