#ifndef PRODUTORA_H
#define PRODUTORA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool ativo;
    int id;
    char nomeFantasia[100];
    char razaoSocial[100];
    char inscricaoEstadual[11];
    char cnpj[14+1];
    char endereco[100];
    char telefone[15];
    char email[100];
    char nomeDoResponsavel[50];
    char telefoneDoResponsavel[15];
    float margemDeLucro;
} TipoProdutora;

typedef struct ListaProdutora{
    struct ListaProdutora *prox;
    TipoProdutora produtora;
} ListaProdutora;

void inicializarProdutora(TipoProdutora *produtora);
void inicializarListaProdutora(ListaProdutora *lista);
int adicionarProdutora(ListaProdutora **lista, TipoProdutora produtora);
int removerProdutora(ListaProdutora **lista, int id);
int atualizarProdutora(ListaProdutora *lista, TipoProdutora produtoraAtualizada, int id);
TipoProdutora* buscarProdutora(ListaProdutora *lista, int id);

#endif // PRODUTORA_H