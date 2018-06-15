//
// Created by nelon on 6/15/2018.
//

#include "funcionesMain.h"

void holaExterno() {
    cout << "hola";
}

char leerOpciones(const std::string &opciones, const std::string &texto) {
    char entrada;
    bool entradaCorrecta;
    char i;
    do {
        cout << texto << endl;
        LEERSTRING(entrada);

        entradaCorrecta = false;
        i = 0;
        while ('\0' != opciones[i]) {
            entradaCorrecta |= (entrada == opciones[i]);
            i++;
        }
    } while (!entradaCorrecta);
    return entrada;
}

// funciones para cargar un estado en el automata

void cargarEstado(AFD &a) {
    std::string nombre;
    int salida;
    cout << "Ingresando nuevo Estado\n";
    cout << "\tNombre del Estado: ";
    LEERSTRING(nombre);

    salida = leerOpciones("01", "Ingrese 1 si es de salida (0 si no)");

    try {
        a.setEstado(nombre, (bool) salida);
    } catch (int exc) {
        if (-1 == exc)
            cout << "\n\tEl autómata ya tiene todos sus estados definidos\n";
        else {
            if (-2 == exc)
                cout << "\n\tYa existe un Estado con el mismo nombre\n";
            else
                cout << "\n\tERROR: " << exc << "\n";
        }
    }
}

void cargarEstado(APila &a) {
    std::string nombre;
    int salida;
    cout << "Ingresando nuevo Estado\n";
    cout << "\tNombre del Estado: ";
    LEERSTRING(nombre);

    salida = leerOpciones("01", "Ingrese 1 si es de salida (0 si no)");

    try {
        a.setEstado(nombre, (bool) salida);
    } catch (int exc) {
        if (-1 == exc)
            cout << "\n\tEl autómata ya tiene todos sus estados definidos\n";
        else {
            if (-2 == exc)
                cout << "\n\tYa existe un Estado con el mismo nombre\n";
            else
                cout << "\n\tERROR: " << exc << "\n";
        }
    }
}

void cargarEstado(MTuring &a) {
    std::string nombre;
    int salida;
    cout << "Ingresando nuevo Estado\n";
    cout << "\tNombre del Estado: ";
    LEERSTRING(nombre);

    salida = leerOpciones("01", "Ingrese 1 si es de salida (0 si no)");

    try {
        a.setEstado(nombre, (bool) salida);
    } catch (int exc) {
        if (-1 == exc)
            cout << "\n\tEl autómata ya tiene todos sus estados definidos\n";
        else {
            if (-2 == exc)
                cout << "\n\tYa existe un Estado con el mismo nombre\n";
            else
                cout << "\n\tERROR: " << exc << "\n";
        }
    }
}

// funciones para seleccionar el estado inicial del automata

void cargarEstadoInicial(AFD &a) {
    string nom;
    cout << "Ingrese el nombre del estado inicial\n";
    LEERSTRING(nom);

    try {
        a.setEstadoInicial(nom);
    } catch (int exc) {
        if (-1 == exc) {
            cout << "\nNo hay ningun estado con ese nombre\n";
        } else {
            if (-10 == exc)
                cout << "\nEl Automata ya tiene estado de salida\n";
            else
                cout << "\nERROR: " << exc << "\n";
        }
    }
}

void cargarEstadoInicial(APila &a) {
    string nom;
    cout << "Ingrese el nombre del estado inicial\n";
    LEERSTRING(nom);

    try {
        a.setEstadoInicial(nom);
    } catch (int exc) {
        if (-1 == exc) {
            cout << "\nNo hay ningun estado con ese nombre\n";
        } else {
            if (-10 == exc)
                cout << "\nEl Automata ya tiene estado de salida\n";
            else
                cout << "\nERROR: " << exc << "\n";
        }
    }
}

void cargarEstadoInicial(MTuring &a) {
    string nom;
    cout << "Ingrese el nombre del estado inicial\n";
    LEERSTRING(nom);

    try {
        a.setEstadoInicial(nom);
    } catch (int exc) {
        if (-1 == exc) {
            cout << "\nNo hay ningun estado con ese nombre\n";
        } else {
            if (-10 == exc)
                cout << "\nEl Automata ya tiene estado de salida\n";
            else
                cout << "\nERROR: " << exc << "\n";
        }
    }
}

// funciones para cargar simbolos del alfabeto de entrada

void cargarSimboloEntrada(AFD &a) {
    char n;
    cout << "Ingresando nuevo simbolo de entrada\n";
    cin >> n;
    try {
        a.setAlfabeto(n);
    } catch (int exc) {
        if (-1 == exc)
            cout << "\n\tEl autómata ya tiene su alfabeto de entrada definido\n";
        else {
            if (-2 == exc)
                cout << "\n\tYa existe la entrada\n";
            else
                cout << "\n\tERROR: " << exc << "\n";
        }
    }
}

