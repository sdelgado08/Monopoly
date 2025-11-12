#include "Propiedad.h"
#include <iostream>

// crearPropiedad
Propiedad crearPropiedad(const string &nombre,
                         const string &color,
                         int precio,
                         const int alquiler_vals[6],
                         int precioCasa,
                         int hipoteca,
                         bool esFerrocarril,
                         bool esServicios) {
    Propiedad p;
    p.nombre = nombre;
    p.color = color;
    p.precio = precio;
    for (int i = 0; i < 6; ++i) p.alquiler[i] = alquiler_vals[i];
    p.numCasas = 0;
    p.precioCasa = precioCasa;
    p.hipoteca = hipoteca;
    p.tieneDueno = false;
    p.hipotecada = false;
    p.esFerrocarril = esFerrocarril;
    p.esServicios = esServicios;
    p.dueno = nullptr;
    p.disponible = true;
    return p;
}

// mostrarPropiedad
void mostrarPropiedad(const Propiedad &p) {
    cout << "------------------------------------\n";
    cout << "Propiedad: " << p.nombre << " (" << p.color << ")\n";
    cout << "Precio: $" << p.precio << "\n";
    cout << "Precio casa: $" << p.precioCasa << "\n";
    cout << "Hipoteca: $" << p.hipoteca << "\n";
    cout << "Casas/Hotel: " << p.numCasas << "\n";
    cout << "Alquileres:\n";
    for (int i = 0; i < 6; ++i) {
        cout << "  Con " << i << " casas -> $" << p.alquiler[i] << "\n";
    }
    if (p.tieneDueno && p.dueno != nullptr) {
        cout << "Dueño: " << p.dueno->nombre << "\n";
    } else {
        cout << "Sin dueno (disponible)\n";
    }
    if (p.hipotecada) cout << "[HIPOTECADA]\n";
    cout << "------------------------------------\n";
}

// comprarPropiedad
bool comprarPropiedad(Propiedad &p, Jugador &j) {
    if (!p.disponible || p.tieneDueno) {
        cout << "La propiedad \"" << p.nombre << "\" no esta disponible para compra.\n";
        return false;
    }
    if (j.dinero < p.precio) {
        cout << j.nombre << " no tiene suficiente dinero para comprar " << p.nombre << ".\n";
        return false;
    }
    j.dinero -= p.precio;
    p.tieneDueno = true;
    p.disponible = false;
    p.dueno = &j;
    // añadir nombre de propiedad al vector del jugador (si existe)
    try {
        j.propiedades.push_back(p.nombre);
    } catch (...) { /* si no existe, se ignora */ }
    cout << j.nombre << " compro " << p.nombre << " por $" << p.precio << ".\n";
    return true;
}

// venderPropiedad (jugador vende al banco por la mitad del precio)
bool venderPropiedad(Propiedad &p, Jugador &j) {
    if (!p.tieneDueno || p.dueno != &j) {
        cout  << j.nombre << " no es dueno de " << p.nombre << ".\n";
        return false;
    }
    int venta = p.precio / 2;
    j.dinero += venta;
    p.tieneDueno = false;
    p.disponible = true;
    p.dueno = nullptr;
    // remover del vector de propiedades del jugador (si existe)
    for (size_t i = 0; i < j.propiedades.size(); ++i) {
        if (j.propiedades[i] == p.nombre) {
            j.propiedades.erase(j.propiedades.begin() + i);
            break;
        }
    }
    cout << "💱 " << j.nombre << " vendió " << p.nombre << " por $" << venta << ".\n";
    return true;
}

// hipotecarPropiedad
bool hipotecarPropiedad(Propiedad &p, Jugador &j) {
    if (!p.tieneDueno || p.dueno != &j) {
        cout << "Solo el dueño puede hipotecar la propiedad.\n";
        return false;
    }
    if (p.hipotecada) {
        cout << "La propiedad ya está hipotecada.\n";
        return false;
    }
    p.hipotecada = true;
    j.dinero += p.hipoteca;
    cout << j.nombre << " hipoteco " << p.nombre << " y recibio $" << p.hipoteca << ".\n";
    return true;
}

