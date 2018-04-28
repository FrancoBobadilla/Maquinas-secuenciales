//
// Created by nelon on 28/4/2018.
//

#ifndef AFD_NODE_H
#define AFD_NODE_H


/*
 *
 * Clase que implementa Nodo
 *
 * */

template<class T>

class Node {
private:
    T data;
    Node<T> *next;

public:
    // Contructores
    Node<T>(T dato, Node<T> *siguiente);

    Node<T>(T dato);

    // Data methods
    T getData();

    void setData(T dato);

    // Next methods
    Node<T> *getNext();

    void setNext(Node<T> *ptr);
};

template<class T>
Node<T>::Node(T d) {
    this->data = d;
    this->next = nullptr;
}

template<class T>
Node<T>::Node(T d, Node<T> *n) {
    this->data = d;
    this->next = n;
}

template<class T>
T Node<T>::getData() {
    return this->data;
}

template<class T>
void Node<T>::setData(T d) {
    this->data = d;
}

template<class T>
Node<T> *Node<T>::getNext() {
    return this->next;
}

template<class T>
void Node<T>::setNext(Node<T> *p) {
    this->next = p;
}

#endif //AFD_NODE_H