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
} Produtora;

typedef struct ListaProdutora{
    struct ListaProdutora *prox;
    Produtora produtora;
} ListaProdutora;

void inicializarProdutora(Produtora *produtora);
void inicializarListaProdutora(ListaProdutora *lista);
int adicionarProdutora(ListaProdutora **lista, Produtora produtora);
int removerProdutora(ListaProdutora **lista, int id);
int atualizarProdutora(ListaProdutora *lista, Produtora produtoraAtualizada, int id);
Produtora* buscarProdutora(ListaProdutora *lista, int id);

#endif // PRODUTORA_H