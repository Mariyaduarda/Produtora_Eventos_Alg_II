#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    char cpf_cnpj[14+1];
    char telefone[15];
    char email[100];
    char nomeDoContato[100];
} Clientes;

typedef struct {
    ListaClientes *prox;
    Clientes cliente;
} ListaClientes;

#endif CLIENTE_H