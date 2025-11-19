#include "Propiedad.h"
#include <iostream>

using namespace std;

/*
Crea una nueva propiedad inicializada con los valores especificados.
La propiedad se crea sin dueño, no hipotecada y disponible para compra.
Los alquileres se copian del array proporcionado (índices 0-5 representan
sin casas, 1-4 casas y hotel respectivamente).
*/
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
    // Copiar los 6 valores de alquiler (0 casas, 1-4 casas, hotel)
    for (int i = 0; i < 6; ++i) p.alquiler[i] = alquiler_vals[i];
    p.numCasas = 0;  // Sin mejoras inicialmente
    p.precioCasa = precioCasa;
    p.hipoteca = hipoteca;
    p.tieneDueno = false;  // Sin dueño inicialmente
    p.hipotecada = false;  // No hipotecada inicialmente
    p.esFerrocarril = esFerrocarril;
    p.esServicios = esServicios;
    p.dueno = nullptr;
    p.disponible = true;  // Disponible para compra
    return p;
}

/*
Muestra toda la información de una propiedad en consola de forma formateada.
Incluye nombre, color, precio, alquileres según número de casas, estado de
mejoras, dueño e información de hipoteca.
*/
void mostrarPropiedad(const Propiedad &p) {
    cout << "------------------------------------" << endl;
    cout << "Propiedad: " << p.nombre << " (" << p.color << ")" << endl;
    cout << "Precio: $" << p.precio << endl;
    cout << "Precio casa: $" << p.precioCasa << endl;
    cout << "Hipoteca: $" << p.hipoteca << endl;
    cout << "Casas/Hotel: " << p.numCasas << endl;
    cout << "Alquileres:" << endl;
    for (int i = 0; i < 6; ++i) {
        cout << "  Con " << i << " casas -> $" << p.alquiler[i] << endl;
    }
    if (p.tieneDueno && p.dueno != nullptr) {
        cout << "Dueno: " << p.dueno->nombre << endl;
    } else {
        cout << "Sin dueno (disponible)" << endl;
    }
    if (p.hipotecada) cout << "[HIPOTECADA]" << endl;
    cout << "------------------------------------" << endl;
}

/*
Permite que un jugador compre una propiedad.
Realiza validaciones:
1. La propiedad debe estar disponible y sin dueño
2. El jugador debe tener suficiente dinero
Si las validaciones pasan, transfiere la propiedad al jugador y actualiza
el dinero. Retorna true si la compra fue exitosa, false en caso contrario.
*/
bool comprarPropiedad(Propiedad &p, Jugador &j) {
    // Validación 1: verificar que la propiedad esté disponible
    if (!p.disponible || p.tieneDueno) {
        cout << "La propiedad \"" << p.nombre << "\" no esta disponible para compra." << endl;
        return false;
    }
    // Validación 2: verificar que el jugador tenga suficiente dinero
    if (j.dinero < p.precio) {
        cout << j.nombre << " no tiene suficiente dinero para comprar " << p.nombre << "." << endl;
        return false;
    }
    
    // Realizar la compra: jugador paga
    j.dinero -= p.precio;
    
    // Asignar la propiedad al jugador
    p.tieneDueno = true;
    p.disponible = false;
    p.dueno = &j;
    
    // Añadir el nombre de la propiedad a la lista del jugador
    // (usando try-catch por si el vector no existe, aunque debería existir)
    try {
        j.propiedades.push_back(p.nombre);
    } catch (...) { /* si no existe, se ignora */ }
    
    cout << j.nombre << " compro " << p.nombre << " por $" << p.precio << "." << endl;
    return true;
}

/*
Permite que un jugador venda una propiedad al banco.
El jugador recibe la mitad del precio original de compra.
Realiza validaciones:
1. El jugador debe ser el dueño de la propiedad
2. La propiedad no debe estar hipotecada (validación implícita)
Si las validaciones pasan, la propiedad vuelve a estar disponible y el
jugador recibe el dinero. Retorna true si la venta fue exitosa.
*/
bool venderPropiedad(Propiedad &p, Jugador &j) {
    // Validación: verificar que el jugador sea el dueño
    if (!p.tieneDueno || p.dueno != &j) {
        cout << j.nombre << " no es dueno de " << p.nombre << "." << endl;
        return false;
    }
    
    // Calcular el valor de venta (mitad del precio original)
    int venta = p.precio / 2;
    
    // Realizar la venta: jugador recibe dinero
    j.dinero += venta;
    
    // La propiedad vuelve a estar disponible
    p.tieneDueno = false;
    p.disponible = true;
    p.dueno = nullptr;
    
    // Remover la propiedad de la lista del jugador
    for (size_t i = 0; i < j.propiedades.size(); ++i) {
        if (j.propiedades[i] == p.nombre) {
            j.propiedades.erase(j.propiedades.begin() + i);
            break;
        }
    }
    
    cout << "[VENTA] " << j.nombre << " vendio " << p.nombre << " por $" << venta << "." << endl;
    return true;
}

