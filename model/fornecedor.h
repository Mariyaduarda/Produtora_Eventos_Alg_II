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

void inicializarFornecedor(TipoFornecedor *fornecedor);
void inicializarListaFornecedor(ListaFornecedor *lista);
int adicionarFornecedor(ListaFornecedor **lista, TipoFornecedor fornecedor);
int removerFornecedor(ListaFornecedor **lista, int id);
int atualizarFornecedor(ListaFornecedor *lista, TipoFornecedor fornecedorAtualizado, int id);
TipoFornecedor* buscarFornecedor(ListaFornecedor *lista, int id);

#endif // FORNECEDOR_H