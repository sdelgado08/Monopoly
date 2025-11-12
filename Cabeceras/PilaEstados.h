#ifndef PILAESTADOS_H
#define PILAESTADOS_H

#include <stack>
#include <string>

using namespace std;

struct Estado {
    string nombreJugador;  
    int dineroJugador;
    int posicionJugador;
    int dineroBanco;
};

// La pila de estados
struct PilaEstados {
    stack<Estado> pila;
};

/*
pre: nada
post: retorna una pila vacía
*/
PilaEstados crearPila();

/*
pre: pila y estado válidos
post: apila un estado del juego
*/
void guardarEstado(PilaEstados &p, const Estado &e);

/*
pre: pila no vacía
post: retorna el estado anterior y lo elimina de la pila
*/
Estado deshacerEstado(PilaEstados &p);

/*
pre: pila válida
post: muestra cuántos estados tiene (debug)
*/
void mostrarTamano(const PilaEstados &p);

#endif