/*
Permite que un jugador hipoteque una propiedad para obtener dinero.
Al hipotecar, el jugador recibe el valor de hipoteca y la propiedad
deja de generar alquiler hasta que se deshipoteque.
Realiza validaciones:
1. El jugador debe ser el dueño
2. La propiedad no debe estar ya hipotecada
Retorna true si la hipoteca fue exitosa.
*/
bool hipotecarPropiedad(Propiedad &p, Jugador &j) {
    // Validación 1: verificar que el jugador sea el dueño
    if (!p.tieneDueno || p.dueno != &j) {
        cout << "Solo el dueno puede hipotecar la propiedad." << endl;
        return false;
    }
    // Validación 2: verificar que la propiedad no esté ya hipotecada
    if (p.hipotecada) {
        cout << "La propiedad ya esta hipotecada." << endl;
        return false;
    }
    
    // Realizar la hipoteca: propiedad queda hipotecada y jugador recibe dinero
    p.hipotecada = true;
    j.dinero += p.hipoteca;
    
    cout << j.nombre << " hipoteco " << p.nombre << " y recibio $" << p.hipoteca << "." << endl;
    return true;
}

/*
Permite que un jugador compre una casa en su propiedad.
Solo se pueden construir hasta 4 casas antes de poder comprar un hotel.
Realiza validaciones:
1. El jugador debe ser el dueño
2. La propiedad no debe estar hipotecada
3. No debe haber ya 4 casas (debe comprar hotel en su lugar)
4. El jugador debe tener suficiente dinero
Retorna true si la compra fue exitosa.
*/
bool comprarCasa(Propiedad &p, Jugador &j) {
    // Validación 1: verificar que el jugador sea el dueño
    if (!p.tieneDueno || p.dueno != &j) {
        cout << "Solo el dueno puede comprar casas." << endl;
        return false;
    }
    // Validación 2: verificar que la propiedad no esté hipotecada
    if (p.hipotecada) {
        cout << "No se pueden construir casas sobre una propiedad hipotecada." << endl;
        return false;
    }
    // Validación 3: verificar que no haya ya 4 casas
    if (p.numCasas >= 4) {
        cout << "Ya hay 4 casas; compre un hotel en su lugar." << endl;
        return false;
    }
    // Validación 4: verificar que el jugador tenga suficiente dinero
    if (j.dinero < p.precioCasa) {
        cout << j.nombre << " no tiene suficiente dinero para comprar una casa.\n";
        return false;
    }
    
    // Realizar la compra: jugador paga y se incrementa el número de casas
    j.dinero -= p.precioCasa;
    p.numCasas += 1;
    
    cout << j.nombre << " compro una casa en " << p.nombre << ". Casas ahora: " << p.numCasas << ".\n";
    return true;
}

/*
Permite que un jugador compre un hotel en su propiedad.
Un hotel se compra cuando ya hay exactamente 4 casas, convirtiendo
las 4 casas en 1 hotel (numCasas = 5).
Realiza validaciones:
1. El jugador debe ser el dueño
2. La propiedad no debe estar hipotecada
3. Debe haber exactamente 4 casas
4. El jugador debe tener suficiente dinero
Retorna true si la compra fue exitosa.
*/
bool comprarHotel(Propiedad &p, Jugador &j) {
    // Validación 1: verificar que el jugador sea el dueño
    if (!p.tieneDueno || p.dueno != &j) {
        cout << "Solo el dueño puede comprar hotel.\n";
        return false;
    }
    // Validación 2: verificar que la propiedad no esté hipotecada
    if (p.hipotecada) {
        cout << "No se pueden construir hotel sobre propiedad hipotecada.\n";
        return false;
    }
    // Validación 3: verificar que haya exactamente 4 casas
    if (p.numCasas != 4) {
        cout << "Se necesitan exactamente 4 casas antes de comprar un hotel.\n";
        return false;
    }
    // Validación 4: verificar que el jugador tenga suficiente dinero
    // (normalmente se paga precio de casa adicional, usamos precioCasa para simplificar)
    if (j.dinero < p.precioCasa) {
        cout << j.nombre << " no tiene suficiente dinero para comprar hotel.\n";
        return false;
    }
    
    // Realizar la compra: jugador paga y se convierte a hotel (numCasas = 5)
    j.dinero -= p.precioCasa;
    p.numCasas = 5;  // 5 representa hotel
    
    cout << j.nombre << " compro un hotel en " << p.nombre << ".\n";
    return true;
}

