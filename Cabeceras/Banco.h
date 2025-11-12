#ifndef BANCO_H
#define BANCO_H

#include <map>
#include <string>
#include "Jugador.h"
#include "Propiedad.h"

// Representa al banco del Monopoly
struct Banco{
    int dineroTotal;                      // Dinero total del banco
    map<string, Propiedad> propiedades;        // Propiedades disponibles sin dueño
};

//OPERACIONES DEL BANCO
/*
pre: -
post: crea un banco con dinero inicial y propiedades disponibles
*/
Banco crearBanco();

/*
pre: banco válido, propiedad válida
post: registra una propiedad en el banco
*/
void registrarPropiedad(Banco &b, const Propiedad &p);

/*
pre: banco válido, monto >= 0
post: aumenta el dinero total del banco
*/

void depositarDinero(Banco &b, int monto);

/*
pre: banco válido, monto >= 0
post: reduce el dinero del banco si tiene suficiente
*/
void retirarBanco(Banco &b, int monto);

/*
pre: jugador y banco válidos, monto >= 0
post: el jugador paga al banco
*/
void cobrarBanco(Banco &b, Jugador &j, int monto);

/*
pre: jugador y banco válidos, monto >= 0
post: el banco paga al jugador
*/
void pagarBanco(Banco &b, Jugador &j, int monto);

/*
pre: banco válido, propiedad válida y jugador válido
post: transfiere una propiedad al jugador
*/
void venderPropiedad(Banco &b, Jugador &j, const string &nombreProp);

bool bancoVenderPropiedad(Banco &b, Jugador &j, const string &nombreProp);

bool bancoComprarPropiedad(Banco &b, Jugador &j, const string &nombreProp);

#endif // BANCO_H