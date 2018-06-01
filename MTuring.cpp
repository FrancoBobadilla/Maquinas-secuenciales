//
// Created by FrancoBobadilla on 31/5/2018.
//

#include "MTuring.h"

MTuring::MTuring(unsigned int cantidadEstados, unsigned int tamanoAlfabeto, unsigned int tamanoAlfabetoCinta, char blanco)
        : Automata(cantidadEstados, tamanoAlfabeto) {
    if (0 >= tamanoAlfabetoCinta)
        throw 0;

    this->nroElementosAlfabetoCinta = tamanoAlfabetoCinta;
    this->cantActualElementosAlfabetoCinta = 0;
    this->alfabetoCinta = new char[this->nroElementosAlfabetoCinta];

    // f [ESTADO ACTUAL] [ENTRADA DESDE CINTA]
    this->f = new SalidaFuncMaqTuring **[this->nroEstados];
    for (int i = 0; i < this->nroEstados; ++i) {
        this->f[i] = new SalidaFuncMaqTuring *[this->nroElementosAlfabetoCinta];
        for (int j = 0; j < this->nroElementosAlfabetoCinta; ++j) {
            this->f[i][j] = nullptr;
        }
    }

    this->cinta = new Cinta<char>(blanco);
    /*
     * Se debe modificar el prototipo de constructor para admitir que el usuario elija el blanco
     * La clase Cinta debe implementar el metodo getBlanco() para la expresión final
     * Se debería replantear la misma situación para el automata de Pila con el fin de pila
     * */

    this->isCintaLista = false;
}

void MTuring::setF(std::string nombreEstadoSalida, char entradaCinta, std::string nombreEstadoDestino,
                   char direccion, char escritura) {
    unsigned int ESalidaIndex, entradaCintaIndex, EDestinoIndex, escrituraIndex;
    try {
        ESalidaIndex = this->getEstadoIndex(nombreEstadoSalida);
    } catch (int exc) {
        if (-1 == exc)
            throw -11;
    }
    try {
        EDestinoIndex = this->getEstadoIndex(nombreEstadoDestino);
    } catch (int exc) {
        if (-1 == exc) {
            throw -12;
        }
    }
    try {
        entradaCintaIndex = getAlfabetoCintaIndex(entradaCinta);
    } catch (int exc) {
        if (-1 == exc)
            throw -14;
    }
    try {
        escrituraIndex = getAlfabetoCintaIndex(escritura);
    } catch (int exc) {
        if (-1 == exc)
            throw -15;
    }

    //(p: mantener, i:izquierda, d:derecha)
    // direccion no valida
    // se deberia castear mejor con toUpper etc. o solicitar al usuario que increse sus direcciones
    if ('p' != direccion && 'i' != direccion && 'd' != direccion)
        throw -17;

    if (nullptr != f[ESalidaIndex][entradaCintaIndex])
        throw -16;

    // tiene que haber una forma prolija de hacerlo
    this->f[ESalidaIndex][entradaCintaIndex]->estado.nombre = this->estados[EDestinoIndex].nombre;
    this->f[ESalidaIndex][entradaCintaIndex]->estado.situacion = this->estados[EDestinoIndex].situacion;
    this->f[ESalidaIndex][entradaCintaIndex]->direccion = direccion;
    this->f[ESalidaIndex][entradaCintaIndex]->escritura = this->alfabetoCinta[escrituraIndex];
}

void MTuring::setAlfabetoCinta(char c) {
    if (this->cantActualElementosAlfabetoCinta >= this->nroElementosAlfabetoCinta)
        throw -1;          //ya esta lleno

    unsigned int cIndex;

    try {
        cIndex = this->getAlfabetoCintaIndex(c);
    } catch (int exc) {
        this->alfabetoCinta[this->cantActualElementosAlfabetoCinta] = c;
        this->cantActualElementosAlfabetoCinta++;
        return;
    }
    // conceptualmente esta mal: esta tomando como excepcion algo que esta bien
    throw -2;

/*
    try {
        cIndex = this->getAlfabetoCintaIndex(c);
    } catch (int exc) {
        if(-1 != exc)
            throw  -2;  // ya está el simbolo
        // no se si funciona
    }

    this->alfabetoCinta[this->cantActualElementosAlfabetoCinta] = c;
    this->cantActualElementosAlfabetoCinta++;
    // puede fallar dijo Tusam*/

/*
    Opcion 2

    try{
        cIndex = this.getAlfabetoCintaIndex(c);
    } catch (int exc){
    }

    if(this->alfabetoCinta[cIndex] == c)
        throw -2;
    else{
        this->alfabetoCinta[this->cantActualElementosAlfabetoCinta] = c;
        this->cantActualElementosAlfabetoCinta++;
    }
*/
// dejame esto para más adelante Bob
}

void MTuring::setSimboloEnCinta(char c) {
    if (this->isCintaLista)
        throw -2;   //Cinta ya estaba lista
    try {
        this->getAlfabetoCintaIndex(c);
    } catch (int exc) {
        if (-1 == exc)
            throw -1;   //No pertenece al alfabeto de entrada
    }
    this->cinta->desplazarDerecha();
    this->cinta->escribir(c);
    //podría considerarse el hecho de llenar la cinta con los indices del arreglo de entradas, para no controlar tantas veces
}

void MTuring::setCintaLista() {
    if (this->isCintaLista)
        throw -2;   //Cinta ya estaba lista
    this->cinta->desplazarDerecha();
    // Cinta debería ser iterable
    do {
        this->cinta->desplazarIzquierda();
    } while (this->cinta->leer() != this->cinta->getBlanco());
    // muy acoplado
    //asume que se quiere dejar el cabezal sobre el primer blanco antes de la cadena de la cinta
    this->isCintaLista = true;
}

// no me gusta que se llame de otra forma
// conceptualmente un usuario solicita una transicion a cualquier máquina secuencial
void MTuring::lecturaTransicion() {
    try {
        this->transicion(this->cinta->leer());
    } catch (int exc) {
        throw exc;
    }
}

void MTuring::transicion(char lectura) {
    if (!this->isCintaLista)
        throw -2;       // no se puede hacer tranciciones hasta que la cinta no este lista
    SalidaFuncMaqTuring *salidaF;
    try {
        salidaF = this->f[this->getEstadoIndex(this->estadoActual->nombre)][this->getAlfabetoCintaIndex(lectura)]
    } catch (int exc) {
        if (-1 == exc)
            throw -21;
    }
    this->estadoActual = &salidaF->estado;
    this->cinta->escribir(salidaF->escritura);
    if ('d' == salidaF->direccion)
        this->cinta->desplazarDerecha();
    if ('i' == salidaF->direccion)
        this->cinta->desplazarIzquierda();
}

unsigned int MTuring::getAlfabetoCintaIndex(const char &s) {
    for (unsigned int i = 0; i < this->cantActualElementosAlfabetoCinta; ++i) {
        if (s == this->alfabetoCinta[i])
            return i;
    }
    throw -1;
}

char MTuring::getLecturaCabezal() {
    return this->cinta->leer();
}