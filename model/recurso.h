#ifndef RECURSO_H
#define RECURSO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    // Atributos de estado
    int id;
    bool ativo;

    // Atributos
    char descricao[150];
    char categoria[50];
    int qtdEstoque;
    float precoCusto;
    float valorLocacao;
} TipoRecurso;

typedef struct ListaRecurso{
    struct ListaRecurso *prox;
    TipoRecurso recurso;
} ListaRecurso;

void recursoInit(TipoRecurso *recurso);
void recursoListaInit(ListaRecurso *lista);
int recursoAdicionar(ListaRecurso **lista, TipoRecurso recurso);
int recursoRemover(ListaRecurso **lista, int id);
int recursoAtualizar(ListaRecurso *lista, TipoRecurso recursoAtualizado, int id);
TipoRecurso* recursoBuscar(ListaRecurso *lista, int id);
void recursoListaLiberar(ListaRecurso* lista);

#endif // RECURSO_H