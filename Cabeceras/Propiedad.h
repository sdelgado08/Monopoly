#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>
#include <array>
#include <map>
#include "Jugador.h"

using namespace std;

/* 
Representa una propiedad del juego Monopoly.
Una propiedad puede ser una propiedad normal, un ferrocarril o un servicio público.
Cada propiedad tiene un precio de compra, alquileres según el número de casas/hoteles,
y puede ser comprada, vendida, hipotecada y mejorada por los jugadores.
*/
struct Propiedad {
    string nombre;              // Nombre de la propiedad (ej: "Park Place", "Reading Railroad")
    string color;               // Color del grupo de propiedades (ej: "Azul", "Marrón")
    int precio;                 // Precio de compra de la propiedad
    int alquiler[6];            // Alquiler según número de mejoras: [0] sin casas, [1-4] con 1-4 casas, [5] con hotel
    int numCasas;               // Número de casas construidas (0-4) o 5 si tiene hotel
    int precioCasa;             // Precio por construir una casa o hotel
    int hipoteca;               // Valor que recibe el dueño al hipotecar la propiedad
    bool tieneDueno;            // Indica si la propiedad tiene un dueño asignado
    bool hipotecada;            // Indica si la propiedad está hipotecada (no genera alquiler)
    bool esFerrocarril;         // Indica si es una propiedad tipo ferrocarril
    bool esServicios;           // Indica si es una propiedad tipo servicios públicos
    Jugador* dueno;             // Puntero al jugador dueño de la propiedad (null si no tiene dueño)
    bool disponible;           // Indica si está disponible en el banco para compra (sin dueño)
};

//OPERACIONES DE PROPIEDAD
/*
pre: valores válidos (alquiler_vals[6] contiene los 6 valores de alquiler),
     precio >= 0, precioCasa >= 0, hipoteca >= 0
post: devuelve una propiedad inicializada con los valores especificados,
      sin dueño, no hipotecada, disponible para compra
*/
Propiedad crearPropiedad(const string &nombre,
                         const string &color,
                         int precio,
                         const int alquiler_vals[6],
                         int precioCasa,
                         int hipoteca,
                         bool esFerrocarril = false,
                         bool esServicios = false);

/*
pre: mapa válido (puede estar vacío)
post: carga todas las propiedades del Monopoly original en el mapa,
      incluyendo propiedades normales, ferrocarriles y servicios públicos,
      con sus respectivos valores y características
*/
void cargarTodasLasPropiedades(map<string, Propiedad> &m);

/*
pre: propiedad válida
post: imprime en consola la información completa de la propiedad:
      nombre, color, precio, alquileres, estado de mejoras, etc.
*/
void mostrarPropiedad(const Propiedad &p);

/*
pre: propiedad disponible (sin dueño), jugador válido con dinero >= precio
post: el jugador compra la propiedad: se le asigna como dueño, se descuenta
      el precio de su dinero y la propiedad deja de estar disponible;
      retorna true si la compra fue exitosa, false en caso contrario
*/
bool comprarPropiedad(Propiedad &p, Jugador &j);

/*
pre: propiedad perteneciente al jugador j, propiedad no hipotecada
post: el jugador vende la propiedad al banco: recibe la mitad del precio
      original, la propiedad vuelve a estar disponible y el jugador deja
      de ser dueño; retorna true si la venta fue exitosa, false en caso contrario
*/
bool venderPropiedad(Propiedad &p, Jugador &j);

/*
pre: propiedad tiene dueño == j, propiedad no está hipotecada
post: la propiedad queda hipotecada (no genera alquiler), el dueño recibe
      el valor de hipoteca en su dinero; retorna true si la hipoteca fue
      exitosa, false en caso contrario
*/
bool hipotecarPropiedad(Propiedad &p, Jugador &j);

/*
pre: propiedad tieneDueno == true, dueno == j, numCasas < 4,
     jugador tiene suficiente dinero para comprar la casa
post: compra una casa en la propiedad: incrementa numCasas y descuenta
      precioCasa del dinero del jugador; retorna true si la compra fue
      exitosa, false en caso contrario
*/
bool comprarCasa(Propiedad &p, Jugador &j);

/*
pre: propiedad tieneDueno == true, dueno == j, numCasas == 4,
     jugador tiene suficiente dinero para comprar el hotel
post: convierte las 4 casas en hotel (numCasas = 5) y descuenta precioCasa
      del dinero del jugador; retorna true si la compra fue exitosa,
      false en caso contrario
*/
bool comprarHotel(Propiedad &p, Jugador &j);

/*
pre: propiedad tieneDueno == true, dueno == j, numCasas > 0
post: vende una casa de la propiedad: decrementa numCasas y el dueño
      recibe la mitad del precioCasa en su dinero; retorna true si la
      venta fue exitosa, false en caso contrario
*/
bool venderCasa(Propiedad &p, Jugador &j);

/*
pre: propiedad válida, inquilino != null
post: si la propiedad tiene dueño y no está hipotecada, el inquilino paga
      el alquiler correspondiente según el número de casas/hotel y el dueño
      recibe el dinero; retorna true si se cobró el alquiler, false en caso
      contrario (sin dueño, hipotecada, etc.)
*/
bool cobrarAlquiler(Propiedad &p, Jugador &inquilino);

#endif // PROPIEDAD_H
