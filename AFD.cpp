//#include <iostream>
#include "AFD.h"

using namespace std;

AFD::AFD(unsigned int cantEstados, unsigned int tamAlfabeto) : Automata(cantEstados, tamAlfabeto) {
    this->f = new Estado **[cantEstados];
    for (int i = 0; i < cantEstados; ++i) {
        f[i] = new Estado *[tamAlfabeto];
        for (int j = 0; j < tamAlfabeto; ++j)
            f[i][j] = nullptr;
    }
    //primer paramtro representa filas (estados)
    //segundo paramtetro representa columnas (entradas)
}

void AFD::setF(std::string nombreEstadoSalida, char entrada, std::string nombreEstadoDestino) {
    unsigned int ESalida, EDestino, entIndex;

//    if (!this->tieneEstadosDefinidos)
//        throw -21;              // tiene que tener todos los estados definidos
//    if (!this->tieneEntradasDefinidas)
//        throw -22;              // tiene que tener todas las entradas definidas
    if (tieneFDeterminada)
        throw -23;              // la funcion de transicion ya fue definida

    try {
        ESalida = this->getEstadoIndex(nombreEstadoSalida);
    } catch (int exc) {
        if (-1 == exc)
            throw -11;
    }
    try {
        EDestino = this->getEstadoIndex(nombreEstadoDestino);
    } catch (int exc) {
        if (-1 == exc)
            throw -12;
    }
    try {
        entIndex = this->getAlfabetoIndex(entrada);
    } catch (int exc) {
        if (-1 == exc)
            throw -13;
    }

    if (nullptr != this->f[ESalida][entIndex])
        throw -14;

    this->f[ESalida][entIndex] = new Estado();
    this->f[ESalida][entIndex]->nombre = this->estados[EDestino].nombre;
    this->f[ESalida][entIndex]->situacion = this->estados[EDestino].situacion;
    // se puede usar sobrecarga asignacion?

    this->tieneFDeterminada = this->isReadyF();
}

void AFD::transicion(char entrada) {
    if (!this->automataListo)
        throw -8;
    try {
        estadoActual = this->f[this->getEstadoIndex(estadoActual->nombre)][this->getAlfabetoIndex(entrada)];
    } catch (int exc) {
        if (-1 == exc)
            throw -21;
    }
}

bool AFD::isReadyF() {
    for (int i = 0; i < this->nroEstados; ++i)
        for (int j = 0; j < this->nroElementosAlfabeto; ++j)
            if (nullptr == f[i][j])
                return false;
    this->tieneFDeterminada = true;
    this->setAutomataListo();
    return true;
}

void AFD::setAutomataListo() {
    this->automataListo = this->tieneEstadoInicial && this->tieneEstadoSalida && this->tieneEstadosDefinidos &&
                          this->tieneEntradasDefinidas && this->tieneFDeterminada;
}

std::string AFD::getExpresionFormal() {
    if (!this->tieneEstadoInicial || !this->tieneEstadoSalida || !this->tieneEstadosDefinidos ||
        !this->tieneEntradasDefinidas)
        throw -55;

    return "";
}