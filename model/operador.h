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

void inicializarOperador(TipoOperador *operador);
void inicializarListaOperador(ListaOperador *lista);
int adicionarOperador(ListaOperador **lista, TipoOperador operador);
int removerOperador(ListaOperador **lista, int id);
int atualizarOperador(ListaOperador *lista, TipoOperador operadorAtualizado, int id);
TipoOperador* buscarOperador(ListaOperador *lista, int id);

#endif // OPERADOR_H