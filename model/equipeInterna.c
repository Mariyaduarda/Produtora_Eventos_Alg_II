#include <stdio.h>
#include <string.h>
#include "equipeInterna.h"

void incializarEquipeInterna(TipoEquipeInterna *equipe){
    equipe->id = 0;
    strcpy(equipe->nome, "");
    strcpy(equipe->cpf, "");
    strcpy(equipe->funcao, "");
    equipe->valorDiariaHora = 0.0;
}

void cadastrarEquipeInterna(TipoEquipeInterna *equipe, int id, const char *nome, const char *cpf, const char *funcao, float valorDiariaHora){
    equipe->id = id;
    strcpy(equipe->nome, nome);
    strcpy(equipe->cpf, cpf);
    strcpy(equipe->funcao, funcao);
    equipe->valorDiariaHora = valorDiariaHora;
}

void inicializarListaEquipeInterna(ListaEquipeInterna *lista){
    lista->prox = NULL;
    incializarEquipeInterna(&lista->equipe);
}

int adicionarEquipeInterna(ListaEquipeInterna **lista, TipoEquipeInterna equipe){
    // aloca o espaco para um novo no'
    ListaEquipeInterna *novo = (ListaEquipeInterna *)malloc(sizeof(ListaEquipeInterna));
    
    // se n conseguir alocar, retorna erro
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->equipe = equipe;
    novo->prox = *lista;

    // atribui o novo no' como o inicio da lista
    *lista = novo;

    // retorna sucesso
    return 1;
}

int removerEquipeInterna(ListaEquipeInterna **lista, int id){
    // variaveis auxiliares para percorrer a lista
    ListaEquipeInterna *atual = *lista;
    ListaEquipeInterna *anterior = NULL;

    // percorre a lista ate' encontrar o cliente com o id ou o final da lista
    // - se oq eu to olhando n e' nulo e o id atual n e' oq eu quero, avanca
    while(atual != NULL && atual->equipe.id != id){
        anterior = atual;
        atual = atual->prox;
    }

    // quando sair do loop, ou achou o cliente q eu quero ou chegou no final da lista
    // - se n for nulo, achei o cliente
    if(atual != NULL){

        if(anterior == NULL){
            // se for o primeiro da lista, coloca a lista como o proximo do atual
            *lista = atual->prox;
        } else {
            // se n for o primeiro, liga o anterior com o proximo do atual
            anterior->prox = atual->prox;
        }

        // libera a memoria
        free(atual);

        // retorna sucesso
        return 1;
    }

    // se chegar aqui, n achei o cliente
    return 0;
}

int atualizarEquipeInterna(ListaEquipeInterna *lista, TipoEquipeInterna equipeAtualizado){
    // variavel auxiliar para percorrer a lista
    ListaEquipeInterna *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do cliente atual for o id q eu quero, atualiza os dados
        if(atual->equipe.id == equipeAtualizado.id){
            atual->equipe = equipeAtualizado;
            // deu bom, retorna sucesso
            return 1;
        }
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o cliente
    return 0;
}

TipoEquipeInterna* buscarEquipeInterna(ListaEquipeInterna *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaEquipeInterna *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do cliente atual for o id q eu quero, retorna os dados
        if(atual->equipe.id == id){
            return &atual->equipe;
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o cliente
    return NULL;
}