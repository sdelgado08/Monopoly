#include "Tablero.h"
#include <iostream>

using namespace std;

/*
Crea el tablero completo del Monopoly con las 40 casillas estándar.
Crea todas las casillas individuales, las enlaza en una lista circular
doblemente enlazada (cada casilla apunta a la siguiente y a la anterior),
y establece la casilla "Go" como punto de inicio.
*/
void crearTablero (Tablero &t){
    // Creación de todas las 40 casillas del tablero estándar del Monopoly
    Casilla* c1 = crearCasilla("Go", "Inicio", 0);
    Casilla* c2 = crearCasilla("Mediterranean Avenue", "Propiedad", 60);
    Casilla* c3 = crearCasilla("Community Chest", "Arca Comunal", 0);
    Casilla* c4 = crearCasilla("Baltic Avenue", "Propiedad", 60);
    Casilla* c5 = crearCasilla("Income Tax", "Impuesto", 200);
    Casilla* c6 = crearCasilla("Reading Railroad", "Estacion", 200);
    Casilla* c7 = crearCasilla("Oriental Avenue", "Propiedad", 100);
    Casilla* c8 = crearCasilla("Chance", "Casualidad", 0);
    Casilla* c9 = crearCasilla("Vermont Avenue", "Propiedad", 100);
    Casilla* c10 = crearCasilla("Connecticut Avenue", "Propiedad", 120);
    Casilla* c11 = crearCasilla("Jail / Just visiting", "Carcel", 0);
    Casilla* c12 = crearCasilla("St. Charles Place", "Propiedad", 140);
    Casilla* c13 = crearCasilla("Electric Company", "Servicio", 150);
    Casilla* c14 = crearCasilla("States Avenue", "Propiedad", 140);
    Casilla* c15 = crearCasilla("Virginia Avenue", "Propiedad", 160);
    Casilla* c16 = crearCasilla("Pennsylvania Railroad", "Estacion", 200);
    Casilla* c17 = crearCasilla("St. James Place", "Propiedad", 180);
    Casilla* c18 = crearCasilla("Community Chest", "ArcaComunal", 0);
    Casilla* c19 = crearCasilla("Tennessee Avenue", "Propiedad", 180);
    Casilla* c20 = crearCasilla("New York Avenue", "Propiedad", 200);
    Casilla* c21 = crearCasilla("Free Parking", "Parqueadero", 0);
    Casilla* c22 = crearCasilla("Kentucky Avenue", "Propiedad", 220);
    Casilla* c23 = crearCasilla("Chance", "Casualidad", 0);
    Casilla* c24 = crearCasilla("Indiana Avenue", "Propiedad", 220);
    Casilla* c25 = crearCasilla("Illinois Avenue", "Propiedad", 240);
    Casilla* c26 = crearCasilla("B&O Railroad", "Estacion", 200);
    Casilla* c27 = crearCasilla("Atlantic Avenue", "Propiedad", 260);
    Casilla* c28 = crearCasilla("Ventnor Avenue", "Propiedad", 260);
    Casilla* c29 = crearCasilla("Water Works", "Servicio", 150);
    Casilla* c30 = crearCasilla("Marvin Gardens", "Propiedad", 280);
    Casilla* c31 = crearCasilla("Go to Jail", "VayaCarcel", 0);
    Casilla* c32 = crearCasilla("Pacific Avenue", "Propiedad", 300);
    Casilla* c33 = crearCasilla("North Carolina Avenue", "Propiedad", 300);
    Casilla* c34 = crearCasilla("Community Chest", "ArcaComunal", 0);
    Casilla* c35 = crearCasilla("Pennsylvania Avenue", "Propiedad", 320);
    Casilla* c36 = crearCasilla("Short Line Railroad", "Estacion", 200);
    Casilla* c37 = crearCasilla("Chance", "Casualidad", 0);
    Casilla* c38 = crearCasilla("Park Place", "Propiedad", 350);
    Casilla* c39 = crearCasilla("Luxury Tax", "Impuesto", 100);
    Casilla* c40 = crearCasilla("Boardwalk", "Propiedad", 400);

    // Enlazado de casillas en orden circular (sentido horario)
    // Cada casilla se enlaza con la siguiente, creando la lista circular
    enlazarCasillas(c1, c2);   enlazarCasillas(c2, c3);
    enlazarCasillas(c3, c4);   enlazarCasillas(c4, c5);
    enlazarCasillas(c5, c6);   enlazarCasillas(c6, c7);
    enlazarCasillas(c7, c8);   enlazarCasillas(c8, c9);
    enlazarCasillas(c9, c10);  enlazarCasillas(c10, c11);
    enlazarCasillas(c11, c12); enlazarCasillas(c12, c13);
    enlazarCasillas(c13, c14); enlazarCasillas(c14, c15);
    enlazarCasillas(c15, c16); enlazarCasillas(c16, c17);
    enlazarCasillas(c17, c18); enlazarCasillas(c18, c19);
    enlazarCasillas(c19, c20); enlazarCasillas(c20, c21);
    enlazarCasillas(c21, c22); enlazarCasillas(c22, c23);
    enlazarCasillas(c23, c24); enlazarCasillas(c24, c25);
    enlazarCasillas(c25, c26); enlazarCasillas(c26, c27);
    enlazarCasillas(c27, c28); enlazarCasillas(c28, c29);
    enlazarCasillas(c29, c30); enlazarCasillas(c30, c31);
    enlazarCasillas(c31, c32); enlazarCasillas(c32, c33);
    enlazarCasillas(c33, c34); enlazarCasillas(c34, c35);
    enlazarCasillas(c35, c36); enlazarCasillas(c36, c37);
    enlazarCasillas(c37, c38); enlazarCasillas(c38, c39);
    enlazarCasillas(c39, c40); enlazarCasillas(c40, c1);

    // Cerrar el doble enlace circular: la última casilla (c40) debe apuntar
    // a la primera (c1) en sentido antihorario para completar el círculo
    c1->anterior = c40;

    // Asignar el tablero: establecer la casilla de inicio (Go) y el total de casillas
    t.inicio = c1;  // La casilla "Go" es el punto de inicio
    t.totalCasillas = 40;  // Total de casillas en el tablero estándar   
}

