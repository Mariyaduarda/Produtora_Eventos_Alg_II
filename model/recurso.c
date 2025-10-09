#include <stdio.h>
#include <string.h>
#include "recurso.h"

void inicializarRecurso(TipoRecurso *recurso){
    recurso->ativo = true;
    recurso->id = 0;
    strcpy(recurso->descricao, "");
    strcpy(recurso->categoria, "");
    recurso->qtdEstoque = 0;
    recurso->precoCusto = 0.0;
    recurso->valorLocacao = 0.0;
}

void inicializarListaRecurso(ListaRecurso *lista){
    lista->prox = NULL;
    inicializarRecurso(&lista->recurso);
}

int adicionarRecurso(ListaRecurso **lista, TipoRecurso recurso){
    // aloca o espaco para um novo no'
    ListaRecurso *novo = (ListaRecurso *)malloc(sizeof(ListaRecurso));
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
        ListaRecurso *atual = *lista;
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

int removerRecurso(ListaRecurso **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaRecurso *atual = *lista;

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

int atualizarRecurso(ListaRecurso *lista, TipoRecurso recursoAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaRecurso *atual = lista;

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

TipoRecurso* buscarRecurso(ListaRecurso *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaRecurso *atual = lista;

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

void liberarListaRecurso(ListaRecurso* lista){
    //auxiliar pra liberar cada no um por um
    ListaRecurso* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

}