#include "ColaCartas.h"
#include <iostream>

using namespace std;

/*
Crea una cola de cartas vacía, lista para ser poblada con cartas.
La cola se inicializa sin elementos.
*/
ColaCartas crearColaCartas() {
    ColaCartas c;
    return c;
}

/*
Añade una carta al final de la cola (FIFO).
La carta se inserta después de todas las cartas existentes.
*/
void encolarCarta(ColaCartas &c, const Carta &card) {
    c.cartas.push(card);
}

/*
Saca la carta del frente de la cola y la vuelve a insertar al final.
Cuando se saca una carta, esta se vuelve a colocar al final para
que pueda ser sacada nuevamente en el futuro.
Si la cola está vacía, retorna una carta por defecto.
*/
Carta sacarCarta(ColaCartas &c) {
    // Validación: verificar que la cola no esté vacía
    if (c.cartas.empty()) {
        return {"<sin cartas>", 0};  // Carta por defecto si no hay cartas
    }

    // Obtener la primera carta
    Carta primera = c.cartas.front();
    c.cartas.pop();  // Removerla del frente
    
    // Reinsertarla al final (comportamiento circular del Monopoly)
    c.cartas.push(primera);

    return primera;
}

/*
Muestra todas las cartas de la cola en consola.
Como queue no permite recorrer directamente sin modificar la cola,
se crea una copia para poder mostrar todas las cartas sin afectar
el orden original.
*/
void mostrarCartas(const ColaCartas &c) {
    cout << "Cartas en la cola: \n";

    // Crear una copia de la cola para poder recorrerla sin modificar la original
    // (queue no permite iteración directa sin modificar la estructura)
    queue<Carta> copia = c.cartas;

    // Recorrer la copia mostrando cada carta
    while (!copia.empty()) {
        Carta card = copia.front();
        copia.pop();

        cout << "  - " << card.mensaje 
             << "  (efecto " << card.efecto << ")\n";
    }
}
