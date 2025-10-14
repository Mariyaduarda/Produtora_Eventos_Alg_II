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

void clienteInit(TipoCliente *cliente);
void clienteListaInit(ListaCliente *lista);
int clienteAdicionar(ListaCliente **lista, TipoCliente cliente);
int clienteRemover(ListaCliente **lista, int id);
int clienteAtualizar(ListaCliente *lista, TipoCliente clienteAtualizado, int id);
TipoCliente* clienteBuscar(ListaCliente *lista, int id);
void clienteListaLiberar(ListaCliente* lista);

int clienteSalvarTXT(ListaCliente *lista);
ListaCliente* clienteLerTXT();

#endif // CLIENTE_H