#ifndef FORNECEDORPARCEIRO_H
#define FORNECEDORPARCEIRO_H

#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nomeFantasia[100];
    char razaoSocial[100];
    char cpf_cnpj[14+1];
    char endereco[100];
    char telefone[15];
    char tipoServico[100];
} TipoFornecedorParceiro;

typedef struct {
    ListaFornecedorParceiro *prox;
    TipoFornecedorParceiro fornecedor;
} ListaFornecedorParceiro;

#endif FORNECEDORPARCEIRO_H