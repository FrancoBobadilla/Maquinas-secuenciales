#include <iostream>
#include "AFD.h"

using namespace std;

AFD::AFD(int a, int b) {
    if (a <= 0 || b <= 0)throw 1;
    this->nE = a;
    this->nEAlf = b;
    est = new Estado[nE];
    alf = new char[nEAlf];
    f = new Estado *[nE];
    for (int i = 0; i < nE; ++i) f[i] = new Estado[nEAlf];
    //primer paramtro representa filas (estados)
    //segundo paramtetro representa columnas (entradas)

    char nuevEnt;
    int x = 0;
    cout << endl << "Ingresar el alfabeto de entrada" << endl;
    for (int i = 0; i < nEAlf; i++) {
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

    cout << endl << "Ingresar situaciones de los estados" << endl;
    for (int i = 0; i < nE; i++) {
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

    int n = -1;
    for (int i = 0; i < nE; ++i) {
        cout << endl << "Transiciones desde el estado " << this->est[i].nombre << ": " << endl;
        for (int j = 0; j < nEAlf; j++) {
            n = -1;
            while (n < 0 || n >= nE) {
                cout << " con la entrada = " << this->alf[j] << ": ";
                cin >> n;
                if (n < 0 || n >= nE) {
                    cout << endl << "Ingrese un estado válido del autómata" << endl;
                } else {
                    this->f[i][j] = this->est[n];
                }
            }
        }
    }

    n = -1;
    while (n < 0 || n >= nE) {
        cout << endl << "Estado inicial: Estado ";
        cin >> n;
        if (n < 0 || n >= nE) {
            cout << endl << "Ingrese un estado válido del autómata" << endl;
        } else {
            this->estAct = this->est[n];
        }
    }
}

void AFD::transicion(char entrada) { //debe verificarse que entrada pertenezca al alfabteo
    int x = 0;
    for (int i = 0; i < nEAlf; ++i) {
        if (entrada == alf[i]) {
            x = i;
        }
    }
    if (x == nEAlf)throw 1;
    estAct = f[estAct.nombre][x];
    cout << endl << "Estado " << estAct.nombre << " alcanzado" << endl;
    if (estAct.situacion) {
        cout << endl << "SALIDA" << endl;
    }
}