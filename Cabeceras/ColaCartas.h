#ifndef COLACARTAS_H
#define COLACARTAS_H

#include <string>
#include <queue>
using namespace std;

/* 
Representa una carta individual del juego (Arca Comunal o Casualidad).
Cada carta contiene un mensaje que se muestra al jugador y un efecto
numérico que determina la acción a ejecutar.
*/
struct Carta {
    string mensaje;   // Texto mostrado al jugador al sacar la carta
    int efecto;       // Código numérico que representa la acción a ejecutar
                      // (1 = cobrar, 2 = pagar, 3 = mover, etc.)
};

/* 
Representa una cola de cartas (Arca Comunal o Casualidad).
Utiliza una estructura de datos cola (FIFO) para mantener el orden
de las cartas y permitir el comportamiento circular típico del Monopoly,
donde al sacar una carta, esta se vuelve a colocar al final.
*/
struct ColaCartas {
    queue<Carta> cartas;  // Cola que almacena las cartas en orden
};

//OPERACIONES DE COLA DE CARTAS
/*
pre: -
post: retorna una cola de cartas vacía, lista para ser poblada
*/
ColaCartas crearColaCartas();

/*
pre: cola válida, carta válida
post: agrega una carta al final de la cola, manteniendo el orden
      de las cartas existentes
*/
void encolarCarta(ColaCartas &c, const Carta &card);

/*
pre: cola no vacía
post: retorna la carta que está al frente de la cola y la vuelve
      a colocar al final, simulando el comportamiento circular
      del Monopoly donde las cartas se reciclan
*/
Carta sacarCarta(ColaCartas &c);

/*
pre: cola válida
post: muestra en consola todas las cartas de la cola en orden,
      útil para depuración y verificación del contenido
*/
void mostrarCartas(const ColaCartas &c);

#endif // COLACARTAS_H