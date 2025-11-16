#include "JuegoMonopoly.h"
#include "Estados.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

// Generador de números aleatorios para los dados
// Se inicializa con el tiempo actual como semilla para obtener resultados diferentes
mt19937 generador(time(0));
uniform_int_distribution<int> dado(1, 6);  // Distribución uniforme entre 1 y 6

/*
Simula el lanzamiento de dos dados de 6 caras.
Genera dos números aleatorios entre 1 y 6, los muestra en consola
y retorna la suma de ambos (el total de pasos a avanzar).
*/
int tirarDados() {
    int d1 = dado(generador);  // Primer dado
    int d2 = dado(generador);  // Segundo dado
    cout << endl << "Dados: [" << d1 << "] + [" << d2 << "] = " << (d1 + d2) << endl;
    return d1 + d2;  // Retornar la suma (total de pasos)
}

/*
Muestra el estado completo de un jugador en consola de forma formateada.
Incluye nombre, dinero disponible, posición actual en el tablero, estado
de cárcel y lista de propiedades que posee con sus respectivos colores.
*/
void mostrarEstadoJugador(const Jugador &j, const Juego &juego) {
    cout << endl << "-----------------------------------------" << endl;
    cout << "Jugador: " << j.nombre << endl;
    cout << "Dinero: $" << j.dinero << endl;
    cout << "Posicion: " << j.posicion->nombre << endl;

    // Mostrar estado de cárcel si aplica
    if (j.enCarcel) cout << "[EN CARCEL]" << endl;
    
    // Mostrar cantidad y lista de propiedades con sus colores
    cout << "Propiedades: " << j.propiedades.size();
    if (j.propiedades.size() > 0) {
        for (size_t i = 0; i < j.propiedades.size(); i++) {
            cout << ", " << j.propiedades[i];
            
            // Buscar la propiedad en el mapa para obtener su color
            auto it = juego.propiedades.find(j.propiedades[i]);
            if (it != juego.propiedades.end()) {
                const Propiedad &prop = it->second;
                // Mostrar el color si la propiedad tiene uno (no está vacío)
                if (!prop.color.empty()) {
                    cout << " (" << prop.color << ")";
                }
            }
        }
    }
    cout << endl << "-----------------------------------------" << endl;
}

/*
Muestra el menú de acciones disponibles para el jugador según el tipo
de casilla en la que se encuentra. El menú varía según:
- Si es una propiedad disponible: opción de comprar
- Si es una propiedad de otro jugador: opción de pagar alquiler
- Si es una propiedad propia: opción de construir casas
- Si es una casilla especial: opciones específicas (impuestos, cartas, etc.)
*/
void mostrarMenuAcciones(Jugador &j, Casilla *casilla, Juego &juego) {
    cout << endl << "----- MENU DE ACCIONES -----" << endl << endl;
    cout << "Ubicacion: " << casilla->nombre << " [" << casilla->tipo << "]" << endl;
    
    // Casillas que pueden ser propiedades (normales, ferrocarriles, servicios)
    if (casilla->tipo == "Propiedad" || casilla->tipo == "Ferrocarril" || casilla->tipo == "Servicio" || casilla->tipo == "Estacion") {
        // Buscar la propiedad en el mapa de propiedades del juego
        auto it = juego.propiedades.find(casilla->nombre);
        if (it != juego.propiedades.end()) {
            Propiedad &prop = it->second;
            
            // Caso 1: Propiedad sin dueño (disponible para compra)
            if (!prop.tieneDueno) {
                cout << "1. Comprar propiedad ($" << prop.precio << ")" << endl;
                cout << "2. Ver tablero" << endl;
                cout << "3. Pasar" << endl;

            // Caso 2: Propiedad de otro jugador (debe pagar alquiler)
            } else if (prop.dueno->nombre != j.nombre) {
                cout << "Esta propiedad pertenece a: " << prop.dueno->nombre << endl;
                cout << "Alquiler: $" << prop.alquiler[prop.numCasas] << endl;
                cout << "1. Pagar alquiler" << endl;
                cout << "2. Ver tablero" << endl;

            // Caso 3: Propiedad propia (puede construir mejoras)
            } else {
                cout << "Esta es tu propiedad" << endl;
                cout << "1. Construir casa ($" << prop.precioCasa << ")" << endl;
                cout << "2. Ver tablero" << endl;
                cout << "3. Pasar" << endl;
            }
        } else {
            // Si no se encuentra la propiedad en el mapa, mostrar opciones básicas
            cout << "1. Comprar propiedad" << endl;
            cout << "2. Ver tablero" << endl;
            cout << "3. Pasar" << endl;
        }
    } else if (casilla->tipo == "Impuesto") {
        cout << "Debes pagar $" << casilla->precio << " en impuestos" << endl;
        cout << "1. Pagar impuesto" << endl;
        cout << "2. Ver tablero" << endl;

    } else if (casilla->tipo == "VayaCarcel") {
        cout << "Ve a la carcel!" << endl;
        cout << "1. Ir a la carcel" << endl;
        cout << "2. Ver tablero" << endl;
        cout << "3. Pasar" << endl;

    } else if (casilla->tipo == "Arca Comunal" || casilla->tipo == "ArcaComunal") {
        cout << "Arca Comunal - Saca una carta" << endl;
        cout << "1. Sacar carta" << endl;
        cout << "2. Ver tablero" << endl;
        cout << "3. Pasar" << endl;

    } else if (casilla->tipo == "Casualidad") {
        cout << "Casualidad - Saca una carta" << endl;
        cout << "1. Sacar carta" << endl;
        cout << "2. Ver tablero" << endl;
        cout << "3. Pasar" << endl;

    } else {
        cout << "1. Ver tablero" << endl;
        cout << "2. Pasar" << endl;
    }
    cout << endl << "----------------------------" << endl;
}

