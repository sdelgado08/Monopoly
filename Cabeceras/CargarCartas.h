#ifndef CARGARCARTAS_H
#define CARGARCARTAS_H

#include "ColaCartas.h"

/*
pre: cola válida (puede estar vacía o contener cartas previas)
post: carga las 16 cartas de Arca Comunal en la cola especificada,
      cada carta contiene un mensaje y un efecto a ejecutar cuando
      un jugador caiga en una casilla de Arca Comunal
*/
void cargarArcaComunal(ColaCartas &c);

/*
pre: cola válida (puede estar vacía o contener cartas previas)
post: carga las 16 cartas de Casualidad en la cola especificada,
      cada carta contiene un mensaje y un efecto a ejecutar cuando
      un jugador caiga en una casilla de Casualidad
*/
void cargarCasualidad(ColaCartas &c);

#endif // CARGARCARTAS_H
