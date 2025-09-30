#include <stdio.h>
#include <string.h>
#include "fornecedor.h"

void inicializarFornecedor(TipoFornecedor *fornecedor){
    fornecedor->ativo = true;     // td objeto comeca como ativo
    fornecedor->usa_CNPJ = false; // por padrao usa cpf ao inves de cnpj
    fornecedor->id = 0;           // id vai ser calculado automaticamente
    
    strcpy(fornecedor->nomeFantasia, "");
    strcpy(fornecedor->razaoSocial, "");
    strcpy(fornecedor->cpf_cnpj, "");
    strcpy(fornecedor->endereco, "");
    strcpy(fornecedor->telefone, "");
    strcpy(fornecedor->tipoServico, "");
}

void inicializarListaFornecedor(ListaFornecedor *lista){
    lista->prox = NULL;
    inicializarFornecedor(&lista->fornecedor);
}

int adicionarFornecedor(ListaFornecedor **lista, TipoFornecedor fornecedor){
    // aloca o espaco para um novo no'
    ListaFornecedor *novo = (ListaFornecedor *)malloc(sizeof(ListaFornecedor));
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->fornecedor = fornecedor;
    novo->fornecedor.ativo = true;
    novo->prox = NULL;

    
    if(*lista == NULL){ // se a lista estiver vazia, o novo no' sera o primeiro
        novo->fornecedor.id = 1;
        *lista = novo;
    } else { // se n estiver vazia, percorre ate' o final da lista

        // variavel auxiliar para percorrer a lista
        ListaFornecedor *atual = *lista;
        // percorre ate' o final da lista
        while(atual->prox != NULL) atual = atual->prox;

        // atribui o ID do novo no' como o ID do ultimo mais um
        novo->fornecedor.id = atual->fornecedor.id + 1;
        // adiciona o novo no' no final da lista
        atual->prox = novo;

    }

    // retorna sucesso
    return 1;
}

int removerFornecedor(ListaFornecedor **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaFornecedor *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do fornecedor atual for o id q eu quero, marca como inativo
        if(atual->fornecedor.id == id){
            // marca o fornecedor como inativo
            atual->fornecedor.ativo = false;
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o fornecedor
    return 0;
}

int atualizarFornecedor(ListaFornecedor *lista, TipoFornecedor fornecedorAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaFornecedor *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do fornecedor atual for o id q eu quero, atualiza os dados
        if(atual->fornecedor.id == id){
            atual->fornecedor = fornecedorAtualizado;
            atual->fornecedor.id = id; // garante q o id n vai ser alterado
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o fornecedor
    return 0;
}

TipoFornecedor* buscarFornecedor(ListaFornecedor *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaFornecedor *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do fornecedor atual for o id q eu quero, retorna o fornecedor
        if(atual->fornecedor.id == id){
            return &atual->fornecedor;
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o fornecedor
    return NULL;
}