/*
Procesa el efecto de una carta (Arca Comunal o Casualidad) en el jugador.
Según el código de efecto de la carta, ejecuta diferentes acciones:
- Efecto 1: Cobrar dinero del banco
- Efecto 2: Pagar dinero al banco (el monto se extrae del mensaje)
- Efecto 3: Avanzar hasta Go y cobrar $200
- Efecto 4: Ir a la cárcel sin pasar por Go
- Efecto 5: Cobrar dinero de cada jugador activo
- Efecto 6: Avanzar al servicio más cercano
- Efecto 7: Avanzar al ferrocarril más cercano
- Efecto 8: Ir a una propiedad específica (extrae el nombre del mensaje)
- Efecto 9: Retroceder 3 espacios
- Efecto 10: Avanzar a la próxima propiedad disponible
*/
void procesarCarta(Carta &carta, Jugador &j, Juego &juego) {
    system("cls");
    cout << endl << "========================================" << endl;
    cout << "CARTA: " << carta.mensaje << endl;
    cout << "========================================" << endl;
    
    switch (carta.efecto) {
        case 1: {
            // Efecto 1: Cobrar dinero del banco (típicamente $200)
            cobrar(j, 200);
            break;
        }
        case 2: {
            // Efecto 2: Pagar dinero al banco
            // El monto varía según la carta, se extrae del mensaje
            int monto = 50; // Valor por defecto
            if (carta.mensaje.find("$100") != string::npos) monto = 100;
            else if (carta.mensaje.find("$20") != string::npos) monto = 20;
            else if (carta.mensaje.find("$15") != string::npos) monto = 15;
            else if (carta.mensaje.find("$50") != string::npos) monto = 50;
            
            if (j.dinero >= monto) {
                pagar(j, monto);
            } else {
                cout << "No tienes dinero suficiente para pagar." << endl;
            }
            break;
        }
        case 3: {
            // Efecto 3: Avanzar hasta Go y cobrar $200
            cout << "Avanzas hasta Go!" << endl;
            j.posicion = juego.tablero.inicio;
            cobrar(j, 200);  // Cobrar por pasar por Go
            cout << j.nombre << " esta ahora en: " << j.posicion->nombre << endl;
            break;
        }
        case 4: {
            // Efecto 4: Ir a la cárcel sin pasar por Go ni cobrar $200
            cout << "Vas a la carcel! No pasas por Go. No cobras $200." << endl;
            j.enCarcel = true;
            j.turnosEnCarcel = 0;
            
            // Buscar la casilla de cárcel recorriendo el tablero
            Casilla* actual = juego.tablero.inicio;
            for (int i = 0; i < juego.tablero.totalCasillas; i++) {
                if (actual->tipo == "Carcel") {
                    j.posicion = actual;
                    break;
                }
                actual = actual->siguiente;
            }
            cout << j.nombre << " esta ahora en: " << j.posicion->nombre << endl;
            break;
        }
        case 5: {
            // Efecto 5: Cobrar dinero de cada jugador activo
            int monto = 25;  // Monto a cobrar de cada jugador
            int totalCobrado = 0;
            
            // Recorrer todos los jugadores y cobrarles si tienen dinero
            for (int i = 0; i < juego.numJugadores; i++) {
                if (juego.jugadores[i].nombre != j.nombre && juego.jugadores[i].activo) {
                    if (juego.jugadores[i].dinero >= monto) {
                        juego.jugadores[i].dinero -= monto;
                        totalCobrado += monto;
                    }
                }
            }
            j.dinero += totalCobrado;
            cout << j.nombre << " cobro $" << totalCobrado << " de los otros jugadores." << endl;
            break;
        }
        case 6: {
            // Efecto 6: Avanzar al servicio más cercano (Electric Company o Water Works)
            cout << "¡Avanzas al servicio más cercano!" << endl;
            
            // Buscar el siguiente servicio recorriendo el tablero hacia adelante
            Casilla* actual = j.posicion->siguiente;
            while (actual->tipo != "Servicio" && actual != j.posicion) {
                actual = actual->siguiente;
            }
            
            if (actual->tipo == "Servicio") {
                j.posicion = actual;
                cout << j.nombre << " esta ahora en: " << j.posicion->nombre << endl;
            }
            break;
        }
        case 7: {
            // Efecto 7: Avanzar al ferrocarril más cercano
            cout << "¡Avanzas al ferrocarril más cercano!" << endl;
            
            // Buscar el siguiente ferrocarril recorriendo el tablero hacia adelante
            Casilla* actual = j.posicion->siguiente;
            while ((actual->tipo != "Estacion" && actual->tipo != "Ferrocarril") && actual != j.posicion) {
                actual = actual->siguiente;
            }
            
            if (actual->tipo == "Estacion" || actual->tipo == "Ferrocarril") {
                j.posicion = actual;
                cout << j.nombre << " esta ahora en: " << j.posicion->nombre << endl;
            }
            break;
        }
        case 8: {
            // Efecto 8: Ir a una propiedad específica mencionada en la carta
            cout << "¡Te mueves a una propiedad especifica!" << endl;
            
            // Extraer el nombre de la propiedad buscando palabras clave en el mensaje
            string nombrePropiedad = "";
            if (carta.mensaje.find("Illinois") != string::npos) nombrePropiedad = "Illinois Avenue";
            else if (carta.mensaje.find("Charles") != string::npos) nombrePropiedad = "St. Charles Place";
            else if (carta.mensaje.find("Reading") != string::npos) nombrePropiedad = "Reading Railroad";
            else if (carta.mensaje.find("Boardwalk") != string::npos) nombrePropiedad = "Boardwalk";
            
            // Buscar la propiedad en el tablero y mover al jugador
            if (!nombrePropiedad.empty()) {
                Casilla* actual = juego.tablero.inicio;
                for (int i = 0; i < juego.tablero.totalCasillas; i++) {
                    if (actual->nombre == nombrePropiedad) {
                        j.posicion = actual;
                        cout << j.nombre << " esta ahora en: " << j.posicion->nombre << endl;
                        break;
                    }
                    actual = actual->siguiente;
                }
            }
            break;
        }
        case 9: {
            // Efecto 9: Retroceder 3 espacios en el tablero
            cout << "¡Retrocedes 3 espacios!" << endl;
            j.posicion = retrocederEnTablero(j.posicion, 3);
            cout << j.nombre << " esta ahora en: " << j.posicion->nombre << endl;
            break;
        }
        case 10: {
            // Efecto 10: Avanzar a la próxima propiedad disponible (sin dueño)
            cout << "Avanzas a la proxima propiedad disponible!" << endl;
            
            // Buscar la siguiente propiedad sin dueño recorriendo el tablero
            Casilla* actual = j.posicion->siguiente;
            while (actual != j.posicion) {
                // Verificar que sea una propiedad y que esté en el mapa
                if ((actual->tipo == "Propiedad" || actual->tipo == "Estacion" || actual->tipo == "Servicio") 
                    && juego.propiedades.count(actual->nombre) > 0) {
                    // Verificar que no tenga dueño
                    if (!juego.propiedades[actual->nombre].tieneDueno) {
                        j.posicion = actual;
                        cout << j.nombre << " esta ahora en: " << j.posicion->nombre << endl;
                        break;
                    }
                }
                actual = actual->siguiente;
            }
            break;
        }
        default:
            cout << "Efecto desconocido." << endl;
    }
}

