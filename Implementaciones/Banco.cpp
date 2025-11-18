#include "Banco.h"
#include <iostream>

using namespace std;

/*
Crea un banco inicializado con dinero inicial estándar y sin propiedades.
El banco comienza con $20,000 para realizar transacciones con los jugadores.
*/
Banco crearBanco() {
    Banco b;
    b.dineroTotal = 20000;    // Dinero inicial estándar del banco
    return b;
}

/*
Registra una propiedad en el banco, haciéndola disponible para compra.
La propiedad se almacena en el mapa usando su nombre como clave.
*/
void registrarPropiedad(Banco &b, const Propiedad &p) {
    b.propiedades[p.nombre] = p;
}

/*
Incrementa el dinero total del banco en el monto especificado.
Valida que el monto sea positivo antes de realizar la operación.
*/
void depositarDinero(Banco &b, int monto) {
    if (monto < 0) return;  // Validación: no se permiten montos negativos
    b.dineroTotal += monto;
}

/*
Retira dinero del banco si tiene suficiente disponible.
Si el banco no tiene suficiente dinero, muestra un mensaje y no realiza
la operación. Valida que el monto sea positivo.
*/
void retirarBanco(Banco &b, int monto) {
    if (monto < 0) return;  // Validación: no se permiten montos negativos

    // Verificar que el banco tenga suficiente dinero
    if (b.dineroTotal < monto) {
        cout << "El banco no tiene suficiente dinero para retirar $" << monto << endl;
        return;
    }

    b.dineroTotal -= monto;
}

/*
Transfiere dinero del jugador al banco.
Valida que el jugador tenga suficiente dinero antes de realizar la transacción.
Si el jugador no tiene suficiente, muestra un mensaje y no realiza la operación.
*/
void cobrarBanco(Banco &b, Jugador &j, int monto) {
    if (monto < 0) return;  // Validación: no se permiten montos negativos

    // Verificar que el jugador tenga suficiente dinero
    if (j.dinero < monto) {
        cout << j.nombre << " no tiene suficiente dinero para pagar $" << monto << endl;
        return;
    }

    // Realizar la transacción: jugador paga, banco recibe
    j.dinero -= monto;
    b.dineroTotal += monto;
}

/*
Transfiere dinero del banco al jugador.
Valida que el banco tenga suficiente dinero antes de realizar la transacción.
Si el banco no tiene suficiente, muestra un mensaje y no realiza la operación.
*/
void pagarBanco(Banco &b, Jugador &j, int monto) {
    if (monto < 0) return;  // Validación: no se permiten montos negativos

    // Verificar que el banco tenga suficiente dinero
    if (b.dineroTotal < monto) {
        cout << "El banco no tiene suficiente dinero para pagar $" << monto << endl;
        return;
    }

    // Realizar la transacción: banco paga, jugador recibe
    j.dinero += monto;
    b.dineroTotal -= monto;
}

/*
Permite que un jugador compre una propiedad del banco.
Realiza las siguientes validaciones:
1. Verifica que la propiedad exista en el banco
2. Verifica que la propiedad no tenga dueño
3. Verifica que el jugador tenga suficiente dinero
Si todas las validaciones pasan, transfiere la propiedad al jugador y
actualiza el dinero del banco y del jugador.
*/
void venderPropiedad(Banco &b, Jugador &j, const string &nombreProp) {
    // Buscar la propiedad en el mapa del banco
    auto it = b.propiedades.find(nombreProp);

    // Validación 1: verificar que la propiedad exista
    if (it == b.propiedades.end()) {
        cout << "La propiedad '" << nombreProp << "' no existe en el banco.\n";
        return;
    }

    Propiedad &p = it->second;

    // Validación 2: verificar que la propiedad no tenga dueño
    if (p.tieneDueno) {
        cout << "La propiedad '" << p.nombre << "' ya tiene dueno.\n";
        return;
    }

    // Validación 3: verificar que el jugador tenga dinero suficiente
    if (j.dinero < p.precio) {
        cout << j.nombre << " no tiene suficiente dinero para comprar '" << p.nombre << "'.\n";
        return;
    }

    // Realizar la transacción: jugador paga el precio
    j.dinero -= p.precio;
    b.dineroTotal += p.precio;

    // Asignar la propiedad al jugador
    p.tieneDueno = true;
    p.disponible = false;
    p.dueno = &j;
    j.propiedades.push_back(p.nombre);

    cout << endl << j.nombre << " compro la propiedad '" << p.nombre << "' por $" << p.precio << endl;
}
