#ifndef FORNECEDORPARCEIRO_H
#define FORNECEDORPARCEIRO_H

#include <stdio.h>
#include <stdlib.h>
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

typedef struct ListaFornecedorParceiro{
    struct ListaFornecedorParceiro *prox;
    TipoFornecedorParceiro fornecedor;
} ListaFornecedorParceiro;

void inicializarFornecedorParceiro(TipoFornecedorParceiro *fornecedor);
void cadastrarFornecedorParceiro(TipoFornecedorParceiro *fornecedor, int id, const char *nomeFantasia, const char *razaoSocial, const char *cpf_cnpj, const char *endereco, const char *telefone, const char *tipoServico);
void inicializarListaFornecedoresParceiros(ListaFornecedorParceiro *lista);
int adicionarFornecedorParceiro(ListaFornecedorParceiro **lista, TipoFornecedorParceiro fornecedor);
int removerFornecedorParceiro(ListaFornecedorParceiro **lista, int id);
int atualizarFornecedorParceiro(ListaFornecedorParceiro *lista, TipoFornecedorParceiro fornecedorAtualizado);
TipoFornecedorParceiro* buscarFornecedorParceiro(ListaFornecedorParceiro *lista, int id);

#endif // FORNECEDORPARCEIRO_H