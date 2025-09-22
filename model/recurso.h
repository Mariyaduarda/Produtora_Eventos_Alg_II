#ifndef RECURSO_H
#define RECURSO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool ativo;
    int id;
    char descricao[150];
    char categoria[50];
    int qtdEstoque;
    float precoCusto;
    float valorLocacao;
} TipoRecurso;

typedef struct ListaRecurso{
    struct ListaRecurso *prox;
    TipoRecurso recurso;
} ListaRecurso;

void inicializarRecurso(TipoRecurso *recurso);
void inicializarListaRecurso(ListaRecurso *lista);
int adicionarRecurso(ListaRecurso **lista, TipoRecurso recurso);
int removerRecurso(ListaRecurso **lista, int id);
int atualizarRecurso(ListaRecurso *lista, TipoRecurso recursoAtualizado, int id);
TipoRecurso* buscarRecurso(ListaRecurso *lista, int id);

#endif // RECURSO_H