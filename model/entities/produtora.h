#ifndef PRODUTORA_H
#define PRODUTORA_H

#include <stdio.h>
#include <string.h>

typedef struct {
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

typedef struct {
    ListaProdutora *prox;
    Produtora produtora;
} ListaProdutora;

#endif PRODUTORA_H