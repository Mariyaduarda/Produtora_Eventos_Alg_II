#include <stdio.h>
#include <string.h>
#include "operador.h"

void inicializarOperador(TipoOperador *operador){
    operador->ativo = true;
    operador->id = 0;
    strcpy(operador->nome, "");
    strcpy(operador->usuario, "");
    strcpy(operador->senha, "");
}

void inicializarListaOperador(ListaOperador *lista){
    lista->prox = NULL;
    inicializarOperador(&lista->operador);
}

int adicionarOperador(ListaOperador **lista, TipoOperador operador){
    // aloca o espaco para um novo no'
    ListaOperador *novo = (ListaOperador *)malloc(sizeof(ListaOperador));
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
        ListaOperador *atual = *lista;
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

int removerOperador(ListaOperador **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaOperador *atual = *lista;

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

int atualizarOperador(ListaOperador *lista, TipoOperador operadorAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaOperador *atual = lista;

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

TipoOperador* buscarOperador(ListaOperador *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaOperador *atual = lista;

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

void liberarListaOperador(ListaOperador* lista){
    //auxiliar pra liberar cada no um por um
    ListaOperador* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

}