void cargarSimboloEntrada(APila &a) {
    char n;
    cout << "Ingresando nuevo simbolo de entrada\n";
    cin >> n;
    try {
        a.setAlfabeto(n);
    } catch (int exc) {
        if (-1 == exc)
            cout << "\n\tEl autómata ya tiene su alfabeto de entrada definido\n";
        else {
            if (-2 == exc)
                cout << "\n\tYa existe la entrada\n";
            else
                cout << "\n\tERROR: " << exc << "\n";
        }
    }
}

void cargarSimboloEntrada(MTuring &a) {
    char n;
    cout << "Ingresando nuevo simbolo de entrada\n";
    cin >> n;
    try {
        a.setAlfabeto(n);
    } catch (int exc) {
        if (-1 == exc)
            cout << "\n\tEl autómata ya tiene su alfabeto de entrada definido\n";
        else {
            if (-2 == exc)
                cout << "\n\tYa existe la entrada\n";
            else
                cout << "\n\tERROR: " << exc << "\n";
        }
    }
}

void cargarSimboloPila(APila &p) {
    char n;
    cout << "Ingresando nuevo simbolo de entrada de pila\n";
    cin >> n;
    try {
        p.setAlfabetoPila(n);
    } catch (int exc) {
        if (-1 == exc)
            cout << "\n\tEl autómata ya tiene su alfabeto de pila definido\n";
        else {
            if (-2 == exc)
                cout << "\n\tYa existía la entrada\n";
            else
                cout << "\n\tERROR: " << exc << "\n";
        }
    }
}

void cargarSimboloCinta(MTuring &p) {
    char n;
    cout << "Ingresando nuevo simbolo de entrada de cinta\n";
    cin >> n;
    try {
        p.setAlfabetoCinta(n);
    } catch (int exc) {
        if (-1 == exc)
            cout << "\n\tEl autómata ya tiene su alfabeto de cinta definido\n";
        else {
            if (-2 == exc)
                cout << "\n\tYa existía la entrada\n";
            else
                cout << "\n\tERROR: " << exc << "\n";
        }
    }
}

// define una a una las transiciones de la f

void definirUnaTransicion(AFD &a) {
    char entrada;
    string ESalida, EDestino;
    cout << "Ingreando nueva Transicion\n";

    cout << "\tNombre del Estado del cual se parte: ";
    LEERSTRING(ESalida);

    cout << "\tSímbolo de entrada: ";
    cin >> entrada;

    cout << "\tNombre del Estado al cual se llega: ";
    LEERSTRING(EDestino)

    try {
        a.setF(ESalida, entrada, EDestino);
    } catch (int exc) {
        switch (exc) {
            case -11:
                cout << " \n\tNo existe un estado con el nombre " << ESalida << "\n";
                break;

            case -12:
                cout << " \n\tNo existe un estado con el nombre " << EDestino << "\n";
                break;

            case -13:
                cout << "\n\t No existe la entrada " << entrada << "\n";
                break;

            case -14:
                cout << "\n\t Esta misma transicion ya fue definida previamente" "\n";
                break;

            case -23:
                cout << "\n\t La funcion de transicion ya fue definida en su totalidad \n";
                break;

            default:
                cout << "\n\tERROR: " << exc << "\n";
                break;
        }
    }
}

void definirUnaTransicion(APila &a) {
    char entrada, topePila, nuevoTope;
    bool consTope;
    string ESalida, EDestino;
    cout << "Ingreando nueva Transicion\n";

    cout << "\tNombre del Estado del cual se parte: ";
    LEERSTRING(ESalida);

    cout << "\tSímbolo de entrada: ";
    cin >> entrada;

    cout << "\tSímbolo de tope de pila: ";
    cin >> topePila;

    cout << "\tNombre del Estado al cual se llega: ";
    LEERSTRING(EDestino);

    cout << "\tNueva situación de la pila\n";
    consTope = leerOpciones("01", "\t\tConservar el valor tope anterior? (1 sí / 0 no): ");

    if (leerOpciones("01", "\t\tpilar otro valor más?(1 sí / 0 no):")) {
        cout << "\t\t\tIngrese el nuevo valor a apliar: ";
        cin >> nuevoTope;
    } else
        nuevoTope = (char) 0;

    try {
        a.setF(ESalida, entrada, topePila, EDestino, consTope, nuevoTope);
    } catch (int exc) {
        switch (exc) {
            case -11:
                cout << " \n\tNo existe un estado con el nombre " << ESalida << "\n";
                break;

            case -12:
                cout << " \n\tNo existe un estado con el nombre " << EDestino << "\n";
                break;

            case -13:
                cout << "\n\t No existe la entrada " << entrada << "\n";
                break;

            case -14:
                cout << "\n\t No se encuentra el simbolo " << topePila << " en la pila\n";
                break;

            case -15:
                cout << "\n\t No se puede apilar el simbolo " << nuevoTope << " en la pila\n";
                break;

            case -16:
                cout << "\n\t Esta misma transicion ya fue definida previamente" "\n";
                break;

            case -23:
                cout << "\n\t La funcion de transicion ya fue definida previamente \n";
                break;

            case -50:
                cout << "\n\t Transición errónea: se esperaba un estado que no fuera de salida\n";
                break;

            case -51:
                cout << "\n\t Transición errónea: se esperaba un estado que sea de salida\n";
                break;

            case -52:
                cout << "\n\t Transición errónea: no es posible reemplazar el simbolo fin de pila\n";
                break;

            case -53:
                cout << "\n\t Transición errónea: no se puede apiar otro fin de pila\n";
                break;

            default:
                cout << "\n\tERROR: " << exc << "\n";
                break;
        }
    }
}

