#ifndef FORNECEDORPARCEIRO_H
#define FORNECEDORPARCEIRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool ativo;
    int id;
    char nomeFantasia[100];
    char razaoSocial[100];
    char cpf_cnpj[14+1];
    char endereco[100];
    char telefone[15];
    char tipoServico[100];
} TipoFornecedorParceiro;

typedef struct ListaFornecedorParceiro{
    struct ListaFornecedorParceiro *prox;
    TipoFornecedorParceiro fornecedor;
} ListaFornecedorParceiro;

void inicializarFornecedorParceiro(TipoFornecedorParceiro *fornecedor);
void inicializarListaFornecedoresParceiros(ListaFornecedorParceiro *lista);
int adicionarFornecedorParceiro(ListaFornecedorParceiro **lista, TipoFornecedorParceiro fornecedor);
int removerFornecedorParceiro(ListaFornecedorParceiro **lista, int id);
int atualizarFornecedorParceiro(ListaFornecedorParceiro *lista, TipoFornecedorParceiro fornecedorAtualizado, int id);
TipoFornecedorParceiro* buscarFornecedorParceiro(ListaFornecedorParceiro *lista, int id);

#endif // FORNECEDORPARCEIRO_H