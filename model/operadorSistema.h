#ifndef OPERADORSISTEMA_H
#define OPERADORSISTEMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    char usuario[50];
    char senha[50];
} TipoOperadorSistema;

typedef struct ListaOperadorSistema{
    struct ListaOperadorSistema *prox;
    TipoOperadorSistema operador;
} ListaOperadorSistema;

void inicializarOperadorSistema(TipoOperadorSistema *operador);
void cadastrarOperadorSistema(TipoOperadorSistema *operador, int id, const char *nome, const char *usuario, const char *senha);
void inicializarListaOperadoresSistema(ListaOperadorSistema *lista);
int adicionarOperadorSistema(ListaOperadorSistema **lista, TipoOperadorSistema operador);
int removerOperadorSistema(ListaOperadorSistema **lista, int id);
int atualizarOperadorSistema(ListaOperadorSistema *lista, TipoOperadorSistema operadorAtualizado);
TipoOperadorSistema* buscarOperadorSistema(ListaOperadorSistema *lista, int id);

#endif // OPERADORSISTEMA_H