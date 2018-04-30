//
// Created by nelon on 28/4/2018.
//

#include "APila.h"
#include <iostream>

#define LAMBDA '$'

using namespace std;

APila::APila(int nroEst, int nroAlfEnt, int nroAlfPila) {
    if (nroEst <= 0 || nroAlfEnt <= 0 || nroAlfPila <= 0)throw -1;

    this->nE = nroEst;
    this->est = new Estado[this->nE];

    this->nEAlf = nroAlfEnt + 1;                    // OJO ACA
    this->alf = new char[this->nEAlf];              //para aceptar transición lambda
    this->alf[nEAlf - 1] = LAMBDA;

    this->nEAlfPila = nroAlfPila + 2;               // OJO ACA
    this->alfPila = new char[this->nEAlfPila];      //para aceptar simbolo de pila vacía
    this->alfPila[this->nEAlfPila - 2] = '#';
    this->alfPila[this->nEAlfPila - 1] = LAMBDA;


    //f [ESTADO ACTUAL] [ENTRADA] [TOPE DE PILA] = EstadoYPila*
    f = new EstadoYPila ***[this->nE];

    for (int i = 0; i < this->nE; ++i) {
        f[i] = new EstadoYPila **[this->nEAlf];
        for (int j = 0; j < this->nEAlf; ++j) {
            f[i][j] = new EstadoYPila *[this->nEAlfPila];
            for (int k = 0; k < nEAlfPila; ++k)
                f[i][j][k] = nullptr;
        }
    }

    /*
     * El siguiente bloque es para cargar el alfabeto de entrada de tamaño nEAlf en alf[],
     * en el que '/' no es una entrada admitida
     * y tampoco se admiten entradas repetidas
     *
     * Se deberia exportar método en la clase abstracta
     */
    char nuevEnt;
    //int x = 0;
    cout << endl << "Ingresar el alfabeto de entrada" << endl;
    for (int i = 0; i < nEAlf - 1; i++) {
        cout << " Entrada " << i << " ('/' no admitido): ";
        cin >> nuevEnt;
        if (nuevEnt == '/') {
            cout << endl << "Entrada inválida!" << endl << "Ingresar nuevamente la entrada ('/' no admitido)" << endl
                 << endl;
            i--;
        } else {
            if (getEntradaIndex(nuevEnt) != -1) {
                cout << endl << "Entrada repetida!" << endl << "Ingresar nuevamente la entrada ('/' no admitido)"
                     << endl
                     << endl;
                i--;
            } else {
                this->alf[i] = nuevEnt;
            }
        }
    }

    /*
     * El siguiente bloque es para definir la situacion de los estados est[] en est[].situacion,
     * que solo pueden tomar los valores '0' o '1'
     * y nE es la cantidad de estados
     *
     * Se deberia exportar método en la clase abstracta
     */
    cout << endl << "Ingresar situaciones de los estados" << endl;
    for (int i = 0; i < this->nE; i++) {
        this->est[i].nombre = i;  //podria sacarse el atributo nombre de los estados
        char nuevSit = 'a';
        while (nuevSit != '0' && nuevSit != '1') {
            cout << " El estado " << i << " ¿es de salida? (1/0): ";
            cin >> nuevSit;
            if (nuevSit == '0') {
                est[i].situacion = false;

            } else {
                if (nuevSit == '1') {
                    est[i].situacion = true;
                } else {
                    cout << "Ingrese un caracter valido" << endl;
                }
            }
        }
    }

    /*
     * El siguiente bloque es para cargar el alfabeto de la pila
     * de tamaño nEAlfPila en alfPila[],
     * donde no se admiten entradas repetidas (LAMBDA y '#' cuentan)
     */
    //x = 0;
    cout << endl << "Ingresar el alfabeto de la pila" << endl << "Recuerde que '#' es símbolo de pila vacía y '"
         << LAMBDA << "' es el simbolo de pila vacía" << endl;
    for (int l = 0; l < this->nEAlfPila - 2; ++l) {
        cout << " Símbolo de pila número " << l << ": ";
        cin >> nuevEnt;
        if (getEntradaPilaIndex(nuevEnt) != -1) {
            cout << endl << "Entrada repetida!" << "Ingresar nuevamente la entrada" << endl << endl;
            l--;
        } else {
            this->alfPila[l] = nuevEnt;
        }
    }

    /*
     * Este bloque es para definir las transiciones exitosas
     */
    cout << endl << endl << "Definición de transiciones exitosas" << endl;
    bool t, u;
    int estTmp, cantTran, estDestino;
    char entTmp, topTmp, charPtrTmp, newChar = 'a';
    do {
        cout << endl << "Ingresar nueva transición? (0/1): ";
        cin >> t;

        if (1 == t) {

            //Estado del cual se parte
            cout << "Ingrese el Estado del cual se origina la transición: ";
            cin >> estTmp;
            while (estTmp >= this->nE || estTmp < 0) {
                cout << endl << "Ingrese un estado válido del autómata" << endl;
                cin >> estTmp;
            }

            //Entrada
            cout << "Ingrese el símbolo de entrada: ";
            cin >> entTmp;
            int entTmpIndex = getEntradaIndex(entTmp);
            while (-1 == entTmpIndex) {
                cout << endl << "Ingrese una entrada válida del autómata" << endl;
                cin >> entTmp;
                entTmpIndex = getEntradaIndex(entTmp);
            }

            //Tope de pila
            cout << "Ingrese el valor del tope de la pila: ";
            cin >> topTmp;
            int topTmpIndex = getEntradaPilaIndex(topTmp);
            while (-1 == topTmpIndex) {
                cout << endl << "Ingrese una entrada válida del lenguaje de pila del autómata" << endl;
                cin >> topTmp;
                topTmpIndex = getEntradaPilaIndex(topTmp);
            }

            if (nullptr == f[estTmp][entTmpIndex][topTmpIndex]) {

                //Cantidad de transiciones
                cout << "Ingrese la cantidad de transiciones: ";
                cin >> cantTran;
                while (cantTran <= 0) {
                    cout << endl << "Debe ingresar una cantidad de transiciones válida" << endl;
                    cin >> cantTran;
                }

                f[estTmp][entTmpIndex][topTmpIndex] = new EstadoYPila[cantTran + 1];
                f[estTmp][entTmpIndex][topTmpIndex][cantTran].f_estado.nombre = -1;
                cout << "Entonces: estando en el Estado " << estTmp << " con la entrada " << entTmp
                     << " y en la pila hay " << topTmp << endl;

                for (int i = 0; i < cantTran; ++i) {

                    cout << "Posibilidad " << i + 1 << endl;

                    //Estado al cual se llega
                    cout << "\tVa al estado: ";
                    cin >> estDestino;
                    while (estDestino >= this->nE || estDestino < 0) {
                        cout << "\tIngrese un estado válido del autómata: ";
                        cin >> estDestino;
                    }

                    //Situacion del tope de pila con el cual se parte
                    while (newChar != '0' && newChar != '1') {
                        cout << "¿Se conservará el tope de pila durante la transicion? (1/0): ";
                        cin >> newChar;
                        if (newChar == '0') {
                            u = false;
                        } else {
                            if (newChar == '1') {
                                u = true;
                            } else {
                                cout << "Ingrese un caracter valido" << endl;
                            }
                        }
                    }

                    //Elemento que se apilará
                    cout << "\tIngrese elemento a apilar ('" << LAMBDA << "' para no apilar nada): ";
                    cin >> topTmp;
                    while ((getEntradaPilaIndex(topTmp) == -1) || topTmp == '#') {
                        cout << "\tIngrese un elemento válido a apilar ('" << LAMBDA << "' para no apilar nada): ";
                        cin >> topTmp;
                    }
                    if (LAMBDA == topTmp)
                        charPtrTmp = (char) 0;
                    else
                        charPtrTmp = topTmp;
                    f[estTmp][entTmpIndex][topTmpIndex][i] = {this->est[estDestino], charPtrTmp, u};
                }
            } else {
                cout << endl << "Ya se ha definido esa transición" << endl;
                //EstadoYPila *tmp = f[estTmp][entTmpIndex][topTmpIndex];
                // podria listar las transiciones
            }
        }

    } while (1 == t);

    /*
     * Este bloque es para definir el estado inicial del automata,
     * que pertenece a est[]
     *
     * Se deberia exportar método en la clase abstracta
     */
    int n = -1;
    while (n < 0 || n >= nE) {
        cout << endl << "Estado inicial: Estado ";
        cin >>
            n;
        if (n < 0 || n >= nE) {
            cout << endl << "Ingrese un estado válido del autómata" <<
                 endl;
        } else {
            this->
                    estAct = this->est[n];
        }
    }
}

bool APila::transicion(char nuevEnt) {
    int i=0;
    char topePila = pila.pop();
    int indexAlfEnt = getEntradaIndex(nuevEnt);
    if (indexAlfEnt == -1) throw -1;
    EstadoYPila *resTransicion = f[estAct.nombre][indexAlfEnt][topePila];
    if (resTransicion == nullptr) {
        pila.push(topePila);
        return false;
    }
    while (resTransicion[i].f_estado.nombre != -1) {
        //hacer bien
        if (resTransicion[i].f_tope) pila.push(topePila);
        pila.push(resTransicion[i].f_pila);
        estAct = resTransicion[i].f_estado;
        cout << endl << "Estado " << estAct.nombre << " alcanzado" << endl;
        if (estAct.situacion) cout << endl << "SALIDA" << endl;
        transicion('$');
    }
    return true;
}

int APila::getEntradaIndex(char s) {
    for (int i = 0; i < this->nEAlf; ++i) {
        if (this->alf[i] == s)
            return i;
    }
    return -1;
}

int APila::getEntradaPilaIndex(char s) {
    for (int i = 0; i < this->nEAlfPila; ++i) {
        if (this->alfPila[i] == s)
            return i;
    }
    return -1;
}