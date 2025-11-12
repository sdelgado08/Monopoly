#ifndef ESTADOS_H
#define ESTADOS_H

#include "PilaEstados.h"
#include "Jugador.h"
#include "Banco.h"

// Toma una "foto" del estado actual del jugador y el banco
Estado capturarEstado(const Jugador &j, const Banco &b);

// Restaura el estado anterior
void restaurarEstado(const Estado &e, Jugador &j, Banco &b);

#endif
