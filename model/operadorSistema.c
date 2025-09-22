#include <stdio.h>
#include <string.h>
#include "operadorSistema.h"

void inicializarOperadoresSistema(TipoOperadorSistema *operador){
    operador->ativo = true;
    operador->id = 0;
    strcpy(operador->nome, "");
    strcpy(operador->usuario, "");
    strcpy(operador->senha, "");
}

void inicializarListaOperadoresSistema(ListaOperadorSistema *lista){
    lista->prox = NULL;
    inicializarOperadoresSistema(&lista->operador);
}

int adicionarOperadoresSistema(ListaOperadorSistema **lista, TipoOperadorSistema operador){
    // aloca o espaco para um novo no'
    ListaOperadorSistema *novo = (ListaOperadorSistema *)malloc(sizeof(ListaOperadorSistema));
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->operador = operador;
    novo->operador.ativo = true;
    novo->prox = NULL;
    
    if(*lista == NULL){ // se a lista estiver vazia, o novo no' sera o primeiro
        novo->operador.id = 1;
        *lista = novo;
    } else { // se n estiver vazia, percorre ate' o final da lista

        // variavel auxiliar para percorrer a lista
        ListaOperadorSistema *atual = *lista;
        // percorre ate' o final da lista
        while(atual->prox != NULL) atual = atual->prox;

        // atribui o ID do novo no' como o ID do ultimo mais um
        novo->operador.id = atual->operador.id + 1;
        // adiciona o novo no' no final da lista
        atual->prox = novo;

    }

    // retorna sucesso
    return 1;
}

int removerOperadoresSistema(ListaOperadorSistema **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaOperadorSistema *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do operador atual for o id q eu quero, marca como inativo
        if(atual->operador.id == id){
            // marca o operador como inativo
            atual->operador.ativo = false;
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o operador
    return 0;
}

int atualizarOperadoresSistema(ListaOperadorSistema *lista, TipoOperadorSistema operadorAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaOperadorSistema *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do operador atual for o id q eu quero, atualiza os dados
        if(atual->operador.id == id){
            atual->operador = operadorAtualizado;
            atual->operador.id = id; // garante q o id n vai ser alterado
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o operador
    return 0;
}

TipoOperadorSistema* buscarOperadoresSistema(ListaOperadorSistema *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaOperadorSistema *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do operador atual for o id q eu quero, retorna o operador
        if(atual->operador.id == id){
            return &atual->operador;
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o operador
    return NULL;
}