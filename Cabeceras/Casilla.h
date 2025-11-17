#ifndef CASILLA_H
#define CASILLA_H

#include <string>
#include <map>

using namespace std;

// Forward declaration para evitar dependencia circular
// La definición completa se incluirá en Casilla.cpp
struct Propiedad;
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

//OPERACIONES DE CASILLA
/*
pre: nombre y tipo no vacíos, precio >= 0
post: devuelve un puntero a una nueva casilla creada con los valores
      especificados, con punteros siguiente y anterior inicializados en null
*/
Casilla* crearCasilla (const string &nombre, const string &tipo, int precio);

/*
pre: c != null
post: imprime en consola la información de la casilla (nombre, tipo y precio)
*/
void mostrarCasilla (const Casilla* c);

/*
pre: c != null, propiedades válido (puede estar vacío)
post: imprime en consola la información de la casilla (nombre, tipo, precio)
      y si es una propiedad, también muestra su color
*/
void mostrarCasilla (const Casilla* c, const map<string, Propiedad> &propiedades);

/*
pre: a != null && b != null
post: enlaza la casilla 'a' con la casilla 'b' en ambas direcciones,
      estableciendo a->siguiente = b y b->anterior = a
*/
void enlazarCasillas (Casilla* a, Casilla* b);

/*
pre: c != null
post: libera la memoria asociada a la casilla, eliminándola completamente
*/
void eliminarCasilla (Casilla* c);

#endif // CASILLA_H