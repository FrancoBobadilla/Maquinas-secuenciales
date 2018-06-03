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
    this->Determinado = false;
    //primer paramtro representa filas (estados)
    //segundo paramtetro representa columnas (entradas)
}

void AFD::setF(std::string nombreEstadoSalida, char entrada, std::string nombreEstadoDestino) {
    unsigned int ESalida, EDestino, entIndex;
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

}

void AFD::transicion(char entrada) {
    if (!this->Determinado)
        if (!this->isReadyF())
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
    this->Determinado = true;
    return true;
}