#ifndef RECURSOS_EQUIPAMENTOS_H
#define RECURSOS_EQUIPAMENTOS_H

#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char descricao[150];
    char categoria[50];
    int qtdEstoque;
    float precoCusto;
    float valorLocacao;
} RecursosEquipamentos;

typedef struct ListaRecursosEquipamentos {
    struct ListaRecursosEquipamentos *prox;
    RecursosEquipamentos recurso;
} ListaRecursosEquipamentos;

#endif RECURSOS_EQUIPAMENTOS_H