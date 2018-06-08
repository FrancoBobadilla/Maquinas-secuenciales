//
// Created by FrancoBobadilla on 31/5/2018.
//

#ifndef AFD_CINTA_H
#define AFD_CINTA_H

#include <w32api/d2d1helper.h>
#include "Celda.h"

template<class T>
class Cinta {
private:
    Celda<T> *inicio;
    Celda<T> *cabezal;
    T blanco;
    unsigned int tamano;
public:
    Cinta(T blanco);

    Cinta(const Cinta<T> &);

    void escribir(T dato);

    void desplazarIzquierda();

    void desplazarDerecha();

    T leer();

    T getBlanco();

    unsigned int getTamano();

    ~Cinta();
};

template<class T>
Cinta<T>::Cinta(T blanco) {
    this->blanco = blanco;
    this->cabezal = new Celda<T>(blanco);
    this->tamano = 1;
    this->inicio = this->cabezal;
}

template<class T>
Cinta<T>::Cinta(const Cinta<T> &O) {
    this->blanco = O.blanco;
    this->tamano = O.tamano;

    this->cabezal = new Celda<T>(O.cabezal->getData());
    Celda<T> *tmpOriginal = O.cabezal;              // recorren la original cinta
    Celda<T> *tmpCopia = this->cabezal;             // recorren la nueva cinta

    while (tmpOriginal->getData() != this->blanco) {
        tmpOriginal = tmpOriginal->getRight();
        Celda<T> *nn = new Celda<T>(tmpOriginal->getData());
        nn->setLeft(tmpCopia);
        tmpCopia->setRight(nn);
        tmpCopia = nn;
    }

    tmpOriginal = O.cabezal;
    tmpCopia = this->cabezal;

    while (tmpOriginal->getData() != this->blanco) {
        tmpOriginal = tmpOriginal->getLeft();
        Celda<T> *nn = new Celda<T>(tmpOriginal->getData());
        nn->setRight(tmpCopia);
        tmpCopia->setLeft(nn);
        tmpCopia = nn;
    }

    this->inicio = tmpCopia;
}

template<class T>
void Cinta<T>::escribir(T dato) {
    cabezal->setData(dato);
}

template<class T>
T Cinta<T>::leer() {
    return this->cabezal->getData();
}

template<class T>
void Cinta<T>::desplazarIzquierda() {
    if (this->cabezal->getLeft() == nullptr) {
        Celda<T> *nn = new Celda<T>(blanco);
        this->tamano++;
        nn->setRight(cabezal);
        this->cabezal->setLeft(nn);
        this->inicio = nn;
    }
    this->cabezal = this->cabezal->getLeft();
}

template<class T>
void Cinta<T>::desplazarDerecha() {
    if (cabezal->getRight() == nullptr) {
        Celda<T> *nn = new Celda<T>(blanco);
        this->tamano++;
        nn->setLeft(cabezal);
        this->cabezal->setRight(nn);
    }
    this->cabezal = this->cabezal->getRight();
}

template<class T>
T Cinta<T>::getBlanco() {
    return this->blanco;
}

template<class T>
unsigned int Cinta<T>::getTamano() {
    return this->tamano;
}

template<class T>
Cinta<T>::~Cinta() {
    while (this->cabezal->getLeft() != nullptr)
        this->cabezal = this->cabezal->getLeft();
    Celda<T> *ant;
    while (this->cabezal != nullptr) {
        ant = this->cabezal;
        this->cabezal = this->cabezal->getRight();
        delete ant;
    }
//    delete inicio;
}

#endif //AFD_CINTA_H