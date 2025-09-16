#ifndef EQUIPEINTERNA_H
#define EQUIPEINTERNA_H

#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    char cpf[11+1];
    char funcao[50];
    float valorDiariaHora;
} TipoEquipeInterna;

typedef struct {
    ListaEquipeInterna *prox;
    TipoEquipeInterna equipe;
} ListaEquipeInterna;

#endif EQUIPEINTERNA_H