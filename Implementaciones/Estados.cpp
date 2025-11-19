#include "Estados.h"
#include "Tablero.h"

using namespace std;

/*
Captura un snapshot del estado actual del jugador y del banco.
Almacena el nombre del jugador, su dinero, el índice de posición en el tablero
y el dinero total del banco. Este estado puede ser guardado en una pila
para permitir funcionalidad de deshacer acciones.

NOTA: Se requiere el tablero para obtener el índice de la posición del jugador.
*/
Estado capturarEstado(const Jugador &j, const Banco &b, const Tablero &t) {
    Estado e;
    e.nombreJugador = j.nombre;
    e.dineroJugador = j.dinero;
    // Obtener el índice de la posición actual del jugador en el tablero
    e.posicionJugador = obtenerIndiceCasilla(t, j.posicion);
    e.dineroBanco = b.dineroTotal;
    return e;
}

/*
Restaura el estado del jugador y del banco a los valores guardados
en el objeto Estado. Esto permite revertir cambios y deshacer acciones.
Restaura el dinero del jugador, el dinero del banco y la posición del jugador
en el tablero.
*/
void restaurarEstado(const Estado &e, Jugador &j, Banco &b, const Tablero &t) {
    j.nombre = e.nombreJugador;
    j.dinero = e.dineroJugador;
    // Restaurar la posición del jugador usando el índice guardado
    if(e.posicionJugador >= 0) {
        Casilla* casillaRestaurada = obtenerCasillaPorIndice(t, e.posicionJugador);
        if(casillaRestaurada != nullptr) {
            j.posicion = casillaRestaurada;
        }
    }
    b.dineroTotal = e.dineroBanco;
}
