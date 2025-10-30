#ifndef CASILLA_H
#define CASILLA_H

#include <string>

/* 
Representa una posición individual del tablero de Monopoly.
Cada casilla tiene un nombre, un tipo, un precio (si aplica)
y punteros a la casilla siguiente y anterior, formando una
lista circular doblemente enlazada.
*/

using namespace std;

struct Casilla{
    string nombre;     // Nombre de la casilla (ej: "Go", "Cárcel", "Propiedad A")
    string tipo;       // Tipo de casilla (Propiedad, Go, Carcel, VayaCarcel, etc.)

    int precio;             // Valor de compra o 0 si no aplica
    
    Casilla* siguiente;     // Puntero a la siguiente casilla (sentido horario)
    Casilla* anterior;      // Puntero a la casilla anterior (sentido antihorario)
};

#endif // CASILLA_H