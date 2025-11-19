#include "JuegoMonopoly.h"
#include <iostream>

using namespace std;

int main() {
    cout << "----------------------------------------" << endl;
    cout << "                MONOPOLY"                 << endl;
    cout << "----------------------------------------" << endl << endl;
    
    Juego juego;
    inicializarJuego(juego, 4);
    
    cout << "Juego iniciado con " << juego.numJugadores << " jugadores." << endl;
    
    int turno = 0;
    const int MAX_TURNOS = 100;
    
    // Loop principal del juego
    while (turno < MAX_TURNOS && contarJugadoresActivos(juego) > 1) {
        Jugador &jugadorActual = juego.jugadores[juego.turnActual % juego.numJugadores];
        
        if (jugadorActual.activo) {
            turnoJugador(jugadorActual, juego);
            verificarBancarrota(jugadorActual);
        }
        
        juego.turnActual++;
        turno++;
    }
    
    cout << endl << "---------------------------------------------------------" << endl;
    cout << "                       FIN DEL JUEGO"                              << endl;
    cout << "---------------------------------------------------------" << endl << endl;
    
    // Mostrar ganador
    for (int i = 0; i < juego.numJugadores; i++) {
        if (juego.jugadores[i].activo) {
            cout << "* " << juego.jugadores[i].nombre << " es el ganador!" << endl;
            cout << "Dinero final: $" << juego.jugadores[i].dinero << endl;
        }
    }
    
    return 0;
}