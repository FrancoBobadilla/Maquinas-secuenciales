//
// Created by nelon on 28/4/2018.
//

#ifndef AFD_STACK_H
#define AFD_STACK_H

#include "Node.h"

/*
 * Clase Pila. Sólo implementa los métodos del TAD
 * */

template<class T>
class Stack {
private:
    Node<T> *top;

public:
    Stack();

    ~Stack();

    void push(T dato);

    T pop();

    bool isEmpty();

    T peek();
};

template<class T>
Stack<T>::Stack() {
    this->top = nullptr;
}

template<class T>
Stack<T>::~Stack() {
    while (nullptr != this->top)
        this->pop();
}

template<class T>
void Stack<T>::push(T dato) {
    this->top = new Node<T>(dato, top);
}

template<class T>
T Stack<T>::pop() {
    if (nullptr == this->top)
        throw -11;
    T dataTmp = this->top->getData();
    Node<T> *ptrAux = this->top;

    this->top = this->top->getNext();
    delete ptrAux;

    return dataTmp;
}

template<class T>
bool Stack<T>::isEmpty() {
    return nullptr == this->top;
}

template <class T>
T Stack<T>::peek() {
    if(this->isEmpty())
        throw -11;
    return top->getData();
}

#endif //AFD_STACK_H