void definirUnaTransicion(MTuring &a) {
    char lecturaCinta, escrituraCinta, direccionCabezal;
    string ESalida, EDestino;
    cout << "Ingreando nueva Transicion\n";

    cout << "\tNombre del Estado del cual se parte: ";
    LEERSTRING(ESalida);

    cout << "\tSímbolo que se lee de la cinta: ";
    cin >> lecturaCinta;

    cout << "\tSímbolo que se escribe en la cinta: ";
    cin >> escrituraCinta;

    cout << "\tDirección del cabezal (d, i, p): ";
    cin >> direccionCabezal;

    cout << "\tNombre del Estado al cual se llega: ";
    LEERSTRING(EDestino);

    try {
        a.setF(ESalida, lecturaCinta, EDestino, direccionCabezal, escrituraCinta);
    } catch (int exc) {
        switch (exc) {
            case -11:
                cout << " \n\tNo existe un estado con el nombre " << ESalida << "\n";
                break;

            case -12:
                cout << " \n\tNo existe un estado con el nombre " << ESalida << "\n";
                break;

            case -16:
                cout << "\n\t Esta misma transicion ya fue definida previamente" "\n";
                break;

            case -17:
                cout << "\n\t No se reconoce " << direccionCabezal << "como una direccion valida del cabezal\n";
                break;

            case -18:
                cout << "\n\t No se encuentra el simbolo " << lecturaCinta << " en la cinta\n";
                break;

            case -19:
                cout << "\n\t No se puede escribir el simbolo " << escrituraCinta << " en la cinta\n";
                break;

            case -23:
                cout << "\n\t La funcion de transicion ya fue definida previamente \n";
                break;

            case -50:
                cout << "\n\t Transición errónea: se esperaba un estado que no fuera de salida\n";
                break;

            case -51:
                cout << "\n\t Transición errónea: se esperaba un estado que sea de salida\n";
                break;

            default:
                cout << "\n\tERROR: " << exc << "\n";
                break;
        }
    }
}


// funciones para transicion
void hacerUnaTransicion(AFD &a) {
    cout << "Efectuando nueva transicion\n";
    try {
        a.transicion();
    } catch (int exc) {
        if (-8 == exc)
            cout << " \n\tEl automata no está listo para hacer transiciones\n";
        else
            cout << "ERROR: " << exc << "\n";
    }
    mostrarSalida(a);
}

void hacerUnaTransicion(APila &a) {
    cout << "Efectuando nueva transicion\n";
    cout << "\tIngresar la entrada: ";
    try {
        a.transicion();
    } catch (int exc) {
        switch (exc) {
            case -10:
                cout << " \n\tEl autómata esta apagado\n";
                break;
            case -20:
                cout << " \n\tDesbordamiento negativo de pila\n";
                break;
            case -30:
                cout << " \n\tEl automata no está listo para hacer transiciones\n";
                break;
            default:
                cout << "ERROR: " << exc << "\n";
                break;
        }
    }
    mostrarSalida(a);
}

void hacerUnaTransicion(MTuring &p) {
    cout << "Efectuando nueva transicion\n";
    try {
        p.transicion();
    } catch (int exc) {
        switch (exc) {
            case -1:
                cout << " \n\tEl autómata esta apagado\n";
                break;
            case -2:
                cout << " \n\tLa cinta no esta lista para ser leida por la maquina\n";
                break;
            case -3:
                cout << " \n\tEl cabezal de la máquina no ha sido situado en la cinta\n";
                break;
            case -21:
                cout << " \n\tNo se encuentra el simbolo de cinta (verifique que alfabeto de entrada"
                        " este comprendido en el alfabeto de cinta)\n";
            default:
                cout << "ERROR: " << exc << "\n";
                break;
        }
    }
    mostrarSalida(p);
}

