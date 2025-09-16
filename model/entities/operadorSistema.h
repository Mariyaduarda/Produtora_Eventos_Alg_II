#ifndef OPERADORSISTEMA_H
#define OPERADORSISTEMA_H

#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    char usuario[50];
    char senha[50];
} TipoOperadorSistema;

typedef struct {
    ListaOperadorSistema *prox;
    TipoOperadorSistema operador;
} ListaOperadorSistema;

#endif OPERADORSISTEMA_H