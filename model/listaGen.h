#ifndef LISTA_GENERICA_H
#define LISTA_GENERICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Estrutura generica para um no' de uma lista generica
typedef struct No {
    void *dado;       // *** Ponteiro pra void aponta pra qualquer coisa ***
    int id;           // id, ajusta automatico quando adiciona elemento
    bool ativo;       // ativo ou desativo. para soft delete
    struct No *prox;  // ponteiro pro proximo no'
} No;

void inicializarLista(No **lista);
int adicionarElemento(No **lista, void *dado, size_t tamanho);
int removerElemento(No *lista, int id);
int atualizarElemento(No *lista, int id, void *novoDado, size_t tamanho);
void* buscarElemento(No *lista, int id);

#endif // LISTA_GENERICA_H