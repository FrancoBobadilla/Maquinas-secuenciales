//
// Created by nelon on 28/4/2018.
//

#include "APila.h"

APila::APila(unsigned int nroEst, unsigned int nroAlfEnt, unsigned int nroAlfPila, char finDePila) : Automata(
        nroEst, nroAlfEnt) {
    if (0 >= nroAlfPila)
        throw 0;

    /*
     * Se asume que el automata de pila es indeterminado solo por no definir todas las posibles transiciones
     *
     * Dicho esto
     *      la pila comienza con el simbolo de fin de pila cargado
     *      el usuario no puede ingresar una entrada lambda
     */

    this->nroElementosAlfabetoPila = nroAlfPila + 1;
    this->cantActualElementosAlfabetoPila = 0;
    this->alfabetoPila = new char[this->nroElementosAlfabetoPila];

    this->finDePila = finDePila;
    this->setAlfabetoPila(this->finDePila);

    // este bloque no requiere try and catch
    // porque el tamanio de alfabeto de pila siempre es mayor a cero
    // porque no hay elementos con los que el fin de pila pueda estar repetido

    this->pila = new Stack<char>;
    this->pila->push(this->finDePila);

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
    char apilamientoTMP;
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
    if ((char) 0 != apilamiento) {
        try {
            apilamientoIndex = this->getAlfabetoPilaIndex(apilamiento);
        } catch (int exc) {
            if (-1 == exc)
                throw -15;
        }
        apilamientoTMP = this->alfabetoPila[apilamientoIndex];
    } else {        // si el usuario no quiene ingresar un nuevo simbolo a la pila
        apilamientoTMP = apilamiento;
    }

    if (nullptr != this->f[ESalidaIndex][entradaIndex][valorPilaIndex])
        throw -16;      // sólo se puede definir una

    // tiene que haber una forma prolija de hacerlo
    this->f[ESalidaIndex][entradaIndex][valorPilaIndex] = new ElementosTransicionPila;
    this->f[ESalidaIndex][entradaIndex][valorPilaIndex]->estado.nombre = this->estados[EDestinoIndex].nombre;
    this->f[ESalidaIndex][entradaIndex][valorPilaIndex]->estado.situacion = this->estados[EDestinoIndex].situacion;
    this->f[ESalidaIndex][entradaIndex][valorPilaIndex]->conservarTope = conservarTope;
    this->f[ESalidaIndex][entradaIndex][valorPilaIndex]->apilamiento = apilamientoTMP;
}

/*
     * El siguiente bloque es para cargar el alfabeto de la pila
     * de tamaño nEAlfPila en alfPila[],
     * donde no se admiten entradas repetidas (LAMBDA y '#' cuentan)
*/
void APila::setAlfabetoPila(char c) {
    if (this->cantActualElementosAlfabetoPila >= this->nroElementosAlfabetoPila)
        throw -1;       // ya está lleno

    try {
        this->getAlfabetoPilaIndex(c);
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
        topeDePila = this->pila->pop();
        this->pila->push(topeDePila);
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

    if (nullptr == salidaF) {
        throw -5;   // transicion no definida
        //definir automata como no usable
    }

    this->pila->pop();
    /*
     * El tope de pila es necesario para determinar el estado resultante de la transicion
     * sin embargo en caso de que la entrada sea erronea la funcion retorna y se debe conservar el tope de
     * la pila como estaba
     * el mismo caso para las transiciones no definidas
     * */

    if (salidaF->conservarTope)
        pila->push(topeDePila);

    if ((char) 0 != salidaF->apilamiento)
        pila->push(salidaF->apilamiento);

    estadoActual = &salidaF->estado;
}

unsigned int APila::getAlfabetoPilaIndex(const char &s) {
    for (unsigned int i = 0; i < this->cantActualElementosAlfabetoPila; ++i) {
        if (s == this->alfabetoPila[i])
            return i;
    }
    throw -1;
}

void APila::terminarTransicion() {
    // set as unable to work in the future...
    try {
        char tmp = this->pila->pop();
        this->pila->push(tmp);
        if (this->finDePila == tmp) {
            estadoActual = this->buscarEstadoFinal();
        }
    } catch (int exc){
        throw exc;
    }
}

Estado *APila::buscarEstadoFinal() {
    for (int i = 0; i < this->cantActualEstados; ++i) {
        if (this->estados[i].situacion)
            return &this->estados[i];
    }
    // exception por si no hay estado final?
}


char APila::getTopeDePila() {
    char tmp = this->pila->pop();
    this->pila->push(tmp);
    return tmp;
}