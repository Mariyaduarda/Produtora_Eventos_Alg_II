#include <stdio.h>
#include <string.h>
#include "produtora.h"

void produtoraInit(TipoProdutora *produtora){
    produtora->ativo = true;
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

void produtoraListaInit(ListaProdutora *lista){
    lista->prox = NULL;
    produtoraInit(&lista->produtora);
}

int produtoraAdicionar(ListaProdutora **lista, TipoProdutora produtora){
    // aloca o espaco para um novo no'
    ListaProdutora *novo = (ListaProdutora *)malloc(sizeof(ListaProdutora));
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->produtora = produtora;
    novo->produtora.ativo = true;
    novo->prox = NULL;

    
    if(*lista == NULL){ // se a lista estiver vazia, o novo no' sera o primeiro
        novo->produtora.id = 1;
        *lista = novo;
    } else { // se n estiver vazia, percorre ate' o final da lista

        // variavel auxiliar para percorrer a lista
        ListaProdutora *atual = *lista;
        // percorre ate' o final da lista
        while(atual->prox != NULL) atual = atual->prox;

        // atribui o ID do novo no' como o ID do ultimo mais um
        novo->produtora.id = atual->produtora.id + 1;
        // adiciona o novo no' no final da lista
        atual->prox = novo;

    }

    // retorna sucesso
    return 1;
}

int produtoraRemover(ListaProdutora **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaProdutora *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id da produtora atual for o id q eu quero, marca como inativo
        if(atual->produtora.id == id){
            // marca a produtora como inativo
            atual->produtora.ativo = false;
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei a produtora
    return 0;
}

int produtoraAtualizar(ListaProdutora *lista, TipoProdutora produtoraAtualizada, int id){
    // variavel auxiliar para percorrer a lista
    ListaProdutora *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id da produtora atual for o id q eu quero, atualiza os dados
        if(atual->produtora.id == id){
            atual->produtora = produtoraAtualizada;
            atual->produtora.id = id; // garante q o id n vai ser alterado
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei a produtora
    return 0;
}

TipoProdutora* produtoraBuscar(ListaProdutora *lista, int id){
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

void produtoraListaLiberar(ListaProdutora* lista){
    //auxiliar pra liberar cada no um por um
    ListaProdutora* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

}