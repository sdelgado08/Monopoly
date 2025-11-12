#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>
#include <array>
#include "Jugador.h"

using namespace std;

// ----------------------------------------------------------
// ESTRUCTURA: Propiedad
// ----------------------------------------------------------
struct Propiedad {
    string nombre;
    string color;
    int precio;                 // precio de compra
    int alquiler[6];            // alquiler según 0..5 casas (5 = hotel)
    int numCasas;               // 0..4 casas, 5 = hotel
    int precioCasa;             // precio por casa
    int hipoteca;               // valor que recibe el dueño al hipotecar
    bool tieneDueno;
    bool hipotecada;
    bool esFerrocarril;
    bool esServicios;
    Jugador* dueno;             // nullptr si no tiene dueño
    bool disponible;            // true si está en el banco (sin dueño)
};

// ----------------------------------------------------------
// pre: valores válidos (alquiler[6] contiene los 6 valores)
// post: devuelve una propiedad inicializada sin dueño
Propiedad crearPropiedad(const string &nombre,
                         const string &color,
                         int precio,
                         const int alquiler_vals[6],
                         int precioCasa,
                         int hipoteca,
                         bool esFerrocarril = false,
                         bool esServicios = false);

// ----------------------------------------------------------
// pre: propiedad válida
// post: imprime la información de la propiedad
void mostrarPropiedad(const Propiedad &p);

// ----------------------------------------------------------
// pre: propiedad disponible y jugador con dinero >= precio
// post: el jugador compra la propiedad (se le asigna y se descuenta dinero)
bool comprarPropiedad(Propiedad &p, Jugador &j);

// ----------------------------------------------------------
// pre: propiedad perteneciente al jugador j
// post: el jugador vende la propiedad al banco (recibe la mitad del precio)
bool venderPropiedad(Propiedad &p, Jugador &j);

// ----------------------------------------------------------
// pre: propiedad tiene dueño == j y no está hipotecada
// post: la propiedad queda hipotecada y el dueño recibe el valor de hipoteca
bool hipotecarPropiedad(Propiedad &p, Jugador &j);

// ----------------------------------------------------------
// pre: propiedad tieneDueno == true && dueno==j && numCasas < 4
// post: compra una casa (incrementa numCasas y descuenta precioCasa)
bool comprarCasa(Propiedad &p, Jugador &j);

// ----------------------------------------------------------
// pre: propiedad tieneDueno == true && dueno==j && numCasas == 4
// post: convierte las 4 casas en hotel (numCasas = 5) y descuenta precioCasa
bool comprarHotel(Propiedad &p, Jugador &j);

// ----------------------------------------------------------
// pre: propiedad tieneDueno == true && dueno==j && numCasas > 0
// post: vende una casa (numCasas--), dueño recibe la mitad del precioCasa
bool venderCasa(Propiedad &p, Jugador &j);

// ----------------------------------------------------------
// pre: p tiene dueño (o no). inquilino != nullptr
// post: el inquilino paga el alquiler correspondiente y el dueño recibe el dinero
// Nota: para ferrocarriles/servicios se usa el alquiler definido en p.alquiler[0]
bool cobrarAlquiler(Propiedad &p, Jugador &inquilino);

#endif // PROPIEDAD_H
