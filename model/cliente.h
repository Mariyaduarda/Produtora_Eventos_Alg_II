#ifndef CLIENTE_H
#define CLIENTE_H

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
    char nome[100];
    char endereco[100];
    char cpf_cnpj[20];
    char telefone[20];
    char email[100];
    char nomeDoContato[100];
} TipoCliente;

typedef struct ListaCliente{
    struct ListaCliente *prox;
    TipoCliente cliente;
} ListaCliente;

void inicializarCliente(TipoCliente *cliente);
void inicializarListaCliente(ListaCliente *lista);
int adicionarCliente(ListaCliente **lista, TipoCliente cliente);
int removerCliente(ListaCliente **lista, int id);
int atualizarCliente(ListaCliente *lista, TipoCliente clienteAtualizado, int id);
TipoCliente* buscarCliente(ListaCliente *lista, int id);

#endif // CLIENTE_H