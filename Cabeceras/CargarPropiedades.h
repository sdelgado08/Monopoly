#ifndef CARGARPROPIEDADES_H
#define CARGARPROPIEDADES_H

using namespace std;

#include "Banco.h"

/*
pre: banco válido
post: registra todas las propiedades del Monopoly original en el banco,
      incluyendo propiedades normales, ferrocarriles y servicios públicos,
      con sus respectivos precios, alquileres y características
*/
void cargarPropiedades(Banco &b);

#endif 