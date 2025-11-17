#ifndef ESTADOS_H
#define ESTADOS_H

#include "PilaEstados.h"
#include "Jugador.h"
#include "Banco.h"
#include "Tablero.h"

/*
pre: jugador válido, banco válido, tablero válido
post: crea y retorna un objeto Estado que contiene una "foto" o snapshot
      del estado actual del jugador (nombre, dinero, posición como índice)
      y del banco (dinero total), permitiendo guardar el estado para poder
      restaurarlo posteriormente (útil para funcionalidad de deshacer)
*/
Estado capturarEstado(const Jugador &j, const Banco &b, const Tablero &t);

/*
pre: estado válido, jugador válido, banco válido, tablero válido
post: restaura el estado del jugador y del banco a los valores guardados
      en el objeto Estado, revirtiendo cualquier cambio realizado desde
      que se capturó el estado. Restaura el dinero, la posición del jugador
      y el dinero del banco.
*/
void restaurarEstado(const Estado &e, Jugador &j, Banco &b, const Tablero &t);

#endif // ESTADOS_H