// comprarCasa
bool comprarCasa(Propiedad &p, Jugador &j) {
    if (!p.tieneDueno || p.dueno != &j) {
        cout << "Solo el dueño puede comprar casas.\n";
        return false;
    }
    if (p.hipotecada) {
        cout << "No se pueden construir casas sobre una propiedad hipotecada.\n";
        return false;
    }
    if (p.numCasas >= 4) {
        cout << "Ya hay 4 casas; compre un hotel en su lugar.\n";
        return false;
    }
    if (j.dinero < p.precioCasa) {
        cout << j.nombre << " no tiene suficiente dinero para comprar una casa.\n";
        return false;
    }
    j.dinero -= p.precioCasa;
    p.numCasas += 1;
    cout << j.nombre << " compro una casa en " << p.nombre << ". Casas ahora: " << p.numCasas << ".\n";
    return true;
}

// comprarHotel (convierte 4 casas en 1 hotel -> numCasas = 5)
bool comprarHotel(Propiedad &p, Jugador &j) {
    if (!p.tieneDueno || p.dueno != &j) {
        cout << "Solo el dueño puede comprar hotel.\n";
        return false;
    }
    if (p.hipotecada) {
        cout << "No se pueden construir hotel sobre propiedad hipotecada.\n";
        return false;
    }
    if (p.numCasas != 4) {
        cout << "Se necesitan exactamente 4 casas antes de comprar un hotel.\n";
        return false;
    }
    if (j.dinero < p.precioCasa) { // normalmente se paga precio de casa adicional; usamos precioCasa para simplificar
        cout << j.nombre << " no tiene suficiente dinero para comprar hotel.\n";
        return false;
    }
    j.dinero -= p.precioCasa;
    p.numCasas = 5; // 5 representa hotel
    cout << j.nombre << " compro un hotel en " << p.nombre << ".\n";
    return true;
}

// venderCasa
bool venderCasa(Propiedad &p, Jugador &j) {
    if (!p.tieneDueno || p.dueno != &j) {
        cout << "Solo el dueno puede vender casas.\n";
        return false;
    }
    if (p.numCasas <= 0) {
        cout << "No hay casas para vender.\n";
        return false;
    }
    int reembolso = p.precioCasa / 2;
    // si hay hotel (5), vender hotel -> convertir a 4 casas y devolver reembolso
    if (p.numCasas == 5) {
        p.numCasas = 4;
        j.dinero += reembolso;
        cout << j.nombre << " vendio el hotel de " << p.nombre << " y recibio $" << reembolso << ". Ahora hay 4 casas.\n";
        return true;
    }
    // vender una casa normal
    p.numCasas -= 1;
    j.dinero += reembolso;
    cout << j.nombre << " vendio una casa en " << p.nombre << " y recibio $" << reembolso << ". Casas ahora: " << p.numCasas << ".\n";
    return true;
}

// cobrarAlquiler
bool cobrarAlquiler(Propiedad &p, Jugador &inquilino) {
    if (!p.tieneDueno || p.dueno == nullptr) {
        // sin dueño, no hay alquiler
        cout << p.nombre << " no tiene dueno. No se cobra alquiler.\n";
        return false;
    }
    if (p.dueno == &inquilino) {
        // el dueño cayó en su propia propiedad
        cout << inquilino.nombre << " cayo en su propia propiedad " << p.nombre << ".\n";
        return false;
    }

    int monto = 0;
    if (p.esFerrocarril || p.esServicios) {
        // si definiste alquiler[0] para estos casos, úsalo
        monto = p.alquiler[0];
    } else {
        // alquiler según número de casas (0..5)
        int idx = p.numCasas;
        if (idx < 0) idx = 0;
        if (idx > 5) idx = 5;
        monto = p.alquiler[idx];
    }

    if (inquilino.dinero < monto) {
        cout << inquilino.nombre << " no tiene dinero suficiente para pagar $" << monto << " de alquiler.\n";
        // en un juego real habría subastas o hipotecas, pero aquí devolvemos false
        return false;
    }

    inquilino.dinero -= monto;
    if (p.dueno != nullptr) p.dueno->dinero += monto;

    cout << inquilino.nombre << " pago $" << monto << " de alquiler por " << p.nombre
              << " a " << (p.dueno ? p.dueno->nombre : string("Banco")) << ".\n";
    return true;
}
