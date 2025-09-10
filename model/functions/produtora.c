#include <stdio.h>
#include <string.h>
#include "../entities/produtora.h"

void inicializarProdutora(Produtora *produtora){
    produtora->id = 0;
    strcpy(produtora->nomeFantasia, "");
    strcpy(produtora->razaoSocial, "");
    strcpy(produtora->inscricaoEstadual, "");
    strcpy(produtora->cnpj, "");
    strcpy(produtora->endereco, "");
    strcpy(produtora->telefone, "");
    strcpy(produtora->email, "");
    strcpy(produtora->nomeDoResponsavel, "");
    strcpy(produtora->telefoneDoResponsavel, "");
    produtora->margemDeLucro = 0.0;
}

void cadastrarProdutora(Produtora *produtora, int id, const char *nomeFantasia, const char *razaoSocial, const char *inscricaoEstadual, const char *cnpj, const char *endereco, const char *telefone, const char *email, const char *nomeDoResponsavel, const char *telefoneDoResponsavel, float margemDeLucro){
    produtora->id = id;
    strcpy(produtora->nomeFantasia, nomeFantasia);
    strcpy(produtora->razaoSocial, razaoSocial);
    strcpy(produtora->inscricaoEstadual, inscricaoEstadual);
    strcpy(produtora->cnpj, cnpj);
    strcpy(produtora->endereco, endereco);
    strcpy(produtora->telefone, telefone);
    strcpy(produtora->email, email);
    strcpy(produtora->nomeDoResponsavel, nomeDoResponsavel);
    strcpy(produtora->telefoneDoResponsavel, telefoneDoResponsavel);
    produtora->margemDeLucro = margemDeLucro;
}

void inicializarListaProdutora(ListaProdutora *lista){
    lista->prox = NULL;
    inicializarProdutora(&lista->produtora);
}

int adicionarProdutora(ListaProdutora **lista, Produtora produtora){
    // aloca o espaco para um novo no'
    ListaProdutora *novo = (ListaProdutora *)malloc(sizeof(ListaProdutora));
    
    // se n conseguir alocar, retorna erro
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->produtora = produtora;
    novo->prox = *lista;

    // atribui o novo no' como o inicio da lista
    *lista = novo;

    // retorna sucesso
    return 1;
}

int removerProdutora(ListaProdutora **lista, int id){
    // variaveis auxiliares para percorrer a lista
    ListaProdutora *atual = *lista;
    ListaProdutora *anterior = NULL;

    // percorre a lista ate' encontrar a produtora com o id ou o final da lista
    // - se oq eu to olhando n e' nulo e o id atual n e' oq eu quero, avanca
    while(atual != NULL && atual->produtora.id != id){
        anterior = atual;
        atual = atual->prox;
    }

    // quando sair do loop, ou achou a produtora q eu quero ou chegou no final da lista
    // - se n for nulo, achei a produtora
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

    // se chegar aqui, n achei a produtora
    return 0;
}

int atualizarProdutora(ListaProdutora *lista, Produtora produtoraAtualizada){
    // variavel auxiliar para percorrer a lista
    ListaProdutora *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id da produtora atual for o id q eu quero, atualiza os dados
        if(atual->produtora.id == produtoraAtualizada.id){
            atual->produtora = produtoraAtualizada;
            return 1; // retorna sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei a produtora
    return 0;
}

Produtora* buscarProdutoraPorId(ListaProdutora *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaProdutora *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id da produtora atual for o id q eu quero, retorna o endereco da produtora
        if(atual->produtora.id == id){
            return &atual->produtora;
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei a produtora
    return NULL;
}