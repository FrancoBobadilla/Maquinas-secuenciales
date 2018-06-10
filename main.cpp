#include <iostream>
#include "AFD.h"
#include "APila.h"
#include "MTuring.h"
// o solo include de clase Automata abs?

#define LEERSTRING(X) fflush(stdin); cin >> X; fflush(stdin);

using namespace std;

// todas estas funciones podrían formar parte de la clase Automata,
// proveen una forma estandar de interactuar con el automata.

void cargarEstados(Automata *a) {
    std::string nombre;
    int salida;
    char t;
    do {
        cout << "Ingresando nuevo Estado\n";
        cout << "\tNombre del Estado: ";
        LEERSTRING(nombre);

        do {
            cout << "\n\tIngrese 1 si es de salida (0 si no): ";
            cin >> salida;
        } while (salida != 0 && salida != 1);

        try {
            a->setEstado(nombre, (bool) salida);
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
        cout << "\nIngrese 1 para nuevo Estado o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
    //podria mostrarse cuantos se han ingresado y el la cant max de estados.
}

void cargarAlfabetoEntradas(Automata *a) {
    char n;
    int tmp;
    char t;

    cout << "Ingresar el alfabeto de Entrada" << endl;
    do {
        cout << "Ingresando nueva Entrada\n";
        cout << "\tSímbolo de entrada: ";
        cin >> n;

        try {
            a->setAlfabeto(n);
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
        cout << "Ingrese 1 para nueva Entrada o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
}

void cargarEstadoInicial(Automata *a) {
    string nom;
    cout << "Ingresando el Estado Inicial del Autómata\n";
    cout << "Ingrese el nombre del estado inicial\n";
    LEERSTRING(nom);

    try {
        a->setEstadoInicial(nom);
    } catch (int exc) {
        if (-1 == exc) {
            cout << "\nNo hay ningun estado con ese nombre\n";
            cargarEstadoInicial(a);
        } else
            cout << "\nERROR: " << exc << "\n";
    }
}

void MostrarSalida(Automata *a) {
    cout << "Se ha alcanzado el estado: " << a->getNombreEstadoActual() << "\n";
    if (a->getSituacionEstadoActual()) {
        cout << " \t SALIDA\n ";
    }
    //Se deberia considerar querer mostrrar el tope de pila para automatas de pila
}

void efectuarTransicion(Automata *a) {
    char ent;
    cout << "Efectuando nueva transicion\n";
    cout << "\tIngresar la entrada: ";
    cin >> ent;
    try {
        a->transicion(ent);
    } catch (int exc) {
        if (-8 == exc)
            cout << " \n\tLa función de transicion no está completamente cargada\n";
        else {
            if (-21 == exc)
                cout << "\n\tLa entrada no es válida para el autómata\n";
            else
                cout << "ERROR: " << exc << "\n";
        }
    }


    MostrarSalida(a);
}
//esta funcion puede ser la misma para AFD y AP si se oculta la pila en el segundo caso

// todas estas funciones podrían formar parte de la clase Automata Finito Determinista,
// proveen una forma estandar de interactuar con el automata.

void efectuarTransicion(APila *a) {
    char ent;
    cout << "Efectuando nueva transicion\n";
    cout << "\tIngresar la entrada: ";
    cin >> ent;
    try {
        a->transicion(ent);
    } catch (int exc) {
        if (-8 == exc)
            cout << " \n\tLa función de transicion no está completamente cargada\n";
        else {
            if (-21 == exc)
                cout << "\n\tLa entrada no es válida para el autómata\n";
            else {
                if (-5 == exc)
                    cout << "\n\t No se ha definido dicha transición como exitosa \n";
                else if (-20 == exc)
                    cout << "\n\t Desbordamiento negativo de pila \n";
                else
                    cout << "ERROR: " << exc << "\n";
            }
        }
    }
    MostrarSalida(a);
}

void cargarFTransicion(AFD *f) {
    char t, ent;
    string ESalida, EDestino;

    cout << "Ingresar Transiciones\n";
    do {
        cout << "Ingreando nueva Transicion\n";

        cout << "\tNombre del Estado del cual se parte: ";
        LEERSTRING(ESalida);

        cout << "\tSímbolo de entrada: ";
        cin >> ent;

        cout << "\tNombre del Estado al cual se llega: ";
        LEERSTRING(EDestino)

        try {
            f->setF(ESalida, ent, EDestino);
        } catch (int exc) {
            if (-11 == exc)
                cout << " \n\tNo existe un estado con el nombre " << ESalida << "\n";
            else {
                if (-12 == exc)
                    cout << "\n\t No existe un estado con el nombre " << EDestino << "\n";
                else {
                    if (-13 == exc)
                        cout << "\n\t No existe la entrada " << ent << "\n";
                    else {
                        if (-14 == exc)
                            cout << "\n\t Ya se ha definido la transicion previamente \n";
                        else
                            cout << "\n\t ERROR: " << exc << "\n";
                    }
                }
            }
        }
        cout << "Ingrese 1 para nueva Transicion o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
}

// todas estas funciones podrían formar parte de la clase Automata de Pila,
// proveen una forma estandar de interactuar con el automata de Pila.

void cargarAlfabetoEntradasPila(APila *p) {
    char n;
    int tmp;
    char t;

    cout << "Ingresar el alfabeto de Entrada de Pila" << endl;
    do {
        cout << "Ingresando nueva Entrada\n";
        cout << "\tSímbolo de entrada de pila: ";
        cin >> n;

        try {
            p->setAlfabetoPila(n);
        } catch (int exc) {
            if (-1 == exc)
                cout << "\n\tEl autómata ya tiene su alfabeto de entrada de pila definido\n";
            else {
                if (-2 == exc)
                    cout << "\n\tYa existe la entrada\n";
                else
                    cout << "\n\tERROR: " << exc << "\n";
            }
        }
        cout << "Ingrese 1 para nueva Entrada o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
}

void cargarAlfabetoEntradasCinta(MTuring *p) {
    char n;
    char t;

    cout << "Ingresar el alfabeto de Entrada de Cinta" << endl;
    do {
        cout << "Ingresando nueva Entrada\n";
        cout << "\tSímbolo de entrada de cinta: ";
        cin >> n;
        try {
            p->setAlfabetoCinta(n);
        } catch (int exc) {
            if (-1 == exc)
                cout << "\n\tEl autómata ya tiene su alfabeto de entrada de cinta definido\n";
            else {
                if (-2 == exc)
                    cout << "\n\tYa existe la entrada\n";
                else
                    cout << "\n\tERROR: " << exc << "\n";
            }
        }
        cout << "Ingrese 1 para nueva Entrada o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
}

void cargarFTransicion(APila *p) {
    char t, ent, pil, nuevoTope;
    string ESalida, EDestino;
    bool cons;
    bool op;

    cout << "Ingresar Transiciones\n";
    do {
        cout << "Ingreando nueva Transicion\n";

        cout << "\tNombre del Estado del cual se parte: ";
        LEERSTRING(ESalida);

        cout << "\tSímbolo de entrada: ";
        cin >> ent;

        cout << "\tValor del tope de pila: ";
        cin >> pil;

        cout << "\tNombre del Estado al cual se llega: ";
        LEERSTRING(EDestino)

        cout << "\tNueva situación de la pila\n";
        cout << "\t\tConservar el valor tope anterior? (1 sí / 0 no): ";
        cin >> cons;        // agregar robustez para que no se rompa en caso cualquier entrada;
        cout << "\t\tApilar otro valor más?(1 sí / 0 no): ";
        cin >> op;
        if (1 == op) {
            cout << "\t\tIngrese el valor: ";
            cin >> nuevoTope;
        } else
            nuevoTope = (char) 0;

        try {
            p->setF(ESalida, ent, pil, EDestino, cons, nuevoTope);
        } catch (int exc) {
            switch (exc) {
                case -11:
                    cout << " \n\tNo existe un estado con el nombre " << ESalida << "\n";
                    break;
                case -12:
                    cout << "\n\t No existe un estado con el nombre " << EDestino << "\n";
                    break;
                case -13:
                    cout << "\n\t No existe la entrada " << ent << "\n";
                    break;
                case -14:
                    cout << "\n\t No existe la el tope de pila " << pil << "\n";
                    break;
                case -15:
                    cout << "\n\t No existe la entrada de pila " << nuevoTope << "\n";
                    break;
                case -16:
                    cout << "\n\t Ya se ha definido la transicion previamente \n";
                    break;
                default:
                    cout << "\n\t ERROR: " << exc << "\n";
                    break;
            }
        }

        cout << "Ingrese 1 para nueva Transicion o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
}

void cargarFTransicion(MTuring *p) {
    string ESalida, EDestino;
    char lec, esc, t, dir;

    cout << "Ingresar Transiciones\n";
    do {
        cout << "Ingresar nueva Transicion\n";

        cout << "\tNombre del Estado del cual se parte: ";
        LEERSTRING(ESalida);

        cout << "\tSímbolo que lee de la cinta: ";
        cin >> lec;

        cout << "\tSímbolo que escribe en la cinta: ";
        cin >> esc;

        cout << "\tDirección del cabezal (d, i, p): ";
        cin >> dir;

        cout << "\tNombre del Estado al cual se llega: ";
        LEERSTRING(EDestino);

        try {
            p->setF(ESalida, lec, EDestino, dir, esc);
        } catch (int exc) {
            switch (exc) {
                case -11:
                    cout << " \n\tNo existe un estado con el nombre " << ESalida << "\n";
                    break;
                case -12:
                    cout << "\n\tNo existe un estado con el nombre " << EDestino << "\n";
                    break;
                case -14:
                    cout << "\n\tNo existe un símbolo de cinta " << lec << "\n";
                    break;
                case -15:
                    cout << "\n\tNo existe un símbolo de cinta " << esc << "\n";
                    break;
                case -16:
                    cout << "\n\tYa se ha definido la transicion previamente \n";
                    break;
                case -17:
                    cout << "\n\tNo existe una dirección de cinta " << dir << "\n";
                    break;
                default:
                    cout << "\n\tERROR: " << exc << "\n";
                    break;
            }
        }

        cout << "Ingrese 1 para nueva Transicion o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
}

void finalizarTransicion(APila *p) {
    try {
        p->terminarTransicion();
        MostrarSalida(p);
    } catch (int exc) {
        if (-11 == exc) {
            cout << "\n Hubo desbordamiento negativo de pila\n";
        } else {
            cout << "\n\tERROR: " << exc << "\n";
        }
    }
}

void cargarCinta(MTuring *p) {
    char t;
    string c;
    cout << "Cargando la cinta para la Maquina de Turing\n";

    do {
        cout << "\nIngrese la cadena de simbolos de la cinta: ";
        LEERSTRING(c);
        try {
            p->escribirCinta(c);
        } catch (int exc) {
            if (-2 == exc) {
                cout << "\n\tLa cinta ha sido cargada previamente";
            } else {
                if (-1 == exc) {
                    cout << "\n\tLa cinta no reconoce la cadena " << c;
                } else {
                    cout << "\n\t ERROR: " << exc << "\n";
                }
            }
        }
        cout << "\nIngrese 1 para escribir otra cadena de símbolos en la cinta";
        cout << "\nIngrese 0 para marcar la cinta como cargada\n";
        cin >> t;
        while ('0' != t && '1' != t) {
            cout << "\nEntrada Inválida";
            cout << "\n\tIngrese 1 para escribir otro símbolo en la cinta";
            cout << "\n\tIngrese 0 para marcar la cinta como cargada\n";
            cin >> t;
        }
    } while ('1' == t);
    try {
        p->setCintaLista();
    } catch (int exc) {
        if (-2 == exc) {
            cout << "\n\tLa cinta ha sido cargada previamente";
        } else {
            cout << "\n\t ERROR: " << exc << "\n";
        }
    }
    cout << "La máquina de Turing recibió la siguiente cadena en la cinta\n";
    cout << p->devolverCopiaCinta() << endl;
}

void efectuarTransicion(MTuring *p) {
    cout << "Efectuando nueva transicion\n";
    cout << "La máquina leyó " << p->getLecturaCabezal() << " en la cinta";
    try {
        p->transicion();
    } catch (int exc) {
        if (-1 == exc) {
            cout << "\nLa máquina se encuentra detenida";
        } else {
            if (-2 == exc) {
                cout << "\nLa cinta no está lista para usarse";
            } else {
                if (-3 == exc) {
                    cout << "\nEl cabezal no ha sido colocado todavía";
                } else {
                    if (-5 == exc) {
                        cout << "\nLa transicion no está definida";
                    } else {
                        if (-21 == exc) {
                            cout << "\nEl simbolo de la cinta no es reconocido por la maquina";
                        } else {
                            cout << "\nERROR: " << exc << "\n";
                        }
                    }
                }
            }
        }
    }
//    cout << "\nLa máquina escribió " << p->getLecturaCabezal() << " en la cinta\n";
//    no funciona devuelve el valor nuevo porque el cabezal ya se desplazó en la transicion
    MostrarSalida(p);
}

void cargarCabezal(MTuring *p) {
    unsigned int pos;
    cout << "\nIngrese la posición en donde comienza el cabezal\n";
    cout << "La cinta actualmente se encuentra así:\n";
    cout << p->devolverCopiaCinta();
    cin >> pos;
    try {
        p->ponerCabezal(pos);
    } catch (int exc) {
        if (-1 == exc) {
            cout << "\nNo se puede situar el cabezal hasta que la cinta no esté cargada";
        } else {
            if (-2 == exc) {
                cout << "\nEl cabezal ya ha sido puesto anteriormente";
            } else {
                if (-3 == exc) {
                    cout << "\nLa posición ingresada excede la cinta";
                } else {
                    cout << "\nERROR: " << exc << "\n";
                }
            }
        }
    }
}

//funciones del main
void ProbarAFD();

void ProbarAPila();

void ProbarMT();

int main() {
    ProbarMT();
//    ProbarAFD();
//    ProbarAPila();
    return 0;
}

void ProbarAFD() {
    unsigned int cantEst, cantAlf;
    cout << "Ingresar cantidad de Estados del automata\n";
    cin >> cantEst;
    cout << "Ingresar cantidad de elementos de entrada del automata\n";
    cin >> cantAlf;

    AFD A(cantEst, cantAlf);
    cout << "Cargando todos los estados\n";
    cargarEstados(&A);
    cout << "Cargando todas las entradas\n";
    cargarAlfabetoEntradas(&A);
    cout << "Cargando la función de transicion\n";
    cargarFTransicion(&A);
    cargarEstadoInicial(&A);

    char t;
    do {
        cout << "Efectuando transición\n";
        efectuarTransicion(&A);
        cout << "\nIngrese 1 si desea una nueva transicion\n";
        cin >> t;
    } while ('1' == t);
}

void ProbarAPila() {
    unsigned int cantEst, cantAlf, cantAlfPila;
    char pilaVac, finPila;
    cout << "Ingresar cantidad de Estados del automata\n";
    cin >> cantEst;
    cout << "Ingresar cantidad de elementos de entrada del automata\n";
    cin >> cantAlf;
    cout << "Ingresar cantidad de elementos de la pila del automata\n";
    cin >> cantAlfPila;
    cout << "Ingresar el simbolo que identifica el fin de pila\n";
    cin >> finPila;

    APila P(cantEst, cantAlf, cantAlfPila, finPila);
    cout << "Cargando todos los estados\n";
    cargarEstados(&P);
    cout << "Cargando todas las entradas\n";
    cargarAlfabetoEntradas(&P);
    cout << "Cargando todos los símbolos de pila\n";
    cargarAlfabetoEntradasPila(&P);
    cout << "Cargando la función de transicion\n";
    cargarFTransicion(&P);
    cargarEstadoInicial(&P);

    char t;
    do {
        cout << "Efectuando transición\n";
        efectuarTransicion(&P);
        cout << "\nIngrese 1 si desea una nueva transicion\n";
        cin >> t;
    } while ('1' == t);
    cout << "Ha finalizado las trancisiones del automata de pila\n";
    finalizarTransicion(&P);
    cin >> t;       //system pause multiplataforma
}

void ProbarMT() {
    unsigned int cantEst, cantAlf, cantAlfCinta;
    char blanc;
    cout << "Ingresar cantidad de Estados del automata\n";
    cin >> cantEst;
    cout << "Ingresar cantidad de elementos de entrada del automata\n";
    cin >> cantAlf;
    cout << "Ingresar cantidad de elementos de la cinta del automata\n";
    cin >> cantAlfCinta;
    cout << "Ingresar el símbolo de blanco del automata\n";
    cin >> blanc;


    MTuring M(cantEst, cantAlf, cantAlfCinta, blanc);
    cout << "Cargando todos los estados\n";
    cargarEstados(&M);
    cout << "Cargando todas las entradas\n";
    cargarAlfabetoEntradas(&M);
    cout << "Cargando todos los símbolos de cinta\n";
    cargarAlfabetoEntradasCinta(&M);
    cout << "Cargando la función de transicion\n";
    cargarFTransicion(&M);
    cargarEstadoInicial(&M);
    cargarCinta(&M);
    cargarCabezal(&M);
    char tmp;
    while (!M.isMaquinaParada()) {
        cout << "\nPresione cualquier tecla para hacer una transicion\n";
        cin >> tmp;
        efectuarTransicion(&M);
    }
}