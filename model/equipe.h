#ifndef EQUIPE_H
#define EQUIPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool ativo;
    int id;
    char nome[100];
    char cpf[11+1];
    char funcao[50];
    float valorDiariaHora;
} TipoEquipe;

typedef struct ListaEquipe{
    struct ListaEquipe *prox;
    TipoEquipe equipe;
} ListaEquipe;

void inicializarEquipe(TipoEquipe *equipe);
void inicializarListaEquipe(ListaEquipe *lista);
int adicionarEquipe(ListaEquipe **lista, TipoEquipe equipe);
int removerEquipe(ListaEquipe **lista, int id);
int atualizarEquipe(ListaEquipe *lista, TipoEquipe equipeAtualizado, int id);
TipoEquipe* buscarEquipe(ListaEquipe *lista, int id);

#endif // EQUIPE_H