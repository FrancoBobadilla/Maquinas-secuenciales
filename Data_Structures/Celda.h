//
// Created by FrancoBobadilla on 31/5/2018.
//

#ifndef AFD_CELDA_H
#define AFD_CELDA_H

template<class T>
class Celda {
private:
    T data;
    Celda<T> *left;
    Celda<T> *right;

public:
    Celda<T>(T dato);

    T getData();

    void setData(T dato);

    Celda<T> *getLeft();

    Celda<T> *getRight();

    void setLeft(Celda<T> *p);

    void setRight(Celda<T> *p);
};

template<class T>
Celda<T>::Celda(T d) {
    this->data = d;
    this->left = nullptr;
    this->right = nullptr;
}

template<class T>
T Celda<T>::getData() {
    return this->data;
}

template<class T>
void Celda<T>::setData(T d) {
    this->data = d;
}

template<class T>
Celda<T> *Celda<T>::getLeft() {
    return this->left;
}

template<class T>
Celda<T> *Celda<T>::getRight() {
    return this->right;
}

template<class T>
void Celda<T>::setLeft(Celda<T> *p) {
    this->left = p;
}

template<class T>
void Celda<T>::setRight(Celda<T> *p) {
    this->right = p;
}

#endif //AFD_CELDA_H
