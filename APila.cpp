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
    this->tieneSimbolosPilaDefinidos = false;

    this->finDePila = finDePila;
    this->setAlfabetoPila(this->finDePila);

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

    if (tieneFDeterminada)
        throw -23;              // la funcion de transicion ya fue usada una vez

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

    /*
     * Este bloque verifica que no haya dos fines de pila al mismo tiempo
     * */
    if (apilamiento == this->finDePila) {
        if (conservarTope)
            throw -53;
        else {
            if (valorPila != this->finDePila)
                throw -53;
        }
    }

    /*
     * El siguiente bloque de instrucciones verifica
     * Que siempre que se quite el fin de pila se alcance un estado de salida
     * Que siempre que esté al menos el simbolo de pila se alcance un estado que no sea de salida
     * Que no se reemplace el fin de pila por cualquier otro simbolo
     *
     * */
    if (conservarTope) {
        // si se conserva el tope, hay al menos un elemento en la pila
        // por ende sólo se puede alcanzar estados que no sean de salida
        if (this->estados[EDestinoIndex].situacion)
            throw -50;
    } else {
        // si se desapila
        if ((char) 0 == apilamiento) {
            // si se desapila el fin de pila
            if (valorPila == this->finDePila) {
                // solo se puede alcanzar salida
                if (!this->estados[EDestinoIndex].situacion)
                    throw -51;
            } else {
                // no se puede alcanzar salida
                if (this->estados[EDestinoIndex].situacion)
                    throw -50;
            }
        } else {
            // en este caso algo se apila
            // no se puede reemplazar el tope de pila por otro simbolo
            if (valorPila == this->finDePila && apilamiento != this->finDePila) {
                throw -52;
            }
            if (this->estados[EDestinoIndex].situacion)
                throw -50;
        }
    }
    //fin bloque

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
    if (this->tieneSimbolosPilaDefinidos)
        throw -1;       // ya está lleno

    if (this->existsIn(c, this->alfabetoPila, this->cantActualElementosAlfabetoPila))
        throw -2;

    this->alfabetoPila[this->cantActualElementosAlfabetoPila] = c;
    this->cantActualElementosAlfabetoPila++;

    if (this->cantActualElementosAlfabetoPila == this->nroElementosAlfabetoPila) {
        this->tieneSimbolosPilaDefinidos = true;
        this->setAutomataListo();
    }
}

void APila::transicion() {
    if (this->automataApagado)
        throw -10;

    if (!this->automataListo) {
        if (!this->tieneEstadoInicial ||
            !this->tieneEstadoSalida ||
            !this->tieneEstadosDefinidos ||
            !this->tieneEntradasDefinidas ||
            !this->tieneSimbolosPilaDefinidos ||
            !this->tieneCadenaAnalizar)
            throw -30;
    }

    if ('\0' == this->cadenaAnalizar[0]) {
        this->apagarAutomata();
        return;
    }
    // no es una excepcion porque coresponde a la transicion lambda

    char entrada = this->cadenaAnalizar[0];
    this->cadenaAnalizar = &this->cadenaAnalizar[1];

    ElementosTransicionPila *salidaF;
    try {
        salidaF = this->f[this->getEstadoIndex(this->estadoActual->nombre)][this->getAlfabetoIndex(
                entrada)][this->getAlfabetoPilaIndex(this->pila->peek())];
    } catch (int exc) {
        if (-1 == exc)
            throw -21;
    }

    // En caso de efectuarse una transicion quita simbolo de la pila. Porque si no se hace la
    // transicion se perdería el tope de pila

    if (nullptr == salidaF) {
        Estado *tmpEstado = new Estado();
        tmpEstado->nombre = "ESTADO DE ERROR";
        tmpEstado->situacion = false;
        this->estadoActual = tmpEstado;
        this->automataApagado = true;
        //define automata como no usable
    } else {
        if (!salidaF->conservarTope)
            pila->pop();

        if ((char) 0 != salidaF->apilamiento)
            pila->push(salidaF->apilamiento);

        estadoActual = &salidaF->estado;

        if (!this->tieneFDeterminada) {
            this->tieneFDeterminada = true;
            this->setAutomataListo();
        }
    }
}

unsigned int APila::getAlfabetoPilaIndex(const char &s) {
    for (unsigned int i = 0; i < this->cantActualElementosAlfabetoPila; ++i) {
        if (s == this->alfabetoPila[i])
            return i;
    }
    throw -1;
}

// método para reemplazar la transición lambda entre útlimo estado alcanzado
// por el usuario y el estado de salida
void APila::apagarAutomata() {
    this->automataApagado = true;
    try {
        if (this->finDePila == this->pila->peek()) {
            this->estadoActual = this->buscarEstadoFinal();
        }
    } catch (int exc) {
        throw exc;
    }
}

Estado *APila::buscarEstadoFinal() {
    for (int i = 0; i < this->cantActualEstados; ++i) {
        if (this->estados[i].situacion)
            return &this->estados[i];
    }
    throw -5;
}

unsigned int APila::getNroElementosAlfabetoPila() {
    return this->nroElementosAlfabetoPila;
}

char APila::getTopeDePila() {
    char tmp = this->pila->pop();
    this->pila->push(tmp);
    return tmp;
}

bool APila::expresionFormalLista() {
    return !(!this->tieneEstadoInicial ||
             !this->tieneEstadoSalida ||
             !this->tieneEstadosDefinidos ||
             !this->tieneEntradasDefinidas ||
             !this->tieneSimbolosPilaDefinidos);
}

void APila::setAutomataListo() {
    this->automataListo = this->tieneEstadoInicial &&
                          this->tieneEstadoSalida &&
                          this->tieneEstadosDefinidos &&
                          this->tieneEntradasDefinidas &&
                          this->tieneFDeterminada &&
                          this->tieneSimbolosPilaDefinidos &&
                          this->tieneCadenaAnalizar;
}

std::string APila::tipoAutomata() {
    return "AP";
}

std::string APila::expresionEspecifica() {
    std::string r = "{ ";
    char i;
    for (i = 0; i < this->nroElementosAlfabetoPila - 1; i++) {
        r += this->alfabetoPila[i];
        r += ", ";
    }
    r += this->alfabetoPila[i];
    r += " }, ";
    r += this->finDePila;
    r += ", ";

    return r;
}