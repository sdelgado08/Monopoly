#include "PilaEstados.h"
#include <iostream>

using namespace std;

/*
Crea una pila de estados vacía, lista para almacenar estados del juego.
La pila se inicializa sin elementos.
*/
PilaEstados crearPila() {
    PilaEstados p;
    return p;
}

/*
Guarda un estado en la parte superior de la pila (LIFO).
El estado más reciente queda en el tope y será el primero en ser recuperado
al deshacer.
*/
void guardarEstado(PilaEstados &p, const Estado &e) {
    p.pila.push(e);
}

/*
Recupera y elimina el estado más reciente de la pila (LIFO).
Este estado puede ser usado para restaurar el juego a un estado anterior.
Si la pila está vacía, retorna un estado por defecto y muestra un mensaje.
*/
Estado deshacerEstado(PilaEstados &p) {
    // Validación: verificar que la pila no esté vacía
    if (p.pila.empty()) {
        cout << "No hay estados para deshacer." << endl;
        return {"", 0, 0, 0};  // Estado vacío por defecto
    }

    // Obtener el estado del tope (más reciente) y eliminarlo
    Estado e = p.pila.top();
    p.pila.pop();
    return e;
}

/*
Muestra la cantidad de estados almacenados en la pila.
Útil para depuración y verificación del tamaño de la pila.
*/
void mostrarTamano(const PilaEstados &p) {
    cout << "Estados guardados: " << p.pila.size() << endl;
}
