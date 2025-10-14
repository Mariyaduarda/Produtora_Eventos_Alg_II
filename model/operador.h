#ifndef OPERADOR_H
#define OPERADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    // Atributos de estado
    int id;
    bool ativo;
    
    // Atributos
    char nome[100];
    char usuario[50];
    char senha[50];
} TipoOperador;

typedef struct ListaOperador{
    struct ListaOperador *prox;
    TipoOperador operador;
} ListaOperador;

void operadorInit(TipoOperador *operador);
void operadorListaInit(ListaOperador *lista);
int operadorAdicionar(ListaOperador **lista, TipoOperador operador);
int operadorRemover(ListaOperador **lista, int id);
int operadorAtualizar(ListaOperador *lista, TipoOperador operadorAtualizado, int id);
TipoOperador* operadorBuscar(ListaOperador *lista, int id);
void operadorListaLiberar(ListaOperador* lista);

#endif // OPERADOR_H