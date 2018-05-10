//
// Created by nelon on 28/4/2018.
//

#include "APila.h"

APila::APila(unsigned int nroEst, unsigned int nroAlfEnt, unsigned int nroAlfPila) : Automata(nroEst, nroAlfEnt) {
    if (0 >= nroAlfPila)
        throw 0;

    this->nroElementosAlfabetoPila = nroAlfPila;               // ahora el símbolo de pila vacia es isEmpty()
    this->cantActualElementosAlfabetoPila = 0;                 // se debería considerar una columna mas para pila vacia
    this->alfabetoPila = new char[this->nroElementosAlfabetoPila];


    //f [ESTADO ACTUAL] [ENTRADA] [TOPE DE PILA] = EstadoYPila*
    f = new ElementosTransicionPila ***[this->nroEstados];
    for (int i = 0; i < this->nroEstados; ++i) {
        f[i] = new ElementosTransicionPila **[this->nroElementosAlfabeto];
        for (int j = 0; j < this->nroElementosAlfabeto; ++j) {
            f[i][j] = new ElementosTransicionPila *[this->nroElementosAlfabetoPila];
            for (int k = 0; k < nroElementosAlfabetoPila; ++k)
                f[i][j][k] = nullptr;
        }
    }
}

void APila::setF(std::string nombreEstadoSalida, char entrada, char valorPila, std::string nombreEstadoDestino,
                 bool conservarTope, char apilamiento) {
    unsigned int ESalidaIndex, entradaIndex, valorPilaIndex, EDestinoIndex, apilamientoIndex;
    try {
        ESalidaIndex = this->getEstadoIndex(nombreEstadoSalida);
    } catch (int exc) {
        if (-1 == exc)
            throw -11;
    }
    try {
        EDestinoIndex = this->getEstadoIndex(nombreEstadoDestino);
    } catch (int exc) {
        if (-1 == exc)
            throw -12;
    }
    try {
        entradaIndex = this->getAlfabetoIndex(entrada);
    } catch (int exc) {
        if (-1 == exc)
            throw -13;
    }
    try {
        valorPilaIndex = this->getAlfabetoPilaIndex(valorPila);
    } catch (int exc) {
        if (-1 == exc)
            throw -14;
    }
    try {
        apilamientoIndex = this->getAlfabetoPilaIndex(apilamiento);
    } catch (int exc) {
        if (-1 == exc)
            throw -15;
    }

    if (nullptr != this->f[ESalidaIndex][entradaIndex][valorPilaIndex])
        throw -16;      // sólo se puede definir una

    // tiene que haber una forma prolija de hacerlo
    this->f[ESalidaIndex][entradaIndex][valorPilaIndex]->estado.nombre = this->estados[EDestinoIndex].nombre;
    this->f[ESalidaIndex][entradaIndex][valorPilaIndex]->estado.situacion = this->estados[EDestinoIndex].situacion;
    this->f[ESalidaIndex][entradaIndex][valorPilaIndex]->conservarTope = conservarTope;
    this->f[ESalidaIndex][entradaIndex][valorPilaIndex]->apilamiento = this->alfabetoPila[apilamientoIndex];
}

/*
     * El siguiente bloque es para cargar el alfabeto de la pila
     * de tamaño nEAlfPila en alfPila[],
     * donde no se admiten entradas repetidas (LAMBDA y '#' cuentan)
*/
void APila::setAlfabetoPila(char c) {
    if (this->cantActualElementosAlfabetoPila >= this->nroElementosAlfabetoPila)
        throw -1;       // ya está lleno

    unsigned int cIndex;

    try {
        cIndex = this->getAlfabetoPilaIndex(c);
    } catch (int exc) {
        this->alfabetoPila[this->cantActualElementosAlfabetoPila] = c;
        this->cantActualElementosAlfabetoPila++;
        return;
    }
    // conceptualmente esta mal: esta tomando como excepcion algo que esta bien
    throw -2;
}

void APila::transicion(char entrada) {
    // se deberia guardar una constante para que una vez efectuada la primer transicion no se pueda
    // modificar la funcion de transicion
    char topeDePila;
    try {
        topeDePila = pila.pop();
    } catch (int exc) {
        if (-11 == exc)
            throw -20;
    }

    ElementosTransicionPila *salidaF;
    try {
        salidaF = this->f[this->getEstadoIndex(estadoActual->nombre)][this->getAlfabetoIndex(
                entrada)][this->getAlfabetoPilaIndex(topeDePila)];
    } catch (int exc) {
        if (-1 == exc)
            throw -21;
    }

    if (true == salidaF->conservarTope)
        pila.push(topeDePila);

    pila.push(salidaF->apilamiento);

    *estadoActual = salidaF->estado;
}

unsigned int APila::getAlfabetoPilaIndex(char s) {
    for (unsigned int i = 0; i < this->nroElementosAlfabetoPila; ++i) {
        if (s == this->alfabetoPila[i])
            return i;
    }
    throw -1;
}

char APila::getTopeDePila() {
    char tmp = this->pila.pop();
    this->pila.push(tmp);
    return tmp;
}

