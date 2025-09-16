#ifndef RECURSO_EQUIPAMENTO_H
#define RECURSO_EQUIPAMENTO_H

#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char descricao[150];
    char categoria[50];
    int qtdEstoque;
    float precoCusto;
    float valorLocacao;
} TipoRecursoEquipamento;

typedef struct {
    struct ListaRecursoEquipamento *prox;
    TipoRecursoEquipamento recurso;
} ListaRecursoEquipamento;

#endif RECURSO_EQUIPAMENTO_H