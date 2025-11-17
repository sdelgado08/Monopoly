#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "Casilla.h"

using namespace std;

/* 
Representa a un jugador del juego Monopoly.
Cada jugador tiene un nombre, dinero disponible, posición en el tablero,
estado de cárcel, lista de propiedades que posee y estado de actividad.
El jugador puede moverse por el tablero, comprar propiedades, pagar
alquileres y realizar todas las acciones típicas del juego.
*/
struct Jugador{
    string nombre;                    // Nombre del jugador
    int dinero;                       // Dinero disponible para transacciones
    Casilla* posicion;                // Puntero a la casilla actual del jugador en el tablero
    bool enCarcel;                    // Indica si el jugador está en la cárcel
    vector<string> propiedades;      // Lista de nombres de propiedades que posee el jugador
    int turnosEnCarcel;               // Cantidad de turnos consecutivos que lleva en la cárcel
    bool activo;                      // Indica si el jugador aún está activo (no en bancarrota)
};

//OPERACIONES DEL JUGADOR
/*
pre: nombre no vacío, inicio != null
post: crea un jugador inicializado con el nombre especificado,
      dinero inicial, posición en la casilla de inicio (Go),
      no en cárcel, sin propiedades y activo
*/
Jugador crearJugador(const string &nombre, Casilla* inicio);

/*
pre: jugador válido, pasos >= 0
post: actualiza la posición del jugador avanzando 'pasos' posiciones
      en el tablero desde su posición actual, siguiendo el orden
      circular de las casillas
*/
void moverJugador(Jugador &j, int pasos);

/*
pre: jugador válido, monto >= 0
post: resta el monto especificado del dinero del jugador,
      reduciendo su capital disponible
*/
void pagar(Jugador &j, int monto);

/*
pre: jugador válido, monto >= 0
post: suma el monto especificado al dinero del jugador,
      aumentando su capital disponible
*/
void cobrar(Jugador &j, int monto);

#endif // JUGADOR_H