#ifndef PILAESTADOS_H
#define PILAESTADOS_H

#include <stack>
#include <string>

using namespace std;

/* 
Representa un snapshot o "foto" del estado del juego en un momento dado.
Almacena información crítica del jugador (nombre, dinero, posición) y
del banco (dinero total) para permitir restaurar el estado anterior
y implementar funcionalidad de deshacer acciones.
*/
struct Estado {
    string nombreJugador;   // Nombre del jugador al momento de capturar el estado
    int dineroJugador;      // Dinero del jugador al momento de capturar el estado
    int posicionJugador;    // Posición del jugador (índice de casilla) al momento de capturar
    int dineroBanco;        // Dinero total del banco al momento de capturar el estado
};

/* 
Representa una pila (LIFO - Last In First Out) de estados del juego.
Permite guardar múltiples estados en orden temporal y restaurarlos
en orden inverso, implementando funcionalidad de deshacer múltiples pasos.
*/
struct PilaEstados {
    stack<Estado> pila;  // Pila que almacena los estados en orden temporal
};

//OPERACIONES DE PILA DE ESTADOS
/*
pre: -
post: retorna una pila de estados vacía, lista para almacenar estados
      del juego
*/
PilaEstados crearPila();

/*
pre: pila válida, estado válido
post: apila un estado del juego en la parte superior de la pila,
      guardándolo para poder restaurarlo posteriormente
*/
void guardarEstado(PilaEstados &p, const Estado &e);

/*
pre: pila no vacía
post: retorna el estado más reciente (el último guardado) y lo elimina
      de la pila, permitiendo restaurar el estado anterior del juego
*/
Estado deshacerEstado(PilaEstados &p);

/*
pre: pila válida
post: muestra en consola la cantidad de estados almacenados en la pila,
      útil para depuración y verificación del tamaño de la pila
*/
void mostrarTamano(const PilaEstados &p);

#endif // PILAESTADOS_H
