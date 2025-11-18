#include "CargarCartas.h"

using namespace std;

/*
Función para crear y encolar una carta de forma más sencilla.
Crea una carta con el mensaje y efecto especificados y la añade a la cola.
*/
static void add(ColaCartas &c, const string &mensaje, int efecto) {
    Carta card;
    card.mensaje = mensaje;
    card.efecto = efecto; 
    encolarCarta(c, card);
}

// --------------------------
//  ARCA COMUNAL (16 cartas)
// --------------------------

/*
Carga las 16 cartas de Arca Comunal en la cola especificada.
Cada carta tiene un mensaje descriptivo y un código de efecto:
- Efecto 1: Cobrar dinero del banco
- Efecto 2: Pagar dinero al banco
- Efecto 3: Avanzar hasta Go
- Efecto 4: Ir a la cárcel
- Efecto 5: Cobrar de cada jugador
- Efecto 6: Ir al servicio más cercano
- Efecto 7: Ir al ferrocarril más cercano
*/
void cargarArcaComunal(ColaCartas &c) {
    add(c, "Cobra $200 por error bancario a tu favor.", 1);
    add(c, "Paga $50 por gastos médicos.", 2);
    add(c, "Avanza hasta Go.", 3);
    add(c, "Ve a la cárcel. No pases por Go. No cobres $200.", 4);
    add(c, "Cobra $50 por alquiler de propiedades.", 1);
    add(c, "Paga $100 por reparación de calles.", 2);
    add(c, "Cobra $25 de cada jugador.", 5);
    add(c, "Cobra $100 por inversión exitosa.", 1);
    add(c, "Cobra $20 por servicios prestados.", 1);
    add(c, "Paga $50 por consulta médica.", 2);
    add(c, "Avanza a la casilla más cercana de servicio.", 6);
    add(c, "Cobra $10 por encontrar dinero.", 1);
    add(c, "Paga $50 por reparación de propiedades.", 2);
    add(c, "Ve al ferrocarril más cercano.", 7);
    add(c, "Cobra $100 por recompensa de comunidad.", 1);
    add(c, "Paga $50 por impuestos atrasados.", 2);
}

// --------------------------
//  CASUALIDAD (16 cartas)
// --------------------------

/*
Carga las 16 cartas de Casualidad en la cola especificada.
Cada carta tiene un mensaje descriptivo y un código de efecto:
- Efecto 1: Cobrar dinero del banco
- Efecto 2: Pagar dinero al banco
- Efecto 3: Avanzar hasta Go
- Efecto 4: Ir a la cárcel
- Efecto 7: Ir al ferrocarril más cercano
- Efecto 8: Ir a una propiedad específica
- Efecto 9: Retroceder espacios
- Efecto 10: Avanzar a propiedad más cercana disponible
*/
void cargarCasualidad(ColaCartas &c) {
    add(c, "Avanza hasta Go.", 3);
    add(c, "Ve a Illinois Avenue.", 8);
    add(c, "Ve a St. Charles Place.", 8);
    add(c, "Ve a la cárcel. No pases por Go.", 4);
    add(c, "Retrocede 3 espacios.", 9);
    add(c, "Ve al ferrocarril más cercano.", 7);
    add(c, "Paga $15 por multa de velocidad.", 2);
    add(c, "Cobra $50 por ganar un concurso.", 1);
    add(c, "Paga impuesto por reparación de casas.", 2);
    add(c, "Avanza a la propiedad más cercana en venta.", 10);
    add(c, "Cobra $150 por venta de acciones.", 1);
    add(c, "Ve a Reading Railroad.", 8);
    add(c, "Ve a Boardwalk.", 8);
    add(c, "Paga $20 por tarjeta perdida.", 2);
    add(c, "Recibe $25 por banco por error.", 1);
    add(c, "Cobra $100 por comisión.", 1);
}
