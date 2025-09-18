#ifndef RECURSO_EQUIPAMENTO_H
#define RECURSO_EQUIPAMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
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
void cadastrarRecursoEquipamento(TipoRecursoEquipamento *recurso, int id, const char *descricao, const char *categoria, int qtdEstoque, float precoCusto, float valorLocacao);
void inicializarListaRecursosEquipamentos(ListaRecursoEquipamento *lista);
int adicionarRecursoEquipamento(ListaRecursoEquipamento **lista, TipoRecursoEquipamento recurso);
int removerRecursoEquipamento(ListaRecursoEquipamento **lista, int id);
int atualizarRecursoEquipamento(ListaRecursoEquipamento *lista, TipoRecursoEquipamento recursoAtualizado);
TipoRecursoEquipamento* buscarRecursoEquipamento(ListaRecursoEquipamento *lista, int id);

#endif // RECURSO_EQUIPAMENTO_H