#ifndef RECURSO_EQUIPAMENTO_H
#define RECURSO_EQUIPAMENTO_H

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
} TipoRecursoEquipamento;

typedef struct ListaRecursoEquipamento{
    struct ListaRecursoEquipamento *prox;
    TipoRecursoEquipamento recurso;
} ListaRecursoEquipamento;

void inicializarRecursoEquipamento(TipoRecursoEquipamento *recurso);
void inicializarListaRecursosEquipamentos(ListaRecursoEquipamento *lista);
int adicionarRecursoEquipamento(ListaRecursoEquipamento **lista, TipoRecursoEquipamento recurso);
int removerRecursoEquipamento(ListaRecursoEquipamento **lista, int id);
int atualizarRecursoEquipamento(ListaRecursoEquipamento *lista, TipoRecursoEquipamento recursoAtualizado, int id);
TipoRecursoEquipamento* buscarRecursoEquipamento(ListaRecursoEquipamento *lista, int id);

#endif // RECURSO_EQUIPAMENTO_H