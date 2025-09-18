#ifndef EQUIPEINTERNA_H
#define EQUIPEINTERNA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    char cpf[11+1];
    char funcao[50];
    float valorDiariaHora;
} TipoEquipeInterna;

typedef struct ListaEquipeInterna{
    struct ListaEquipeInterna *prox;
    TipoEquipeInterna equipe;
} ListaEquipeInterna;

void inicializarEquipeInterna(TipoEquipeInterna *equipe);
void cadastrarEquipeInterna(TipoEquipeInterna *equipe, int id, const char *nome, const char *cpf, const char *funcao, float valorDiariaHora);
void inicializarListaEquipeInterna(ListaEquipeInterna *lista);
int adicionarEquipeInterna(ListaEquipeInterna **lista, TipoEquipeInterna equipe);
int removerEquipeInterna(ListaEquipeInterna **lista, int id);
int atualizarEquipeInterna(ListaEquipeInterna *lista, TipoEquipeInterna equipeAtualizado);
TipoEquipeInterna* buscarEquipeInterna(ListaEquipeInterna *lista, int id);

#endif // EQUIPEINTERNA_H