#include "Tablero.h"
#include <iostream>

void crearTablero (Tablero &t){
    //Creación de todas las casillas
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

    //Enlazado de casillas hacia adelante
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

    //Cerrar el doble enlace circular
    c1->anterior = c40;

    //Asignar tablero
    t.inicio = c1;
    t.totalCasillas = 40;   
}

void mostrarTablero(const Tablero &t){
    if(t.inicio == nullptr){
        cout << "El tablero está vacío." << endl;
        return;
    }

    cout << "====TABLERO DEL MONOPOLY====" << endl;
    Casilla* actual = t.inicio;
    int contador = 1;

    do{
        cout << contador << ". ";
        mostrarCasilla(actual);
        actual = actual->siguiente;
        contador++;
    }while(actual != t.inicio);

    cout << "Total de casillas: " << t.totalCasillas << endl;
}

Casilla* moverEnTablero(Casilla* actual, int pasos){
    if(actual == nullptr){
        return nullptr;
    }

    for(int i=0; i<pasos; i++){
        actual = actual->siguiente;
    }
    return actual;
}

Casilla* retrocederEnTablero(Casilla* actual, int pasos){
    if(actual == nullptr){
        return nullptr;
    }

    for(int i=0; i<pasos; i++){
        actual = actual->anterior;
    }
    return actual;
}