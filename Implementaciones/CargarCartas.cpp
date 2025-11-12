#include "CargarCartas.h"

// Función auxiliar para encolar una carta más fácil
static void add(ColaCartas &c, const string &mensaje, int efecto) {
    Carta card;
    card.mensaje = mensaje;
    card.efecto = efecto; 
    encolarCarta(c, card);
}

// --------------------------
//  ARCA COMUNAL (16 cartas)
// --------------------------

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
