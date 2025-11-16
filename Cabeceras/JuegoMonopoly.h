#ifndef JUEGOMONOPOLY_H
#define JUEGOMONOPOLY_H

#include "Banco.h"
#include "Propiedad.h"
#include "Jugador.h"
#include "Tablero.h"
#include "CargarPropiedades.h"
#include "CargarCartas.h"
#include "PilaEstados.h"
#include <map>

using namespace std;

/* 
Representa el estado completo del juego Monopoly.
Contiene todos los componentes necesarios para ejecutar una partida:
el tablero con sus casillas, el banco, los jugadores, las propiedades,
las colas de cartas (Arca Comunal y Casualidad) y la pila de estados
para la funcionalidad de deshacer turnos.
*/
struct Juego {
    Tablero tablero;                          // Tablero circular con todas las casillas
    Banco banco;                              // Banco que gestiona dinero y propiedades disponibles
    Jugador jugadores[4];                     // Array de hasta 4 jugadores
    int numJugadores;                         // Cantidad real de jugadores activos (1-4)
    int turnActual;                           // Índice del jugador cuyo turno es actual (0-3)
    map<string, Propiedad> propiedades;       // Mapa con todas las propiedades del juego (indexadas por nombre)
    ColaCartas arcaComunal;                   // Cola de cartas de Arca Comunal
    ColaCartas casualidad;                    // Cola de cartas de Casualidad
    PilaEstados pilaEstados;                  // Pila de estados para funcionalidad de deshacer turnos
};

//OPERACIONES DEL JUEGO
/*
pre: -
post: simula el lanzamiento de dos dados y retorna un número aleatorio
      entre 1 y 6 (resultado de un dado), típicamente se suman dos
      resultados para obtener el total de pasos a avanzar
*/
int tirarDados();

/*
pre: jugador válido, juego válido
post: imprime en consola el estado actual del jugador, incluyendo
      nombre, dinero, posición actual, propiedades (con sus colores)
      y estado de cárcel
*/
void mostrarEstadoJugador(const Jugador &j, const Juego &juego);

/*
pre: jugador válido, casilla válida, juego válido
post: muestra en consola el menú de acciones disponibles para el jugador
      según el tipo de casilla en la que se encuentra (comprar propiedad,
      pagar alquiler, sacar carta, etc.)
*/
void mostrarMenuAcciones(Jugador &j, Casilla *casilla, Juego &juego);

/*
pre: carta válida, jugador válido, juego válido
post: ejecuta el efecto de la carta en el jugador según el código
      de efecto (cobrar dinero, pagar dinero, mover a otra casilla, etc.)
*/
void procesarCarta(Carta &carta, Jugador &j, Juego &juego);

/*
pre: opción válida (1-2), jugador válido, casilla válida, juego válido
post: procesa la acción seleccionada por el jugador desde el menú,
      ejecutando la operación correspondiente (comprar, pasar, etc.)
*/
void procesarAccion(int opcion, Jugador &j, Casilla *casilla, Juego &juego);

/*
pre: juego válido, numJugadores >= 1 y <= 4
post: inicializa completamente el juego: crea el tablero con todas las
      casillas, inicializa el banco con dinero y propiedades, crea los
      jugadores, carga las propiedades y las cartas (Arca Comunal y Casualidad)
*/
void inicializarJuego(Juego &juego, int numJugadores = 4);

/*
pre: jugador válido, juego válido
post: ejecuta un turno completo del jugador: lanza los dados, mueve
      al jugador en el tablero, procesa la casilla en la que cayó
      y muestra el menú de acciones disponibles
*/
void turnoJugador(Jugador &j, Juego &juego);

/*
pre: jugador válido
post: retorna true si el jugador está en bancarrota (dinero <= 0),
      indicando que ha perdido y debe ser eliminado del juego
*/
bool verificarBancarrota(Jugador &j);

/*
pre: jugador válido, propiedad válida, juego válido
post: retorna true si el jugador posee TODAS las propiedades del mismo
      color que la propiedad especificada, lo cual es necesario para
      poder construir casas y hoteles
*/
bool poseeTodasLasPropiedadesDelColor(const Jugador &j, const Propiedad &prop, const Juego &juego);

/*
pre: juego válido
post: retorna la cantidad de jugadores que aún están activos
      (no han caído en bancarrota), útil para determinar si el juego
      debe continuar o terminar
*/
int contarJugadoresActivos(Juego &juego);

#endif // JUEGOMONOPOLY_H
