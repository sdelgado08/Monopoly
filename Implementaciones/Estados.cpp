#include "Estados.h"

Estado capturarEstado(const Jugador &j, const Banco &b) {
    Estado e;
    e.nombreJugador = j.nombre;
    e.dineroJugador = j.dinero;
    e.posicionJugador = j.posicion;
    e.dineroBanco = b.dineroTotal;
    return e;
}

void restaurarEstado(const Estado &e, Jugador &j, Banco &b) {
    j.nombre = e.nombreJugador;
    j.dinero = e.dineroJugador;
    j.posicion = e.posicionJugador;
    b.dineroTotal = e.dineroBanco;
}
