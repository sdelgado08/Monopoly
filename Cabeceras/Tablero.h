#ifndef TABLERO_H
#define TABLERO_H

#include "Casilla.h"

/* 
Representa el tablero completo de Monopoly como una lista
circular doblemente enlazada de casillas.

Cada casilla apunta tanto a la siguiente, como a la anterior,
lo que permite avanzar y retroceder fácilmente.
*/

struct Tablero{
    Casilla* inicio;        //Puntero a la primera casilla
    int totalCasillas;      //Cantidad total de casillas
};


//OPERACIONES DEL TABLERO
/*
pre: -
post: tablero inicializado con un conjunto de casillas conectadas
      circularmente (doblemente enlazadas)
*/
void crearTablero (Tablero &t);

/*
pre: t.inicio != null
post: muestra en consola el nombre y tipo de cada casilla,
      realizando un recorrido circular completo.
*/
void mostrarTablero (const Tablero &t);

/*
pre: actual != null && pasos <= 0
post: devuelve puntero a la casilla resultante después de
      avanzar 'pasos' posiciones en el sentido horario.
*/
Casilla* moverEnTablero (Casilla* actual, int pasos);

/*
pre: actual != null && pasos >= 0
post: devuelve puntero a la casilla resultante después de
      retroceder 'pasos' posiciones en el sentido antihorario.
*/
Casilla* retrocederEnTablero (Casilla* actual, int pasos);

#endif //TABLERO_H