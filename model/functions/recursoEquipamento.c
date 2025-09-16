#include <stdio.h>
#include <string.h>
#include "../entities/recursoEquipamento.h"

void inicializarRecursosEquipamentos(TipoRecursoEquipamento *recurso){
    recurso->id = 0;
    strcpy(recurso->descricao, "");
    strcpy(recurso->categoria, "");
    recurso->qtdEstoque = 0;
    recurso->precoCusto = 0.0;
    recurso->valorLocacao = 0.0;
}

void cadastrarRecursosEquipamentos(TipoRecursoEquipamento *recurso, int id, const char *descricao, const char *categoria, int qtdEstoque, float precoCusto, float valorLocacao){
    recurso->id = id;
    strcpy(recurso->descricao, descricao);
    strcpy(recurso->categoria, categoria);
    recurso->qtdEstoque = qtdEstoque;
    recurso->precoCusto = precoCusto;
    recurso->valorLocacao = valorLocacao;
}

void inicializarListaRecursosEquipamentos(ListaRecursoEquipamento *lista){
    lista->prox = NULL;
    inicializarRecursosEquipamentos(&lista->recurso);
}

int adicionarRecursosEquipamentos(ListaRecursoEquipamento **lista, TipoRecursoEquipamento recurso){
    // aloca o espaco para um novo no'
    ListaRecursoEquipamento *novo = (ListaRecursoEquipamento *)malloc(sizeof(ListaRecursoEquipamento));
    
    // se n conseguir alocar, retorna erro
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->recurso = recurso;
    novo->prox = *lista;

    // atribui o novo no' como o inicio da lista
    *lista = novo;

    // retorna sucesso
    return 1;
}

int removerRecursosEquipamentos(ListaRecursoEquipamento **lista, int id){
    // variaveis auxiliares para percorrer a lista
    ListaRecursoEquipamento *atual = *lista;
    ListaRecursoEquipamento *anterior = NULL;

    // percorre a lista ate' encontrar o recurso com o id ou o final da lista
    // - se oq eu to olhando n e' nulo e o id atual n e' oq eu quero, avanca
    while(atual != NULL && atual->recurso.id != id){
        anterior = atual;
        atual = atual->prox;
    }

    // quando sair do loop, ou achou o recurso q eu quero ou chegou no final da lista
    // - se n for nulo, achei o recurso
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

    // se chegar aqui, n achei o recurso
    return 0;
}

int atualizarRecursosEquipamentos(ListaRecursoEquipamento *lista, int id, const char *descricao, const char *categoria, int qtdEstoque, float precoCusto, float valorLocacao){
    // variavel auxiliar para percorrer a lista
    ListaRecursoEquipamento *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do recurso atual for o id q eu quero, atualiza os dados
        if(atual->recurso.id == id){
            strcpy(atual->recurso.descricao, descricao);
            strcpy(atual->recurso.categoria, categoria);
            atual->recurso.qtdEstoque = qtdEstoque;
            atual->recurso.precoCusto = precoCusto;
            atual->recurso.valorLocacao = valorLocacao;
            return 1; // retorna sucesso
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