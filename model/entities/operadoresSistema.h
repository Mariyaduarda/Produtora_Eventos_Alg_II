#ifndef OPERADORESSISTEMA_H
#define OPERADORESSISTEMA_H

#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    char usuario[50];
    char senha[50];
} OperadoresSistema;

typedef struct {
    ListaOperadoresSistema *prox;
    OperadoresSistema operador;
} ListaOperadoresSistema;

#endif OPERADORESSISTEMA_H