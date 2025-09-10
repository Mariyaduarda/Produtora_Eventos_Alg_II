#include <stdio.h>
#include <string.h>
#include "../entities/fornecedoresParceiros.h"

void inicializarFornecedoresParceiros(FornecedoresParceiros *fornecedor){
    fornecedor->id = 0;
    strcpy(fornecedor->nomeFantasia, "");
    strcpy(fornecedor->razaoSocial, "");
    strcpy(fornecedor->cpf_cnpj, "");
    strcpy(fornecedor->endereco, "");
    strcpy(fornecedor->telefone, "");
    strcpy(fornecedor->tipoServico, "");
}

void cadastrarFornecedoresParceiros(FornecedoresParceiros *fornecedor, int id, const char *nomeFantasia, const char *razaoSocial, const char *cpf_cnpj, const char *endereco, const char *telefone, const char *tipoServico){
    fornecedor->id = id;
    strcpy(fornecedor->nomeFantasia, nomeFantasia);
    strcpy(fornecedor->razaoSocial, razaoSocial);
    strcpy(fornecedor->cpf_cnpj, cpf_cnpj);
    strcpy(fornecedor->endereco, endereco);
    strcpy(fornecedor->telefone, telefone);
    strcpy(fornecedor->tipoServico, tipoServico);
}

void inicializarListaFornecedoresParceiros(ListaFornecedoresParceiros *lista){
    lista->prox = NULL;
    inicializarFornecedoresParceiros(&lista->fornecedor);
}

int adicionarFornecedoresParceiros(ListaFornecedoresParceiros **lista, FornecedoresParceiros fornecedor){
    // aloca o espaco para um novo no'
    ListaFornecedoresParceiros *novo = (ListaFornecedoresParceiros *)malloc(sizeof(ListaFornecedoresParceiros));
    
    // se n conseguir alocar, retorna erro
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->fornecedor = fornecedor;
    novo->prox = *lista;

    // atribui o novo no' como o inicio da lista
    *lista = novo;

    // retorna sucesso
    return 1;
}

int removerFornecedoresParceiros(ListaFornecedoresParceiros **lista, int id){
    // variaveis auxiliares para percorrer a lista
    ListaFornecedoresParceiros *atual = *lista;
    ListaFornecedoresParceiros *anterior = NULL;

    // percorre a lista ate' encontrar o fornecedor com o id ou o final da lista
    // - se oq eu to olhando n e' nulo e o id atual n e' oq eu quero, avanca
    while(atual != NULL && atual->fornecedor.id != id){
        anterior = atual;
        atual = atual->prox;
    }

    // quando sair do loop, ou achou o fornecedor q eu quero ou chegou no final da lista
    // - se n for nulo, achei o fornecedor
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

    // se chegar aqui, n achei o fornecedor
    return 0;
}

int atualizarFornecedoresParceiros(ListaFornecedoresParceiros *lista, FornecedoresParceiros fornecedorAtualizado){
    // variavel auxiliar para percorrer a lista
    ListaFornecedoresParceiros *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do fornecedor atual for o id q eu quero, atualiza os dados
        if(atual->fornecedor.id == fornecedorAtualizado.id){
            atual->fornecedor = fornecedorAtualizado;
            // deu bom, retorna sucesso
            return 1;
        }
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o fornecedor
    return 0;
}

FornecedoresParceiros* buscarFornecedoresParceirosPorId(ListaFornecedoresParceiros *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaFornecedoresParceiros *atual = lista;

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