//
// Created by FrancoBobadilla on 31/5/2018.
//

#ifndef AFD_CABEZAL_H
#define AFD_CABEZAL_H

#include "Celda.h"

#define BLANCO '/'

template<class T>
class Cinta {
private:
    Celda<T> *cabezal;
    T blanco;
public:
    Cinta(T blanco);

    void escribir(T dato);

    void desplazarIzquierda();

    void desplazarDerecha();

    T leer();

    ~Cinta();
};

template<class T>
Cinta::Cinta(T blanco) {
    this->blanco = blanco;
    this->cabezal = new Celda<T>(blanco);
}

template<class T>
void Cinta<T>::escribir(T dato) {
    cabezal->setData(dato);
}

template<class T>
void Cinta<T>::leer() {
    return cabezal->getData();
}

template<class T>
void Cinta<T>::desplazarIzquierda() {
    if (cabezal->getLeft() == nullptr) {
        Celda<T> nn = new Celda<T>(blanco);
        nn->setRight(cabezal);
        cabezal->setLeft(nn);
    }
    cabezal = cabezal->getLeft();
}

template<class T>
void Cinta<T>::desplazarDerecha() {
    if (cabezal->getRight() == nullptr) {
        Celda<T> nn = new Celda<T>(blanco);
        nn->setLeft(cabezal);
        cabezal->setRight(nn);
    }
    cabezal = cabezal->getRight();
}

template<class T>
void Cinta::~Cinta() {
    while (cabezal->getLeft() != nullptr)
        cabezal = cabezal->getLeft();
    Celda<T> *ant;
    while (cabezal != nullptr) {
        ant = cabezal;
        cabezal = cabezal->getRight();
        delete ant;
    }
}

#endif //AFD_CABEZAL_H