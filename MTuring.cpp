//
// Created by FrancoBobadilla on 31/5/2018.
//

#include "MTuring.h"

MTuring::MTuring(unsigned int cantidadEstados, unsigned int tamanoAlfabeto, unsigned int tamanoAlfabetoCinta,
                 char blanco)
        : Automata(cantidadEstados, tamanoAlfabeto) {
    if (0 >= tamanoAlfabetoCinta)
        throw 0;

    this->nroElementosAlfabetoCinta = tamanoAlfabetoCinta + 1;  //para el blanco
    this->cantActualElementosAlfabetoCinta = 0;
    this->alfabetoCinta = new char[this->nroElementosAlfabetoCinta];

    // f [ESTADO ACTUAL] [ENTRADA DESDE CINTA]
    this->f = new SalidaFuncMaqTuring **[this->nroEstados];
    for (int i = 0; i < this->nroEstados; ++i) {
        this->f[i] = new SalidaFuncMaqTuring *[this->nroElementosAlfabetoCinta];       // mas el blanco
        for (int j = 0; j < this->nroElementosAlfabetoCinta; ++j) {
            this->f[i][j] = nullptr;
        }
    }

    this->cinta = new Cinta<char>(blanco);
    // el blanco cuenta como simbolo del alfabeto de cinta?
    this->setAlfabetoCinta(blanco);

    this->isCintaLista = false;
    this->maquinaParada = false;
    this->isCabezalListo = false;
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
    this->f[ESalidaIndex][entradaCintaIndex] = new SalidaFuncMaqTuring;
    this->f[ESalidaIndex][entradaCintaIndex]->estado.nombre = this->estados[EDestinoIndex].nombre;
    this->f[ESalidaIndex][entradaCintaIndex]->estado.situacion = this->estados[EDestinoIndex].situacion;
    this->f[ESalidaIndex][entradaCintaIndex]->direccion = direccion;
    this->f[ESalidaIndex][entradaCintaIndex]->escritura = this->alfabetoCinta[escrituraIndex];
}

void MTuring::setAlfabetoCinta(char c) {
    if (this->cantActualElementosAlfabetoCinta >= this->nroElementosAlfabetoCinta)
        throw -1;          //ya esta lleno

    try {
        this->getAlfabetoCintaIndex(c);
    } catch (int exc) {
        this->alfabetoCinta[this->cantActualElementosAlfabetoCinta] = c;
        this->cantActualElementosAlfabetoCinta++;
        return;
    }
    // conceptualmente esta mal: esta tomando como excepcion algo que esta bien
    throw -2;   // ya existe en el alfabeto
    // dejame esto para más adelante Bob
}

void MTuring::escribirSimboloEnCinta(char c) {
    if (this->isCintaLista)
        throw -2;   //Cinta ya estaba lista
    try {
        this->getAlfabetoIndex(c);      //al comienzo  sólo debe haber simbolos del alf de entrada, no del de cinta
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
    this->cinta->desplazarDerecha(); // crea un blanco al final de la cinta
    do {
        this->cinta->desplazarIzquierda();
    } while (this->cinta->leer() != this->cinta->getBlanco());
    // es un esfuerzo inutil volver al comienzo si luego el usuario elige donde dejar el cabezal
    this->isCintaLista = true;
}

// no me gusta que tenga parámetros distintos
void MTuring::transicion() {
    try {
        this->transicion(this->cinta->leer());
    } catch (int exc) {
        throw exc;
    }
}

void MTuring::transicion(char lectura) {
    if (this->maquinaParada)
        throw -1;
    if (!this->isCintaLista)
        throw -2;       // no se puede hacer tranciciones hasta que la cinta no este lista
    if (!this->isCabezalListo)
        throw -3;
    SalidaFuncMaqTuring *salidaF;
    try {
        salidaF = this->f[this->getEstadoIndex(this->estadoActual->nombre)][this->getAlfabetoCintaIndex(lectura)];
    } catch (int exc) {
        if (-1 == exc)
            throw -21;
    }

    if (nullptr == salidaF)
        throw -5;   // transicion no definida

    this->estadoActual = &salidaF->estado;
    if (this->estadoActual->situacion)
        this->maquinaParada = true;
    this->cinta->escribir(salidaF->escritura);
    if ('d' == salidaF->direccion) {
        this->cinta->desplazarDerecha();
    } else {
        if ('i' == salidaF->direccion)
            this->cinta->desplazarIzquierda();
        else {
            this->maquinaParada = true;
        }
    }
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

bool MTuring::isMaquinaParada() {
    return this->maquinaParada;
}

void MTuring::ponerCabezal(unsigned int pos) {
    if (!this->isCintaLista)
        throw -1;   // solo se puede situar el cabezal cuando la cinta está cargada
    if (this->isCabezalListo)
        throw -2;   // solo se puede poner el cabezal una vez
    if (this->cinta->getTamano() <= pos)
        throw -3;   // la cinta es mas chica

    unsigned int i = pos;
    while (0 != i) {
        this->cinta->desplazarDerecha();
        i--;
    }
    this->isCabezalListo = true;
}