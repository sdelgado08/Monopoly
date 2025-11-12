#include "CargarPropiedades.h"
#include "Propiedad.h"
#include <map>
#include <string>

void cargarTodasLasPropiedades(map<string, Propiedad> &m) {
    m.clear();

    auto add = [&](const string &nombre,
                   const string &color,
                   int precio,
                   const int alquiler[6],
                   int precioCasa,
                   bool esFerrocarril = false,
                   bool esServicio = false)
    {
        Propiedad p = crearPropiedad(nombre, color, precio, alquiler, precioCasa, esFerrocarril, esServicio);
        m[p.nombre] = p;
    };

    // === Marrón ===
    int a1[6] = {2,10,30,90,160,250};
    add("Mediterranean Avenue", "Marron", 60, a1, 50);

    int a2[6] = {4,20,60,180,320,450};
    add("Baltic Avenue", "Marron", 60, a2, 50);

    // === Celeste ===
    int a3[6] = {6,30,90,270,400,550};
    add("Oriental Avenue", "Celeste", 100, a3, 50);

    int a4[6] = {6,30,90,270,400,550};
    add("Vermont Avenue", "Celeste", 100, a4, 50);

    int a5[6] = {8,40,100,300,450,600};
    add("Connecticut Avenue", "Celeste", 120, a5, 50);

    // === Rosa ===
    int a6[6] = {10,50,150,450,625,750};
    add("St. Charles Place", "Rosa", 140, a6, 100);

    int a7[6] = {10,50,150,450,625,750};
    add("States Avenue", "Rosa", 140, a7, 100);

    int a8[6] = {12,60,180,500,700,900};
    add("Virginia Avenue", "Rosa", 160, a8, 100);

    // === Naranja ===
    int a9[6] = {14,70,200,550,750,950};
    add("St. James Place", "Naranja", 180, a9, 100);

    int a10[6] = {14,70,200,550,750,950};
    add("Tennessee Avenue", "Naranja", 180, a10, 100);

    int a11[6] = {16,80,220,600,800,1000};
    add("New York Avenue", "Naranja", 200, a11, 100);

    // === Rojo ===
    int a12[6] = {18,90,250,700,875,1050};
    add("Kentucky Avenue", "Rojo", 220, a12, 150);

    int a13[6] = {18,90,250,700,875,1050};
    add("Indiana Avenue", "Rojo", 220, a13, 150);

    int a14[6] = {20,100,300,750,925,1100};
    add("Illinois Avenue", "Rojo", 240, a14, 150);

    // === Amarillo ===
    int a15[6] = {22,110,330,800,975,1150};
    add("Atlantic Avenue", "Amarillo", 260, a15, 150);

    int a16[6] = {22,110,330,800,975,1150};
    add("Ventnor Avenue", "Amarillo", 260, a16, 150);

    int a17[6] = {24,120,360,850,1025,1200};
    add("Marvin Gardens", "Amarillo", 280, a17, 150);

    // === Verde ===
    int a18[6] = {26,130,390,900,1100,1275};
    add("Pacific Avenue", "Verde", 300, a18, 200);

    int a19[6] = {26,130,390,900,1100,1275};
    add("North Carolina Avenue", "Verde", 300, a19, 200);

    int a20[6] = {28,150,450,1000,1200,1400};
    add("Pennsylvania Avenue", "Verde", 320, a20, 200);

    // === Azul Oscuro ===
    int a21[6] = {35,175,500,1100,1300,1500};
    add("Park Place", "Azul Oscuro", 350, a21, 200);

    int a22[6] = {50,200,600,1400,1700,2000};
    add("Boardwalk", "Azul Oscuro", 400, a22, 200);

    // === FERROCARRILES ===
    int rr[6] = {25,25,25,25,25,25};
    add("Reading Railroad", "", 200, rr, 0, true, false);
    add("Pennsylvania Railroad", "", 200, rr, 0, true, false);
    add("B. & O. Railroad", "", 200, rr, 0, true, false);
    add("Short Line", "", 200, rr, 0, true, false);

    // === SERVICIOS ===
    int srv[6] = {0,0,0,0,0,0};
    add("Electric Company", "", 150, srv, 0, false, true);
    add("Water Works", "", 150, srv, 0, false, true);
}
