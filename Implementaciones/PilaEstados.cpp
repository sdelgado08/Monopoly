#include "PilaEstados.h"
#include <iostream>

using namespace std;

PilaEstados crearPila() {
    PilaEstados p;
    return p;
}

void guardarEstado(PilaEstados &p, const Estado &e) {
    p.pila.push(e);
}

Estado deshacerEstado(PilaEstados &p) {
    if (p.pila.empty()) {
        cout << "No hay estados para deshacer.\n";
        return {"", 0, 0, 0}; // estado vacío
    }

    Estado e = p.pila.top();
    p.pila.pop();
    return e;
}

void mostrarTamano(const PilaEstados &p) {
    cout << "Estados guardados: " << p.pila.size() << endl;
}