/*
Muestra todas las casillas del tablero en consola, realizando un recorrido
circular completo desde la casilla de inicio.
Si el tablero está vacío, muestra un mensaje indicándolo.
Cada casilla se muestra con su número de posición y su información.
*/
void mostrarTablero(const Tablero &t){
    // Validación: verificar que el tablero no esté vacío
    if(t.inicio == nullptr){
        cout << "El tablero está vacío." << endl;
        return;
    }

    cout << endl << "====TABLERO====" << endl << endl;
    Casilla* actual = t.inicio;
    int contador = 1;

    // Recorrer el tablero circularmente usando do-while para asegurar
    // que se muestre al menos la casilla de inicio
    do{
        cout << contador << ". ";
        mostrarCasilla(actual);
        actual = actual->siguiente;  // Avanzar a la siguiente casilla
        contador++;
    }while(actual != t.inicio);  // Continuar hasta volver al inicio
}

/*
Avanza en el tablero desde la casilla actual el número de pasos especificado
en sentido horario (siguiendo los punteros 'siguiente').
Si la casilla actual es nula, retorna null.
La función navega por la lista circular, dando la vuelta completa si es necesario.
*/
Casilla* moverEnTablero(Casilla* actual, int pasos){
    // Validación: verificar que la casilla actual no sea nula
    if(actual == nullptr){
        return nullptr;
    }

    // Avanzar 'pasos' posiciones siguiendo los punteros 'siguiente'
    // (sentido horario en el tablero)
    for(int i=0; i<pasos; i++){
        actual = actual->siguiente;
    }
    return actual;
}

/*
Retrocede en el tablero desde la casilla actual el número de pasos especificado
en sentido antihorario (siguiendo los punteros 'anterior').
Si la casilla actual es nula, retorna null.
La función navega por la lista circular, dando la vuelta completa si es necesario.
*/
Casilla* retrocederEnTablero(Casilla* actual, int pasos){
    // Validación: verificar que la casilla actual no sea nula
    if(actual == nullptr){
        return nullptr;
    }

    // Retroceder 'pasos' posiciones siguiendo los punteros 'anterior'
    // (sentido antihorario en el tablero)
    for(int i=0; i<pasos; i++){
        actual = actual->anterior;
    }
    return actual;
}

/*
Obtiene el índice de una casilla en el tablero, contando desde la casilla
de inicio (Go = índice 0). Recorre el tablero circularmente hasta encontrar
la casilla especificada.
*/
int obtenerIndiceCasilla(const Tablero &t, Casilla* casilla){
    // Validación: verificar que el tablero y la casilla sean válidos
    if(t.inicio == nullptr || casilla == nullptr){
        return -1;
    }

    // Recorrer el tablero desde el inicio contando posiciones
    Casilla* actual = t.inicio;
    int indice = 0;

    do{
        if(actual == casilla){
            return indice;  // Casilla encontrada, retornar su índice
        }
        actual = actual->siguiente;
        indice++;
    }while(actual != t.inicio && indice < t.totalCasillas);

    return -1;  // Casilla no encontrada
}

/*
Obtiene un puntero a la casilla que se encuentra en el índice especificado
del tablero, contando desde la casilla de inicio (0 = Go).
*/
Casilla* obtenerCasillaPorIndice(const Tablero &t, int indice){
    // Validación: verificar que el tablero sea válido y el índice esté en rango
    if(t.inicio == nullptr || indice < 0 || indice >= t.totalCasillas){
        return nullptr;
    }

    // Recorrer el tablero desde el inicio hasta llegar al índice deseado
    Casilla* actual = t.inicio;
    for(int i = 0; i < indice; i++){
        actual = actual->siguiente;
    }

    return actual;
}