#ifndef COLACARTAS_H
#define COLACARTAS_H

#include <string>
#include <queue>
using namespace std;

// Cada carta del juego
struct Carta {
    string mensaje;   // texto mostrado al jugador
    int efecto;       // representa la acción (1 = cobrar, 2 = pagar, 3 = mover, etc.)
};

// Cola de cartas (Arca Comunal o Casualidad)
struct ColaCartas {
    queue<Carta> cartas;
};

/*
pre: vacío
post: retorna una cola vacía
*/
ColaCartas crearColaCartas();

/*
pre: cola válida
post: agrega una carta al final de la cola
*/
void encolarCarta(ColaCartas &c, const Carta &card);

/*
pre: cola no vacía
post: retorna la carta siguiente y la vuelve a meter al final (comportamiento Monopoly)
*/
Carta sacarCarta(ColaCartas &c);

/*
pre: cola válida
post: muestra todas las cartas (debug)
*/
void mostrarCartas(const ColaCartas &c);

#endif