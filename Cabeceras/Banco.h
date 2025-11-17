#ifndef BANCO_H
#define BANCO_H

#include <map>
#include <string>
#include "Jugador.h"
#include "Propiedad.h"

/* 
Representa al banco del juego Monopoly.
El banco gestiona el dinero total disponible y mantiene un registro
de todas las propiedades que aún no han sido compradas por los jugadores.
Actúa como intermediario en todas las transacciones financieras del juego.
*/
struct Banco{
    int dineroTotal;                      // Dinero total del banco
    map<string, Propiedad> propiedades;   // Propiedades disponibles sin dueño (indexadas por nombre)
};

//OPERACIONES DEL BANCO
/*
pre: -
post: crea un banco inicializado con dinero inicial y propiedades disponibles
      listas para ser compradas por los jugadores
*/
Banco crearBanco();

/*
pre: banco válido, propiedad válida
post: registra una propiedad en el banco, haciéndola disponible para compra
*/
void registrarPropiedad(Banco &b, const Propiedad &p);

/*
pre: banco válido, monto >= 0
post: aumenta el dinero total del banco en el monto especificado
*/
void depositarDinero(Banco &b, int monto);

/*
pre: banco válido, monto >= 0
post: reduce el dinero del banco en el monto especificado si tiene suficiente,
      en caso contrario no realiza ningún cambio
*/
void retirarBanco(Banco &b, int monto);

/*
pre: jugador y banco válidos, monto >= 0
post: el jugador paga el monto especificado al banco (dinero del jugador
      se reduce y dinero del banco se aumenta)
*/
void cobrarBanco(Banco &b, Jugador &j, int monto);

/*
pre: jugador y banco válidos, monto >= 0
post: el banco paga el monto especificado al jugador (dinero del banco
      se reduce y dinero del jugador se aumenta)
*/
void pagarBanco(Banco &b, Jugador &j, int monto);

/*
pre: banco válido, propiedad válida y jugador válido
post: transfiere una propiedad del banco al jugador, actualizando
      la propiedad para indicar que tiene dueño
*/
void venderPropiedad(Banco &b, Jugador &j, const string &nombreProp);

/*
pre: banco válido, jugador válido, nombreProp corresponde a una propiedad
      disponible en el banco
post: intenta vender la propiedad al jugador; retorna true si la venta
      fue exitosa (jugador tiene suficiente dinero), false en caso contrario
*/
bool bancoVenderPropiedad(Banco &b, Jugador &j, const string &nombreProp);

/*
pre: banco válido, jugador válido, nombreProp corresponde a una propiedad
      que pertenece al jugador
post: intenta que el banco compre la propiedad del jugador; retorna true
      si la compra fue exitosa, false en caso contrario
*/
bool bancoComprarPropiedad(Banco &b, Jugador &j, const string &nombreProp);

#endif // BANCO_H
