#ifndef PRODUTORA_H
#define PRODUTORA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char nomeFantasia[100];
    char razaoSocial[100];
    char inscricaoEstadual[20];
    char cnpj[20];
    char endereco[100];
    char telefone[20];
    char email[100];
    char nomeDoResponsavel[50];
    char telefoneDoResponsavel[20];
    float margemDeLucro;
} TipoProdutora;

void produtoraInit(TipoProdutora *produtora);
int produtoraSalvarTXT(TipoProdutora *produtora);
int produtoraLerTXT(TipoProdutora *produtora);
int produtoraSalvarBIN(TipoProdutora *produtora);
int produtoraLerBIN(TipoProdutora *produtora);

#endif // PRODUTORA_H