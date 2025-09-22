#ifndef FORNECEDOR_H
#define FORNECEDOR_H

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
} TipoFornecedor;

typedef struct ListaFornecedor{
    struct ListaFornecedor *prox;
    TipoFornecedor fornecedor;
} ListaFornecedor;

void inicializarFornecedor(TipoFornecedor *fornecedor);
void inicializarListaFornecedor(ListaFornecedor *lista);
int adicionarFornecedor(ListaFornecedor **lista, TipoFornecedor fornecedor);
int removerFornecedor(ListaFornecedor **lista, int id);
int atualizarFornecedor(ListaFornecedor *lista, TipoFornecedor fornecedorAtualizado, int id);
TipoFornecedor* buscarFornecedor(ListaFornecedor *lista, int id);

#endif // FORNECEDOR_H