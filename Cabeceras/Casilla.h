#ifndef CASILLA_H
#define CASILLA_H

#include <string>

using namespace std;
/* 
Representa una posición individual del tablero de Monopoly.
Cada casilla tiene un nombre, un tipo, un precio (si aplica)
y punteros a la casilla siguiente y anterior, formando una
lista circular doblemente enlazada.
*/

struct Casilla{
    string nombre;     // Nombre de la casilla (ej: "Go", "Cárcel", "Propiedad A")
    string tipo;       // Tipo de casilla (Propiedad, Go, Carcel, VayaCarcel, etc.)
    int precio;             // Valor de compra o 0 si no aplica
    Casilla* siguiente;     // Puntero a la siguiente casilla (sentido horario)
    Casilla* anterior;      // Puntero a la casilla anterior (sentido antihorario)
};

//OPERACIONES DEL TABLERO
/*
pre: nombre y tipo no vacíos
post: devuelve un puntero a una nueva casilla creada
*/
Casilla* crearCasilla (const string &nombre, const string &tipo, int precio);

/*
pre: c =! null
post: imprime en consola la información de la casilla
*/
void mostrarCasilla (const Casilla* c);

/*
pre: a =! null && b =! null
post: enlaza la casilla 'a' con la casilla 'b' en ambas direcciones
*/
void enlazarCasillas (Casilla* a, Casilla* b);

/*
pre: c =! null
post: libera memoria asociada a la casilla 
*/
void eliminarCasilla (Casilla* c);

#endif // CASILLA_H