/*
Procesa la acción seleccionada por el jugador desde el menú de acciones.
Según el tipo de casilla y la opción elegida, ejecuta diferentes operaciones:
- Comprar propiedades
- Pagar alquileres
- Construir casas/hoteles
- Pagar impuestos
- Ir a la cárcel
- Sacar cartas (Arca Comunal o Casualidad)
- Ver el tablero
- Pasar el turno
Maneja recursivamente el caso de "ver tablero" para permitir múltiples vistas.
*/
void procesarAccion(int opcion, Jugador &j, Casilla *casilla, Juego &juego) {
    // Si elige ver tablero en una casilla neutral, mostrarlo y volver a preguntar
    if (opcion == 1 && (casilla->tipo != "Propiedad" && casilla->tipo != "Ferrocarril" && 
                        casilla->tipo != "Servicio" && casilla->tipo != "Estacion" && 
                        casilla->tipo != "Impuesto" && casilla->tipo != "VayaCarcel" &&
                        casilla->tipo != "Arca Comunal" && casilla->tipo != "ArcaComunal" && 
                        casilla->tipo != "Casualidad")) {
        
        mostrarTablero(juego.tablero);
        cout << endl << "----------------------------" << endl;
        cout << "1. Ver tablero" << endl;
        cout << "2. Pasar" << endl;
        cout << endl << "----------------------------" << endl;
        cout << "Elige una opcion (1-2): ";
        int opcionNueva;
        cin >> opcionNueva;
        procesarAccion(opcionNueva, j, casilla, juego);
        return;
    }
    
    if (casilla->tipo == "Propiedad" || casilla->tipo == "Ferrocarril" || casilla->tipo == "Servicio" || casilla->tipo == "Estacion") {
        auto it = juego.propiedades.find(casilla->nombre);
        if (it != juego.propiedades.end()) {
            Propiedad &prop = it->second;
            
            // Opción 2 = Ver tablero
            if (opcion == 2) {
                mostrarTablero(juego.tablero);
                cout << endl << "----- MENU DE ACCIONES -----" << endl << endl;
                cout << "Ubicacion: " << casilla->nombre << " [" << casilla->tipo << "]" << endl;
                
                if (!prop.tieneDueno) {
                    cout << "1. Comprar propiedad ($" << prop.precio << ")" << endl;
                    cout << "2. Ver tablero" << endl;
                    cout << "3. Pasar" << endl;
                    cout << endl << "----------------------------" << endl;
                    cout << "Elige una opcion: ";
                } else if (prop.dueno->nombre != j.nombre) {
                    cout << "Esta propiedad pertenece a: " << prop.dueno->nombre << endl;
                    cout << "Alquiler: $" << prop.alquiler[prop.numCasas] << endl;
                    cout << "1. Pagar alquiler" << endl;
                    cout << "2. Ver tablero" << endl;
                    cout << endl << "----------------------------" << endl;
                    cout << "Elige una opcion: ";
                } else {
                    cout << "Esta es tu propiedad" << endl;
                    cout << "1. Construir casa ($" << prop.precioCasa << ")" << endl;
                    cout << "2. Ver tablero" << endl;
                    cout << "3. Pasar" << endl;
                    cout << endl << "----------------------------" << endl;
                    cout << "Elige una opcion: ";
                }
                int opcionNueva;
                cin >> opcionNueva;
                procesarAccion(opcionNueva, j, casilla, juego);
                return;
            }
            
            // Si es propiedad de otro jugador, debe pagar (no hay opción 3)
            if (opcion == 3) {
                if (!prop.tieneDueno || prop.dueno->nombre == j.nombre) {
                    return; // Solo permite pasar si la propiedad es disponible o es suya
                }
            }
            
            if (opcion == 1) {
                if (!prop.tieneDueno) {
                    // Intentar comprar
                    if (j.dinero >= prop.precio) {
                        j.dinero -= prop.precio;
                        juego.banco.dineroTotal += prop.precio;
                        prop.tieneDueno = true;
                        prop.disponible = false;
                        prop.dueno = &j;
                        j.propiedades.push_back(prop.nombre);
                        cout << endl << j.nombre << " compro " << casilla->nombre << " por $" << prop.precio 
                             << " | Dinero restante: $" << j.dinero << endl;
                    } else {
                        cout << endl << j.nombre << " no tiene suficiente dinero ($" << j.dinero 
                             << " < $" << prop.precio << ")" << endl;
                    }
                } else if (prop.dueno->nombre != j.nombre) {
                    // Pagar alquiler
                    int alquiler = prop.alquiler[prop.numCasas];
                    if (j.dinero >= alquiler) {
                        j.dinero -= alquiler;
                        prop.dueno->dinero += alquiler;
                        cout << endl << j.nombre << " pago $" << alquiler << " de alquiler a " 
                             << prop.dueno->nombre << " | Dinero restante: $" << j.dinero << endl;
                    } else {
                        cout << endl << j.nombre << " no tiene dinero para pagar alquiler ($" 
                             << j.dinero << " < $" << alquiler << ")" << endl;
                    }
                } else {
                    // Es dueño de la propiedad - intentar construir casa
                    if (!poseeTodasLasPropiedadesDelColor(j, prop, juego)) {
                        cout << endl << "No puedes construir. Necesitas poseer TODAS las propiedades de color " 
                             << prop.color << "." << endl;
                        return;
                    }
                    
                    if (prop.numCasas == 5) {
                        cout << endl << "Ya tienes un hotel aqui. No puedes construir mas." << endl;
                    } else if (prop.numCasas == 4) {
                        // Opción de comprar hotel
                        if (j.dinero >= prop.precioCasa) {
                            j.dinero -= prop.precioCasa;
                            prop.numCasas = 5;
                            cout << endl << j.nombre << " construyo un HOTEL en " << casilla->nombre 
                                 << " por $" << prop.precioCasa << " | Dinero restante: $" << j.dinero << endl;
                        } else {
                            cout << endl << j.nombre << " no tiene suficiente dinero para construir hotel ($" 
                                 << j.dinero << " < $" << prop.precioCasa << ")" << endl;
                        }
                    } else if (prop.numCasas < 4) {
                        // Construir una casa más
                        if (j.dinero >= prop.precioCasa) {
                            j.dinero -= prop.precioCasa;
                            prop.numCasas++;
                            cout << endl << j.nombre << " construyo una CASA en " << casilla->nombre 
                                 << " por $" << prop.precioCasa << " | Dinero restante: $" << j.dinero << endl;
                        } else {
                            cout << endl << j.nombre << " no tiene suficiente dinero para construir casa ($" 
                                 << j.dinero << " < $" << prop.precioCasa << ")" << endl;
                        }
                    }
                }
            }
        }
    } else if (casilla->tipo == "Impuesto") {
        if (opcion == 2) {
            mostrarTablero(juego.tablero);
            cout << endl << "Debes pagar $" << casilla->precio << " en impuestos" << endl;
            cout << "1. Pagar impuesto" << endl;
            cout << "2. Ver tablero" << endl;
            cout << endl << "----------------------------" << endl;
            cout << "Elige una opcion: ";
            int opcionNueva;
            cin >> opcionNueva;
            procesarAccion(opcionNueva, j, casilla, juego);
            return;
        }
        
        if (opcion == 1) {
            if (j.dinero >= casilla->precio) {
                cobrarBanco(juego.banco, j, casilla->precio);
                cout << endl << j.nombre << " pago $" << casilla->precio << " de impuestos" << endl;
            } else {
                cout << endl << "No tienes dinero suficiente para pagar impuestos" << endl;
            }
        }
    } else if (casilla->tipo == "VayaCarcel") {
        if (opcion == 2) {
            mostrarTablero(juego.tablero);
            cout << endl << "Ve a la carcel!" << endl;
            cout << "1. Ir a la carcel" << endl;
            cout << "2. Ver tablero" << endl;
            cout << "3. Pasar" << endl;
            cout << "----------------------------" << endl;
            cout << "Elige una opcion: ";
            int opcionNueva;
            cin >> opcionNueva;
            procesarAccion(opcionNueva, j, casilla, juego);
            return;
        }
        if (opcion == 3) return;
        
        if (opcion == 1) {
            j.enCarcel = true;
            j.turnosEnCarcel = 0;
            cout << endl << j.nombre << " esta en la carcel!" << endl;
        }
    } else if (casilla->tipo == "Arca Comunal" || casilla->tipo == "ArcaComunal") {
        if (opcion == 2) {
            mostrarTablero(juego.tablero);
            cout << endl << "Arca Comunal - Saca una carta" << endl;
            cout << "1. Sacar carta" << endl;
            cout << "2. Ver tablero" << endl;
            cout << "3. Pasar" << endl;
            cout << "----------------------------" << endl;
            cout << "Elige una opcion: ";
            int opcionNueva;
            cin >> opcionNueva;
            procesarAccion(opcionNueva, j, casilla, juego);
            return;
        }
        if (opcion == 3) return;
        
        if (opcion == 1) {
            Carta carta = sacarCarta(juego.arcaComunal);
            procesarCarta(carta, j, juego);
        }
    } else if (casilla->tipo == "Casualidad") {
        if (opcion == 2) {
            mostrarTablero(juego.tablero);
            cout << endl << "Casualidad - Saca una carta" << endl;
            cout << "1. Sacar carta" << endl;
            cout << "2. Ver tablero" << endl;
            cout << "3. Pasar" << endl;
            cout << "----------------------------" << endl;
            cout << "Elige una opcion: ";
            int opcionNueva;
            cin >> opcionNueva;
            procesarAccion(opcionNueva, j, casilla, juego);
            return;
        }
        if (opcion == 2) return; // Para "Pasar"
        
        if (opcion == 1) {
            Carta carta = sacarCarta(juego.casualidad);
            procesarCarta(carta, j, juego);
        }
    }
}

