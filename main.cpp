#include "Banco.h"
#include "Propiedad.h"
#include "Jugador.h"
#include <iostream>

int main() {
    Banco banco = crearBanco();
    Jugador j = {"Sebastian", 1500, nullptr, false};
    Propiedad p = crearPropiedad("Baltic Avenue", "Marron", 60, 4);

    cout << "\n--- Estado inicial ---\n";
    mostrarPropiedad(p);

    cout << "\n--- Compra de propiedad ---\n";
    venderPropiedad(banco, j, p);

    cout << "\n--- Cobro de impuesto ---\n";
    cobrarBanco(banco, j, 200);

    cout << "\n--- Pago al pasar por 'Go' ---\n";
    pagarBanco(banco, j, 200);

    cout << "\n--- Estado final ---\n";
    mostrarPropiedad(p);
    return 0;
}