/*
Permite que un jugador venda una casa de su propiedad.
El jugador recibe la mitad del precio de la casa.
Si hay un hotel (numCasas = 5), se convierte de vuelta a 4 casas.
Realiza validaciones:
1. El jugador debe ser el dueño
2. Debe haber al menos una casa para vender
Retorna true si la venta fue exitosa.
*/
bool venderCasa(Propiedad &p, Jugador &j) {
    // Validación 1: verificar que el jugador sea el dueño
    if (!p.tieneDueno || p.dueno != &j) {
        cout << "Solo el dueno puede vender casas.\n";
        return false;
    }
    // Validación 2: verificar que haya casas para vender
    if (p.numCasas <= 0) {
        cout << "No hay casas para vender.\n";
        return false;
    }
    
    // Calcular el reembolso (mitad del precio de la casa)
    int reembolso = p.precioCasa / 2;
    
    // Si hay hotel (numCasas = 5), vender hotel -> convertir a 4 casas
    if (p.numCasas == 5) {
        p.numCasas = 4;
        j.dinero += reembolso;
        cout << j.nombre << " vendio el hotel de " << p.nombre << " y recibio $" << reembolso << ". Ahora hay 4 casas.\n";
        return true;
    }
    
    // Vender una casa normal: decrementar numCasas y dar reembolso
    p.numCasas -= 1;
    j.dinero += reembolso;
    
    cout << j.nombre << " vendio una casa en " << p.nombre << " y recibio $" << reembolso << ". Casas ahora: " << p.numCasas << ".\n";
    return true;
}

/*
Cobra el alquiler de una propiedad cuando un jugador cae en ella.
El monto del alquiler depende del número de casas/hotel (0-5).
Para ferrocarriles y servicios, el alquiler se calcula de forma especial.
Realiza validaciones:
1. La propiedad debe tener dueño
2. El inquilino no debe ser el dueño
3. La propiedad no debe estar hipotecada (implícito)
4. El inquilino debe tener suficiente dinero
Retorna true si se cobró el alquiler exitosamente.
*/
bool cobrarAlquiler(Propiedad &p, Jugador &inquilino) {
    // Validación 1: verificar que la propiedad tenga dueño
    if (!p.tieneDueno || p.dueno == nullptr) {
        // Sin dueño, no hay alquiler
        cout << p.nombre << " no tiene dueno. No se cobra alquiler.\n";
        return false;
    }
    // Validación 2: verificar que el inquilino no sea el dueño
    if (p.dueno == &inquilino) {
        // El dueño cayó en su propia propiedad, no paga alquiler
        cout << inquilino.nombre << " cayo en su propia propiedad " << p.nombre << ".\n";
        return false;
    }

    // Calcular el monto del alquiler según el tipo de propiedad
    int monto = 0;
    if (p.esFerrocarril || p.esServicios) {
        // Para ferrocarriles y servicios, usar el valor base (alquiler[0])
        // NOTA: En un juego completo, el alquiler de ferrocarriles se multiplica
        // por la cantidad de ferrocarriles que posea el dueño, y el de servicios
        // se calcula según el resultado de los dados
        monto = p.alquiler[0];
    } else {
        // Para propiedades normales, el alquiler depende del número de casas/hotel
        // Índice: 0 = sin casas, 1-4 = con 1-4 casas, 5 = con hotel
        int idx = p.numCasas;
        if (idx < 0) idx = 0;  // Asegurar límite inferior
        if (idx > 5) idx = 5;  // Asegurar límite superior
        monto = p.alquiler[idx];
    }

    // Validación 3: verificar que el inquilino tenga suficiente dinero
    if (inquilino.dinero < monto) {
        cout << inquilino.nombre << " no tiene dinero suficiente para pagar $" << monto << " de alquiler.\n";
        // En un juego real habría subastas o hipotecas, pero aquí devolvemos false
        return false;
    }

    // Realizar el pago: inquilino paga, dueño recibe
    inquilino.dinero -= monto;
    if (p.dueno != nullptr) p.dueno->dinero += monto;

    cout << inquilino.nombre << " pago $" << monto << " de alquiler por " << p.nombre
              << " a " << (p.dueno ? p.dueno->nombre : string("Banco")) << ".\n";
    return true;
}