/*
Inicializa completamente el juego Monopoly con todos sus componentes.
Crea el tablero con las 40 casillas, inicializa el banco con dinero y propiedades,
carga todas las propiedades del juego, carga las cartas (Arca Comunal y Casualidad),
crea los jugadores especificados (máximo 4) e inicializa la pila de estados para
la funcionalidad de deshacer. Todos los jugadores comienzan en la casilla "Go"
con dinero inicial y sin propiedades.
*/
void inicializarJuego(Juego &juego, int numJugadores) {
    // Paso 1: Crear el tablero con todas las casillas enlazadas circularmente
    crearTablero(juego.tablero);
    
    // Paso 2: Crear el banco con dinero inicial
    juego.banco = crearBanco();
    
    // Paso 3: Cargar todas las propiedades del Monopoly en el mapa
    cargarTodasLasPropiedades(juego.propiedades);
    
    // Paso 4: Registrar todas las propiedades en el banco (disponibles para compra)
    for (auto &prop : juego.propiedades) {
        registrarPropiedad(juego.banco, prop.second);
    }
    
    // Paso 5: Cargar las cartas de Arca Comunal y Casualidad
    cargarArcaComunal(juego.arcaComunal);
    cargarCasualidad(juego.casualidad);
    
    // Paso 6: Inicializar la pila de estados para funcionalidad de deshacer
    juego.pilaEstados = crearPila();
    
    // Paso 7: Crear los jugadores (máximo 4)
    juego.numJugadores = min(numJugadores, 4);
    string nombres[4] = {"Jugador 1", "Jugador 2", "Jugador 3", "Jugador 4"};
    
    for (int i = 0; i < juego.numJugadores; i++) {
        juego.jugadores[i] = crearJugador(nombres[i], juego.tablero.inicio);
        juego.jugadores[i].activo = true;  // Todos los jugadores comienzan activos
    }
    
    // Paso 8: Establecer el turno inicial (primer jugador)
    juego.turnActual = 0;
}

