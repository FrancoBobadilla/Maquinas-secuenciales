//
// Created by nelon on 6/15/2018.
//

#ifndef AFD_FUNCIONESMAIN_H
#define AFD_FUNCIONESMAIN_H

#include <iostream>
#include "Automata.h"
#include "AFD.h"
#include "APila.h"
#include "MTuring.h"

#define LEERSTRING(X) fflush(stdin); cin >> X; fflush(stdin);

using namespace std;

void holaExterno();

char leerOpciones(const std::string&, const std::string &);

void cargarEstado(AFD &);
void cargarEstado(APila &);
void cargarEstado(MTuring &);

void cargarEstadoInicial(AFD &);
void cargarEstadoInicial(APila &);
void cargarEstadoInicial(MTuring &);

void cargarSimboloEntrada(AFD &);
void cargarSimboloEntrada(APila &);
void cargarSimboloEntrada(MTuring &);

void cargarSimboloPila(APila &);
void cargarSimboloCinta(MTuring &);

void definirUnaTransicion(AFD &);
void definirUnaTransicion(APila &);
void definirUnaTransicion(MTuring &);

void hacerUnaTransicion(AFD &);
void hacerUnaTransicion(APila &);
void hacerUnaTransicion(MTuring &);

void hacerTodasTransiciones(AFD &);
void hacerTodasTransiciones(APila &);
void hacerTodasTransiciones(MTuring &);

void ingresarCadenaAnalizar(AFD &);
void ingresarCadenaAnalizar(APila &);
void ingresarCadenaAnalizar(MTuring &);

void ponerCabezalCinta(MTuring &);

void mostrarSalida(AFD &);
void mostrarSalida(APila &);
void mostrarSalida(MTuring &);

#endif //AFD_FUNCIONESMAIN_H
