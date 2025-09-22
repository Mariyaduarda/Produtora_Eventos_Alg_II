#include <stdio.h>
#include <string.h>
#include "recursoEquipamento.h"

void inicializarRecursosEquipamentos(TipoRecursoEquipamento *recurso){
    recurso->ativo = true;
    recurso->id = 0;
    strcpy(recurso->descricao, "");
    strcpy(recurso->categoria, "");
    recurso->qtdEstoque = 0;
    recurso->precoCusto = 0.0;
    recurso->valorLocacao = 0.0;
}

void inicializarListaRecursosEquipamentos(ListaRecursoEquipamento *lista){
    lista->prox = NULL;
    inicializarRecursosEquipamentos(&lista->recurso);
}

int adicionarRecursosEquipamentos(ListaRecursoEquipamento **lista, TipoRecursoEquipamento recurso){
    // aloca o espaco para um novo no'
    ListaRecursoEquipamento *novo = (ListaRecursoEquipamento *)malloc(sizeof(ListaRecursoEquipamento));
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->recurso = recurso;
    novo->recurso.ativo = true;
    novo->prox = NULL;

    
    if(*lista == NULL){ // se a lista estiver vazia, o novo no' sera o primeiro
        novo->recurso.id = 1;
        *lista = novo;
    } else { // se n estiver vazia, percorre ate' o final da lista

        // variavel auxiliar para percorrer a lista
        ListaRecursoEquipamento *atual = *lista;
        // percorre ate' o final da lista
        while(atual->prox != NULL) atual = atual->prox;

        // atribui o ID do novo no' como o ID do ultimo mais um
        novo->recurso.id = atual->recurso.id + 1;
        // adiciona o novo no' no final da lista
        atual->prox = novo;

    }

    // retorna sucesso
    return 1;
}

int removerRecursosEquipamentos(ListaRecursoEquipamento **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaRecursoEquipamento *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do recurso atual for o id q eu quero, marca como inativo
        if(atual->recurso.id == id){
            // marca o recurso como inativo
            atual->recurso.ativo = false;
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o recurso
    return 0;
}

int atualizarRecursosEquipamentos(ListaRecursoEquipamento *lista, TipoRecursoEquipamento recursoAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaRecursoEquipamento *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do recurso atual for o id q eu quero, atualiza os dados
        if(atual->recurso.id == id){
            atual->recurso = recursoAtualizado;
            atual->recurso.id = id; // garante q o id n vai ser alterado
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o recurso
    return 0;
}

TipoRecursoEquipamento* buscarRecursosEquipamentosPorId(ListaRecursoEquipamento *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaRecursoEquipamento *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do recurso atual for o id q eu quero, retorna o recurso
        if(atual->recurso.id == id){
            return &atual->recurso; // retorna o recurso encontrado
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o recurso
    return NULL;
}