/*
Ejecuta un turno completo de un jugador en el juego.
El turno incluye:
1. Capturar el estado inicial del jugador (para poder deshacer)
2. Mostrar el estado actual del jugador
3. Permitir al jugador tirar los dados (o ver el tablero primero)
4. Mover al jugador según el resultado de los dados
5. Permitir deshacer el turno si el jugador lo desea
6. Mostrar la casilla en la que cayó
7. Mostrar el menú de acciones disponibles
8. Procesar la acción seleccionada por el jugador
El jugador puede ver el tablero antes de tirar los dados si lo desea,
y puede deshacer su turno después de tirar los dados.
*/
void turnoJugador(Jugador &j, Juego &juego) {
    // Capturar el estado inicial del jugador antes de comenzar el turno
    // Esto permite deshacer el turno completo si el jugador lo desea
    Estado estadoInicial = capturarEstado(j, juego.banco, juego.tablero);
    guardarEstado(juego.pilaEstados, estadoInicial);
    
    // Mostrar el estado actual del jugador (con colores de propiedades)
    mostrarEstadoJugador(j, juego);
    
    cout << endl << "========================================" << endl;
    cout << "Turno de " << j.nombre << endl;
    cout << "========================================" << endl;
    
    // Menú inicial: tirar dados o ver tablero
    cout << endl << "1. Tirar dados" << endl;
    cout << "2. Ver tablero" << endl;
    cout << "----------------------------" << endl;
    cout << "Elige una opcion: ";
    int opcionInicial;
    cin >> opcionInicial;
    
    // Si elige ver tablero, mostrarlo y permitir verlo nuevamente o tirar dados
    if (opcionInicial == 2) {
        mostrarTablero(juego.tablero);
        
        // Volver a mostrar el menú inicial
        cout << endl << "1. Tirar dados" << endl;
        cout << "2. Ver tablero" << endl;
        cout << "----------------------------" << endl;
        cout << "Elige una opcion: ";
        cin >> opcionInicial;
        
        // Si elige ver tablero de nuevo, mostrarlo y forzar a tirar dados después
        if (opcionInicial == 2) {
            mostrarTablero(juego.tablero);
            opcionInicial = 1; // Forzar a tirar dados después de ver el tablero
        }
    }
    
    // Tirar los dados y mover al jugador
    int movimiento = tirarDados();
    moverJugador(j, movimiento);
    
    // Mostrar el resultado del movimiento
    cout << endl << "-> " << j.nombre << " se movio a: " << j.posicion->nombre << endl;
    
    // Opción de deshacer el turno después de tirar los dados
    cout << endl << "Presiona Enter para ver el resultado o 'x' para deshacer turno: ";
    cin.ignore();
    char tecla = cin.get();
    
    // Si el jugador presiona 'x' o 'X', deshacer el turno
    if (tecla == 'x' || tecla == 'X') {
        // Deshacer el estado: restaurar el estado inicial
        if (!juego.pilaEstados.pila.empty()) {
            Estado estadoRestaurado = deshacerEstado(juego.pilaEstados);
            restaurarEstado(estadoRestaurado, j, juego.banco, juego.tablero);
            
            system("cls");
            cout << endl << "========================================" << endl;
            cout << "Turno deshecho. Volviendo al inicio del turno..." << endl;
            cout << "========================================" << endl << endl;
            
            // Volver a empezar el turno desde el principio (llamada recursiva)
            turnoJugador(j, juego);
            return;
        }
    }
    
    // Si no deshizo, continuar con el turno normalmente
    system("cls");
    cout << endl << "-> " << j.nombre << " esta en: " << j.posicion->nombre << endl;
    
    // Mostrar información de la casilla en la que cayó (con color si es propiedad)
    mostrarCasilla(j.posicion, juego.propiedades);
    
    // Mostrar el menú de acciones disponibles según el tipo de casilla
    mostrarMenuAcciones(j, j.posicion, juego);
    
    // Determinar el rango de opciones válidas según el tipo de casilla
    // (algunas casillas tienen menos opciones disponibles)
    int maxOpcion = 3;
    if (j.posicion->tipo == "Impuesto") {
        maxOpcion = 2;  // Solo pagar impuesto y ver tablero
    } else if (j.posicion->tipo == "Propiedad" || j.posicion->tipo == "Ferrocarril" || 
               j.posicion->tipo == "Servicio" || j.posicion->tipo == "Estacion") {
        auto it = juego.propiedades.find(j.posicion->nombre);
        if (it != juego.propiedades.end()) {
            Propiedad &prop = it->second;
            // Si la propiedad es de otro jugador, solo puede pagar alquiler o ver tablero
            if (prop.tieneDueno && prop.dueno->nombre != j.nombre) {
                maxOpcion = 2;
            }
        }
    }
    
    // Obtener la opción del jugador y procesarla
    cout << "Elige una opcion: ";
    int opcion;
    cin >> opcion;
    
    procesarAccion(opcion, j, j.posicion, juego);
    
    // Pausa antes de continuar al siguiente turno
    cout << endl << "Presiona Enter para continuar al siguiente turno" << endl;
    cin.ignore();
    cin.ignore();
    system("cls");
}

