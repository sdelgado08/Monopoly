#include "ColaCartas.h"
#include <iostream>

using namespace std;

ColaCartas crearColaCartas() {
    ColaCartas c;
    return c;
}

void encolarCarta(ColaCartas &c, const Carta &card) {
    c.cartas.push(card);
}

// Saca la carta del frente y la vuelve a insertar al final
Carta sacarCarta(ColaCartas &c) {
    if (c.cartas.empty()) {
        return {"<sin cartas>", 0};
    }

    Carta primera = c.cartas.front();
    c.cartas.pop();
    c.cartas.push(primera);

    return primera;
}

void mostrarCartas(const ColaCartas &c) {
    cout << "Cartas en la cola: \n";

    // No se pede recorrer el queue directo, así que se clona:
    queue<Carta> copia = c.cartas;

    while (!copia.empty()) {
        Carta card = copia.front();
        copia.pop();

        cout << "  - " << card.mensaje 
             << "  (efecto " << card.efecto << ")\n";
    }
}