void hacerTodasTransiciones(AFD &a) {
    while (!a.isAutomataApagado())
        hacerUnaTransicion(a);
}

void hacerTodasTransiciones(APila &a) {
    while (!a.isAutomataApagado())
        hacerUnaTransicion(a);
}

void hacerTodasTransiciones(MTuring &a) {
    while (!a.isAutomataApagado())
        hacerUnaTransicion(a);
}

// funciones para entrar la cadena a analizar por el automata
void ingresarCadenaAnalizar(AFD &a) {
    string r;
    cout << "Ingrese la cadena para que el automata analice\n";
    LEERSTRING(r);
    try {
        a.setCadenaAnalizar(r);
    } catch (int exc) {
        switch (exc) {
            case -2:
                cout
                        << " \n\tEl automata ya tiene una cadena a analizar, si desea que analice otra reinicie el automata\n";
                break;

            case -5:
                cout << " \n\tLa cadena vacía no es valida\n";
                break;

            case -21:
                cout << " \n\tLa cadena ingresada contiene simbolos no reconocidos por el automata\n";
                break;

            default:
                break;
        }
    }
}

void ingresarCadenaAnalizar(APila &a) {
    string r;
    cout << "Ingrese la cadena para que el automata analice\n";
    LEERSTRING(r);
    try {
        a.setCadenaAnalizar(r);
    } catch (int exc) {
        switch (exc) {
            case -2:
                cout
                        << " \n\tEl automata ya tiene una cadena a analizar, si desea que analice otra reinicie el automata\n";
                break;

            case -5:
                cout << " \n\tLa cadena vacía no es valida\n";
                break;

            case -21:
                cout << " \n\tLa cadena ingresada contiene simbolos no reconocidos por el automata\n";
                break;

            default:
                cout << "ERROR: " << exc << "\n";
                break;
        }
    }
}

void ingresarCadenaAnalizar(MTuring &a) {
    string r;
    cout << "Ingrese la cadena para que el automata analice\n";
    LEERSTRING(r);
    try {
        a.setCadenaAnalizar(r);
    } catch (int exc) {
        switch (exc) {
            case -2:
                cout
                        << "\n\tEl automata ya tiene una cadena a analizar, si desea que analice otra reinicie el automata\n";
                break;

            case -5:
                cout << "\n\tLa cadena vacía no es valida\n";
                break;

            case -21:
                cout << "\n\tLa cadena ingresada contiene simbolos no reconocidos por el automata\n";
                break;

            default:
                cout << "ERROR: " << exc << "\n";
                break;
        }
    }
}

// funciones para poner el cabezal para la maquina de turing
void ponerCabezalCinta(MTuring &p) {
    unsigned int pos;
    cout << "\nIngrese la posición en donde comienza el cabezal\n";
    cout << "La cinta actualmente se encuentra así:\n";
    cout << p.getCopiaCinta() << endl;
    cin >> pos;

    try {
        p.ponerCabezal(pos);
    } catch (int exc) {
        switch (exc) {
            case -1:
                cout << "\n\tLa cinta no esta lista para poner el cabezal\n";
                break;
            case -2:
                cout << "\n\tEl cabezal ya ha sido colocado previamente\n";
                break;
            case -3:
                cout << "\n\tNo se encuentra la posición ingresada\n";
                break;
            default:
                cout << "ERROR: " << exc << "\n";
                break;
        }

    }
}


// funciones para mostrar salida

void mostrarSalida(AFD &a) {
    cout << "Se ha alcanzado el estado: " << a.getNombreEstadoActual() << "\n";
    if (a.getSituacionEstadoActual())
        cout << " \t SALIDA\n ";
}

void mostrarSalida(APila &a) {
    cout << "Se ha alcanzado el estado: " << a.getNombreEstadoActual() << "\n";
    if (a.getSituacionEstadoActual())
        cout << " \t SALIDA\n ";
    try {
        cout << "El tope de pila es : " << a.getTopeDePila() << "\n";
    } catch (int exc) {
        if (-11 == exc) {
            cout << "\nDesbordamiento de pila\n";
        } else {
            cout << "\nERROR: " << exc << "\n";
        }
    }
}

void mostrarSalida(MTuring &a) {
    cout << "Se ha alcanzado el estado: " << a.getNombreEstadoActual() << "\n";
    if (a.getSituacionEstadoActual())
        cout << " \t SALIDA\n ";
    cout << " El cabezal de la máquina lee " << a.getLecturaCabezal() << endl;
    cout << "La cinta se encuentra así " << a.getCopiaCinta() << endl;
}