/*
Verifica si un jugador está en bancarrota (dinero <= 0).
Si el jugador está en bancarrota, lo marca como inactivo y muestra un mensaje.
Retorna true si el jugador está en bancarrota, false en caso contrario.
*/
bool verificarBancarrota(Jugador &j) {
    if (j.dinero <= 0) {
        cout << endl << j.nombre << " esta en bancarrota." << endl;
        j.activo = false;  // Marcar como inactivo (eliminado del juego)
        return true;
    }
    return false;
}

/*
Verifica si un jugador posee TODAS las propiedades de un mismo color.
Esta verificación es necesaria para poder construir casas y hoteles en
propiedades del Monopoly (regla del juego: solo se pueden construir
mejoras si se poseen todas las propiedades del mismo color).
No aplica para ferrocarriles y servicios públicos.
Retorna true si el jugador posee todas las propiedades del color, false en caso contrario.
*/
bool poseeTodasLasPropiedadesDelColor(const Jugador &j, const Propiedad &prop, const Juego &juego) {
    // Validación: ferrocarriles y servicios no tienen color, no se pueden construir casas
    if (prop.color.empty() || prop.esFerrocarril || prop.esServicios) {
        return false;
    }
    
    // Contar cuántas propiedades de este color existen en total en el juego
    int totalDelColor = 0;
    int poseidasDelColor = 0;
    
    // Recorrer todas las propiedades del juego
    for (const auto &par : juego.propiedades) {
        const Propiedad &p = par.second;
        
        // Si tiene el mismo color y no es ferrocarril ni servicio
        if (p.color == prop.color && !p.esFerrocarril && !p.esServicios) {
            totalDelColor++;
            
            // Verificar si el jugador es dueño de esta propiedad
            if (p.tieneDueno && p.dueno != nullptr && p.dueno->nombre == j.nombre) {
                poseidasDelColor++;
            }
        }
    }
    
    // El jugador debe poseer TODAS las propiedades del color (todas = poseídas)
    return (totalDelColor > 0 && totalDelColor == poseidasDelColor);
}

/*
Cuenta cuántos jugadores están aún activos en el juego (no en bancarrota).
Útil para determinar si el juego debe continuar o terminar (si solo queda 1 jugador activo).
Retorna el número de jugadores activos.
*/
int contarJugadoresActivos(Juego &juego) {
    int count = 0;
    for (int i = 0; i < juego.numJugadores; i++) {
        if (juego.jugadores[i].activo) count++;
    }
    return count;
}
