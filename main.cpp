#include "Tablero.h"
#include "Jugador.h"
#include <iostream>

int main() {
    Tablero t;
    crearTablero(t);
    mostrarTablero(t);

    Jugador j1 = crearJugador("Sebastian", t.inicio);
    cout << j1.nombre << " inicia en: " << j1.posicion->nombre << "\n";

    moverJugador(j1, 7); // mover 7 casillas
    moverJugador(j1, 5); // mover otras 5
    pagar(j1, 200);
    cobrar(j1, 100);

    return 0;
}
