//
// Created by FrancoBobadilla on 31/5/2018.
//

#include "MTuring.h"

MTuring::MTuring(unsigned int cantidadEstados, unsigned int tamanoAlfabeto, unsigned int tamanoAlfabetoCinta)
        : Automata(cantidadEstados, tamanoAlfabeto) {
    if (0 >= tamanoAlfabetoCinta)
        throw 0;

    this->nroElementosAlfabetoCinta = tamanoAlfabetoCinta;
    this->cantActualElementosAlfabetoCinta = 0;
    this->alfabetoCinta = new char[this->nroElementosAlfabetoCinta];

    //f [ESTADO ACTUAL] [ENTRADA] [VALOR CINTA] = SalidaFuncMaqTuring*
    f = new SalidaFuncMaqTuring ***[this->nroEstados];
    for (int i = 0; i < this->nroEstados; ++i) {
        f[i] = new SalidaFuncMaqTuring **[this->nroElementosAlfabeto];
        for (int j = 0; j < this->nroElementosAlfabeto; ++j) {
            f[i][j] = new SalidaFuncMaqTuring *[this->nroElementosAlfabetoCinta];
            for (int k = 0; k < this->nroElementosAlfabetoCinta; ++k) {
                f[i][j][k] = nullptr;
            }
        }
    }

    this->cinta = new Cinta<char>('/');
    /*
     * Se debe modificar el prototipo de constructor para admitir que el usuario elija el blanco
     * La clase Cinta debe implementar el metodo getBlanco() para la expresión final
     * Se debería replantear la misma situación para el automata de Pila con el fin de pila
     * */
}

void MTuring::setF(std::string nombreEstadoSalida, char entrada, char valorCinta, std::string nombreEstadoDestino,
                   char direccion, char escritura) {
    unsigned int ESalidaIndex, entradaIndex, valorCintaIndex, EDestinoIndex, escrituraIndex;
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
        entradaIndex = this->getAlfabetoIndex(entrada);
    } catch (int exc) {
        if (-1 == exc)
            throw -13;
    }
    try {
        valorCintaIndex = getAlfabetoCintaIndex(valorCinta);
    } catch (int exc) {
        if (-1 == exc)
            throw -14;
    }
    try {
        escrituraIndex = getAlfabetoCintaIndex(valorCinta);
    } catch (int exc) {
        if (-1 == exc)
            throw -15;
    }

    //(p: mantener, i:izquierda, d:derecha)
    // direccion no valida
    // se deberia castear mejor con toUpper etc. o solicitar al usuario que increse sus direcciones
    if ('p' != direccion && 'i' != direccion && 'd' != direccion)
        throw -17;

    if (nullptr != f[ESalidaIndex][entradaIndex][valorCintaIndex])
        throw -16;

    // tiene que haber una forma prolija de hacerlo
    this->f[ESalidaIndex][entradaIndex][valorCintaIndex]->estado.nombre = this->estados[EDestinoIndex].nombre;
    this->f[ESalidaIndex][entradaIndex][valorCintaIndex]->estado.situacion = this->estados[EDestinoIndex].situacion;
    this->f[ESalidaIndex][entradaIndex][valorCintaIndex]->direccion = direccion;
    this->f[ESalidaIndex][entradaIndex][valorCintaIndex]->escritura = this->alfabetoCinta[escrituraIndex];
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
}

void MTuring::transicion(char) {

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