#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    char cpf_cnpj[14+1];
    char telefone[15];
    char email[100];
    char nomeDoContato[100];
} TipoCliente;

typedef struct ListaCliente{
    struct ListaCliente *prox;
    TipoCliente cliente;
} ListaCliente;

void inicializarCliente(TipoCliente *cliente);
void cadastrarCliente(TipoCliente *cliente, int id, const char *nome, const char *cpf_cnpj, const char *telefone, const char *email, const char *nomeDoContato);
void inicializarListaCliente(ListaCliente *lista);
int adicionarCliente(ListaCliente **lista, TipoCliente cliente);
int removerCliente(ListaCliente **lista, int id);
int atualizarCliente(ListaCliente *lista, TipoCliente clienteAtualizado);
TipoCliente* buscarCliente(ListaCliente *lista, int id);

#endif // CLIENTE_H