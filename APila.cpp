//
// Created by nelon on 28/4/2018.
//

#include "APila.h"
#include <iostream>

#define NMA 2
// Numero Máximo de Apilaciones
// 2 porque solo se podrian apilar dos elementos: el recien intervenido y el nuev

#define LAMBDA '$'

using namespace std;

APila::APila(int nroEst, int nroAlfEnt, int nroAlfPila) {
    if (nroEst <= 0 || nroAlfEnt <= 0 || nroAlfPila <= 0)throw 1;

    cout << endl << "Note que lambda se representa por: " << LAMBDA << endl;

    this->nE = nroEst;
    this->est = new Estado[this->nE];

    this->nEAlf = nroAlfEnt + 1;                    // OJO ACA
    this->alf = new char[this->nEAlf];              //para aceptar transición lambda
    this->alf[nEAlf - 1] = LAMBDA;

    this->nEAlfPila = nroAlfPila + 2;               // OJO ACA
    this->alfPila = new char[this->nEAlfPila];      //para aceptar simbolo de pila vacía
    this->alfPila[this->nEAlfPila - 2] = '#';
    this->alfPila[this->nEAlfPila - 1] = LAMBDA;


    /*  Intención de cubo de función
     *   f[a][b][c]
     *
     *   - Las filas (alto) representan distintos estados (Posición más significativa: a)
     *   - Las columnas (ancho) representan distintas entradas (Posición :b)
     *   - Las [inserte nombre] (profundo) representan distintos estados de la Pila (posición menos significativa: c)
     * */

    f = new EstadoYPila ***[this->nE];

    for (int i = 0; i < this->nE; ++i) {
        f[i] = new EstadoYPila **[this->nEAlf];
        for (int j = 0; j < this->nEAlf; ++j) {
            f[i][j] = new EstadoYPila *[this->nEAlfPila];
            for (int k = 0; k < nEAlfPila; ++k)
                f[i][j][k] = nullptr;
        }
    }

    char nuevEnt;
    int x = 0;
    cout << endl << "Ingresar el alfabeto de entrada" << endl;
    for (int i = 0; i < nEAlf - 1; i++) {                    // OJO ACA
        cout << " Entrada " << i << " ('/' no admitido): ";
        cin >> nuevEnt;
        if (nuevEnt == '/') {
            cout << endl << "Entrada inválida!" << endl << "Ingresar nuevamente la entrada" << endl << endl;
            i--;
        } else {
            for (int j = 0; j < i; ++j) {
                if (alf[j] == nuevEnt) {
                    cout << endl << "Entrada repetida!" << "Ingresar nuevamente la entrada" << endl << endl;
                    i--;
                    j = i + 1;
                }
                x = j + 1;
            }
            if (x == i) {
                this->alf[i] = nuevEnt;
            }
        }
    }
    // Se deberia exportar método en la clase abstracta

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
    // Se deberia exportar método en la clase abstracta

    //char nuevEnt;
    x = 0;
    cout << endl << "Ingresar el alfabeto de la pila" << endl;
    cout << "Recuerde que # es símbolo de pila vacía" << endl;
    for (int l = 0; l < this->nEAlfPila - 2; ++l) {         //OJO ACA
        cout << " Símbolo de pila número " << l << " ('/' no admitido): ";
        cin >> nuevEnt;
        if (nuevEnt == '#') {
            cout << endl << "El símbolo # se reserva para pila vacía" << endl;
            cout << "Entrada inválida!" << endl << "Ingresar nuevamente la entrada" << endl << endl;
            l--;
        } else {
            if (nuevEnt == '/') {
                cout << endl << "Entrada inválida!" << endl << "Ingresar nuevamente la entrada" << endl << endl;
                l--;
            } else {
                for (int m = 0; m < l; ++m) {
                    if (this->alfPila[m] == nuevEnt) {
                        cout << endl << "Entrada repetida!" << "Ingresar nuevamente la entrada" << endl << endl;
                        l--;
                        m = l + 1;
                    }
                    x = m + 1;
                }
                if (x == l)
                    this->alfPila[l] = nuevEnt;
            }
        }
    }

    cout << endl << endl << "Definición de transiciones exitosas" << endl;
    bool t;
    int estTmp, cantTran, estDestino;
    char entTmp, topTmp, *charPtrTmp;
    charPtrTmp = new char[NMA]; //2
    do {
        cout << endl << "Ingresar nueva transición? (0/1): ";
        cin >> t;

        if (1 == t) {
            cout << "Ingrese el Estado del cual se origina la transición: ";
            cin >> estTmp;
            while (estTmp >= this->nE || estTmp < 0) {
                cout << endl << "Ingrese un estado válido del autómata" << endl;
                cin >> estTmp;
            }

            cout << "Ingrese el símbolo de entrada: ";
            cin >> entTmp;
            while (!existeEntrada(entTmp)) {
                cout << endl << "Ingrese una entrada válida del autómata" << endl;
                cin >> entTmp;
            }

            cout << "Ingrese el valor del tope de la pila: ";
            cin >> topTmp;
            while (!existeEntradaPila(topTmp)) {
                cout << endl << "Ingrese una entrada válida del lenguaje de pila del autómata" << endl;
                cin >> topTmp;
            }

            int entTmpIndex = getEntradaIndex(entTmp);
            int topTmpIndex = getEntradaPilaIndex(topTmp);

            if (nullptr == f[estTmp][entTmpIndex][topTmpIndex]) {
                cout << "Ingrese la cantidad de transiciones: ";
                cin >> cantTran;
                while (cantTran <= 0) {
                    cout << endl << "Debe ingresar una cantidad de transiciones válida" << endl;
                    cin >> cantTran;
                }

                f[estTmp][entTmpIndex][topTmpIndex] = new EstadoYPila[cantTran];

                cout << "Entonces: estando en el Estado " << estTmp << " con la entrada " << entTmp
                     << " y en la pila hay " << topTmp << endl;
                for (int i = 0; i < cantTran; ++i) {
                    cout << "Posibilidad " << i + 1 << endl;
                    cout << "\tVa al estado: ";
                    cin >> estDestino;
                    while (estDestino >= this->nE || estDestino < 0) {
                        cout << "\tIngrese un estado válido del autómata: ";
                        cin >> estDestino;
                    }
                    cout << "\tIngrese el primer elemento a apilar ('/', si no): ";
                    cin >> topTmp;
                    while ('/' != topTmp && !existeEntradaPila(topTmp)) {
                        cout << "\tIngrese un elemento válido a apilar ('/', si no): ";
                        cin >> topTmp;
                    }
                    if ('/' == topTmp) {
                        f[estTmp][entTmpIndex][topTmpIndex][i] = {this->est[estDestino], nullptr};
                    } else {
                        charPtrTmp[0] = topTmp;
                        cout << "\tIngrese el segundo elemento a apilar ('/', si no hay): ";
                        cin >> topTmp;
                        while ('/' != topTmp && !existeEntradaPila(topTmp)) {
                            cout << "\tIngrese un elemento válido a apilar ('/', si no): ";
                            cin >> topTmp;
                        }
                        if ('/' == topTmp)
                            charPtrTmp[1] = (char) 0;
                        else
                            charPtrTmp[1] = topTmp;

                        f[estTmp][entTmpIndex][topTmpIndex][i] = {this->est[estDestino], charPtrTmp};
                    }
                }
            } else {
                cout << endl << "Ya se ha definido esa transición" << endl;
                //EstadoYPila *tmp = f[estTmp][entTmpIndex][topTmpIndex];
                // podria listar las transiciones
            }
        }

    } while (1 == t);

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

bool APila::existeEntrada(char t) {
    for (int i = 0; i < this->nEAlf; ++i)
        if (this->alf[i] == t)
            return true;
    return false;
}

bool APila::existeEntradaPila(char t) {
    for (int i = 0; i < this->nEAlfPila; ++i)
        if (this->alfPila[i] == t)
            return true;
    return false;
}

int APila::getEntradaIndex(char s) {
    for (int i = 0; i < this->nEAlf; ++i) {
        if (this->alf[i] == s)
            return i;
    }
    return -1;      //nunca deberia llegar
}

int APila::getEntradaPilaIndex(char s) {
    for (int i = 0; i < this->nEAlfPila; ++i) {
        if (this->alfPila[i] == s)
            return i;
    }
    return -1;      //nunca deberia llegar
}