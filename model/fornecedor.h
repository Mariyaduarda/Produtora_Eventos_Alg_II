#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    // Atributos de estado
    int id;
    bool ativo;
    bool usa_CNPJ;

    // Atributos
    char nomeFantasia[100];
    char razaoSocial[100];
    char cpf_cnpj[20];
    char endereco[100];
    char telefone[20];
    char tipoServico[100];
} TipoFornecedor;

typedef struct ListaFornecedor{
    struct ListaFornecedor *prox;
    TipoFornecedor fornecedor;
} ListaFornecedor;

void fornecedorInit(TipoFornecedor *fornecedor);
void fornecedorListaInit(ListaFornecedor *lista);
int fornecedorAdicionar(ListaFornecedor **lista, TipoFornecedor fornecedor);
int fornecedorRemover(ListaFornecedor **lista, int id);
int fornecedorAtualizar(ListaFornecedor *lista, TipoFornecedor fornecedorAtualizado, int id);
TipoFornecedor* fornecedorBuscar(ListaFornecedor *lista, int id);
void fornecedorListaLiberar(ListaFornecedor* lista);

#endif // FORNECEDOR_H