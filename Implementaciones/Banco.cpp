#include "Banco.h"
#include <iostream>

using namespace std;

// Crea un banco con dinero inicial y sin propiedades
Banco crearBanco() {
    Banco b;
    b.dineroTotal = 20000;    // dinero inicial estándar
    return b;
}

// Registra una propiedad en el banco (queda sin dueño)
void registrarPropiedad(Banco &b, const Propiedad &p) {
    b.propiedades[p.nombre] = p;
}

// Incrementa el dinero del banco
void depositarDinero(Banco &b, int monto) {
    if (monto < 0) return;
    b.dineroTotal += monto;
}

// El banco paga dinero (si tiene suficiente en caja)
void retirarBanco(Banco &b, int monto) {
    if (monto < 0) return;

    if (b.dineroTotal < monto) {
        cout << "El banco no tiene suficiente dinero para retirar $" << monto << endl;
        return;
    }

    b.dineroTotal -= monto;
}

// El jugador paga al banco
void cobrarBanco(Banco &b, Jugador &j, int monto) {
    if (monto < 0) return;

    if (j.dinero < monto) {
        cout <<j.nombre << " no tiene suficiente dinero para pagar $" << monto << endl;
        return;
    }

    j.dinero -= monto;
    b.dineroTotal += monto;
}

// El banco paga al jugador
void pagarBanco(Banco &b, Jugador &j, int monto) {
    if (monto < 0) return;

    if (b.dineroTotal < monto) {
        cout << "El banco no tiene suficiente dinero para pagar $" << monto << endl;
        return;
    }

    j.dinero += monto;
    b.dineroTotal -= monto;
}

// El jugador compra una propiedad del banco
void venderPropiedad(Banco &b, Jugador &j, const string &nombreProp) {
    // verificar que exista la propiedad
    auto it = b.propiedades.find(nombreProp);

    if (it == b.propiedades.end()) {
        cout << "La propiedad '" << nombreProp << "' no existe en el banco.\n";
        return;
    }

    Propiedad &p = it->second;

    // verificar si ya tiene dueño
    if (p.tieneDueno) {
        cout << "La propiedad '" << p.nombre << "' ya tiene dueño.\n";
        return;
    }

    // verificar si el jugador tiene dinero suficiente
    if (j.dinero < p.precio) {
        cout << j.nombre << " no tiene suficiente dinero para comprar '" << p.nombre << "'.\n";
        return;
    }

    // el jugador paga
    j.dinero -= p.precio;
    b.dineroTotal += p.precio;

    // asignamos dueño
    asignarDueno(p, &j);

    cout << j.nombre << " compró la propiedad '" << p.nombre << "' por $" << p.precio << endl;
}

bool bancoVenderPropiedad(Banco &b, Jugador &j, const string &nombreProp) {
    if (b.propiedades.count(nombreProp) == 0) {
        cout << "Esa propiedad no está en el banco.\n";
        return false;
    }

    Propiedad &p = b.propiedades[nombreProp];

    if (!comprarPropiedad(p, j)) return false;

    // ya no está en el banco
    b.propiedades.erase(nombreProp);

    return true;
}

bool bancoComprarPropiedad(Banco &b, Jugador &j, const string &nombreProp) {

    bool laTiene = false;
    for (auto &s : j.propiedades) {
        if (s == nombreProp) {
            laTiene = true;
            break;
        }
    }

    if (!laTiene) {
        cout << "El jugador no posee esta propiedad.\n";
        return false;
    }

    // el banco la compra usando venderPropiedad()
    // pero primero debemos tener acceso al objeto Propiedad…
    // en una implementación real tendrías un "tablero" con todas las propiedades centralizadas.
    // Aquí lo haremos recibiendo una referencia externa.
    cout << "bancoComprarPropiedad requiere referencia al objeto Propiedad.\n";
    return false;
}
