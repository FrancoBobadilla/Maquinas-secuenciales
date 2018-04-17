#include <iostream>
#include "AFD.h"

using namespace std;

AFD::AFD(int a, int b) {
    this->nE = a;
    this->nEAlf = b;

    est = new Estado[nE];
    alf = new char[nEAlf];
    f = new Estado *[nE];

    for (int i = 0; i < nE; ++i) {
        f[i] = new Estado[nEAlf];
    }

    //primer paramtro representa filas (estados)
    //segundo paramtetro representa columnas (entradas)

    cout << endl << "Ingresar el alfabeto de entrada" << endl;

    for (int i = 0; i < nEAlf; i++) {
        cout << " Entrada " << i << ": ";
        cin >> this->alf[i];
    }

    cout << endl << "Ingresar situaciones de los estados" << endl;
    for (int i = 0; i < nE; i++) {
        this->est[i].nombre = i;  //podria sacarse el atributo nombre de los estados
        cout << " El estado " << i << " ¿es de salida? (1/0): ";
        cin >> this->est[i].situacion;    //habria que preveer si el usuario no ingresa 1 o 0
    }

    int n;
    for (int i = 0; i < nE; ++i) {
        cout << endl << "Transiciones desde " << this->est[i].nombre << ": " << endl;
        for (int j = 0; j < nEAlf; j++) {
            cout << " con la entrada = " << this->alf[j] << ": ";
            cin >> n;
            this->f[i][j] = this->est[n];   //falla porque no esta implementado el = para Estados
        }
    }

    cout << endl << "Estado inicial: ";
    cin >> n;
    this->estAct = this->est[n];
}

int AFD::transicion(char entrada) {
    int x;
    for (int i = 0; i < nEAlf; ++i) {
        if (entrada == alf[i])
            x = i;
    }
    int y = estAct.nombre;
    estAct = f[y][x];
    if (estAct.situacion)
        cout << endl << "Salida desde estado E" << estAct.nombre << endl;
    return estAct.nombre;
}