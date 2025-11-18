#include "Casilla.h"
#include "Propiedad.h"
#include <iostream>
#include <map>

using namespace std;

/*
Crea una nueva casilla en memoria dinámica con los valores especificados.
Inicializa los punteros siguiente y anterior en nullptr.
IMPORTANTE: La memoria debe ser liberada con eliminarCasilla() cuando
ya no se necesite la casilla.
*/
Casilla* crearCasilla (const string &nombre, const string &tipo, int precio){
    Casilla* nuevaCasilla = new Casilla;
    nuevaCasilla->nombre = nombre;
    nuevaCasilla->tipo = tipo;
    nuevaCasilla->precio = precio;
    nuevaCasilla->siguiente = nullptr;  // Se enlazará después
    nuevaCasilla->anterior = nullptr;    // Se enlazará después
    return nuevaCasilla;
}

/*
Muestra la información de una casilla en consola.
Si la casilla es nula, muestra un mensaje indicándolo.
Solo muestra el precio si es mayor que 0 (casillas con precio).
*/
void mostrarCasilla (const Casilla* c){
    // Validación: verificar que la casilla no sea nula
    if (c == nullptr){
        cout << "(Casilla nula)" << endl;
        return;
    }

    // Mostrar nombre y tipo
    cout << c->nombre << " [" << c->tipo << "]";
    
    // Mostrar precio solo si aplica (mayor que 0)
    if (c->precio > 0){
        cout << " - Precio: $" << c->precio;
    }
    cout << endl;
}

/*
Muestra la información de una casilla en consola, incluyendo el color
si es una propiedad. Si la casilla es nula, muestra un mensaje indicándolo.
Busca la propiedad en el mapa para obtener su color y mostrarlo.
*/
void mostrarCasilla (const Casilla* c, const map<string, Propiedad> &propiedades){
    // Validación: verificar que la casilla no sea nula
    if (c == nullptr){
        cout << "(Casilla nula)" << endl;
        return;
    }

    // Mostrar nombre y tipo
    cout << c->nombre << " [" << c->tipo << "]";
    
    // Si es una propiedad, ferrocarril, servicio o estación, buscar en el mapa para obtener el color
    if (c->tipo == "Propiedad" || c->tipo == "Ferrocarril" || c->tipo == "Servicio" || c->tipo == "Estacion") {
        auto it = propiedades.find(c->nombre);
        if (it != propiedades.end()) {
            const Propiedad &prop = it->second;
            // Mostrar el color si la propiedad tiene uno (no está vacío)
            if (!prop.color.empty()) {
                cout << " - Color: " << prop.color;
            }
        }
    }
    
    // Mostrar precio solo si aplica (mayor que 0)
    if (c->precio > 0){
        cout << " - Precio: $" << c->precio;
    }
    cout << endl;
}

/*
Enlaza dos casillas en ambas direcciones, creando un doble enlace.
Establece a->siguiente = b y b->anterior = a.
Si alguna de las casillas es nula, no realiza ninguna operación.
*/
void enlazarCasillas (Casilla* a, Casilla* b){
    // Validación: ambas casillas deben ser válidas
    if(a == nullptr || b == nullptr){
        return;
    }

    // Crear doble enlace: a apunta a b (adelante) y b apunta a a (atrás)
    a->siguiente = b;
    b->anterior = a;
}

/*
Libera la memoria dinámica asociada a una casilla.
IMPORTANTE: Solo debe llamarse cuando la casilla ya no se necesita y
no está siendo referenciada por otras casillas en la lista circular.
*/
void eliminarCasilla (Casilla* c){
    if(c != nullptr){
        delete c;
    }
}