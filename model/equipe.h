#ifndef EQUIPE_H
#define EQUIPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    // Atributos de estado
    int id;
    bool ativo;

    // Atributos
    char nome[100];
    char cpf[20];
    char funcao[50];
    float valorDiariaHora;
} TipoEquipe;

typedef struct ListaEquipe{
    struct ListaEquipe *prox;
    TipoEquipe equipe;
} ListaEquipe;

void equipeInit(TipoEquipe *equipe);
void equipeListaInit(ListaEquipe *lista);
int equipeAdicionar(ListaEquipe **lista, TipoEquipe equipe);
int equipeRemover(ListaEquipe **lista, int id);
int equipeAtualizar(ListaEquipe *lista, TipoEquipe equipeAtualizado, int id);
TipoEquipe* equipeBuscar(ListaEquipe *lista, int id);
void equipeListaLiberar(ListaEquipe* lista);

#endif // EQUIPE_H