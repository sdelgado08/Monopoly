#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>
#include "Jugador.h"

// Representa una propiedad comprable del Monopoly
struct Propiedad{
    string nombre;      // Nombre de la propiedad
    string color;       // Color del grupo de propiedades
    int precio;         // Precio de compra
    int renta;          // Valor de renta que se cobra
    bool tieneDueno;    // Indica si la propiedad tiene dueño
    Jugador* dueno;     // Puntero al jugador que es dueño, null si no tiene dueño
};

//OPERACIONES DE LA PROPIEDAD
/*
pre: valores válidos, precio > 0
post: devuelve una propiedad sin dueño
*/
Propiedad crearPropiedad(const string &nombre, const string &color, int precio, int renta);

/*
pre: propiedad válida
post: muestra los datos de la propiedad
*/
void mostrarPropiedad(const Propiedad &p);

/*
pre: propiedad válida y jugador existente
post: asigna el dueño a la propiedad
*/
void asignarDueno(Propiedad &p, Jugador* j);

/*
pre: propiedad válida
post: elimina el dueño de la propiedad
*/
void liberarPropiedad(Propiedad &p);

#endif // PROPIEDAD_H