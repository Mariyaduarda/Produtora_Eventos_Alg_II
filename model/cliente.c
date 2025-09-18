#include <stdio.h>
#include <string.h>
#include "cliente.h"

void inicializarCliente(TipoCliente *cliente){
    cliente->id = 0;
    strcpy(cliente->nome, "");
    strcpy(cliente->cpf_cnpj, "");
    strcpy(cliente->telefone, "");
    strcpy(cliente->email, "");
    strcpy(cliente->nomeDoContato, "");
}

void cadastrarCliente(TipoCliente *cliente, int id, const char *nome, const char *cpf_cnpj, const char *telefone, const char *email, const char *nomeDoContato){
    cliente->id = id;
    strcpy(cliente->nome, nome);
    strcpy(cliente->cpf_cnpj, cpf_cnpj);
    strcpy(cliente->telefone, telefone);
    strcpy(cliente->email, email);
    strcpy(cliente->nomeDoContato, nomeDoContato);
}

void inicializarListaCliente(ListaCliente *lista){
    lista->prox = NULL;
    inicializarCliente(&lista->cliente);
}

int adicionarCliente(ListaCliente **lista, TipoCliente cliente){
    // aloca o espaco para um novo no'
    ListaCliente *novo = (ListaCliente *)malloc(sizeof(ListaCliente));
    
    // se n conseguir alocar, retorna erro
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->cliente = cliente;
    novo->prox = *lista;

    // atribui o novo no' como o inicio da lista
    *lista = novo;

    // retorna sucesso
    return 1;
}

int removerCliente(ListaCliente **lista, int id){
    // variaveis auxiliares para percorrer a lista
    ListaCliente *atual = *lista;
    ListaCliente *anterior = NULL;

    // percorre a lista ate' encontrar o cliente com o id ou o final da lista
    // - se oq eu to olhando n e' nulo e o id atual n e' oq eu quero, avanca
    while(atual != NULL && atual->cliente.id != id){
        anterior = atual;
        atual = atual->prox;
    }

    // quando sair do loop, ou achou o cliente q eu quero ou chegou no final da lista
    // - se n for nulo, achei o cliente
    if(atual != NULL){
        // confere se o cliente q vou remover e' o primeiro da lista
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

int atualizarCliente(ListaCliente *lista, TipoCliente clienteAtualizado){
    // variavel auxiliar para percorrer a lista
    ListaCliente *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do cliente atual for o id q eu quero, atualiza os dados
        if(atual->cliente.id == clienteAtualizado.id){
            atual->cliente = clienteAtualizado;
            // deu bom, retorna sucesso
            return 1;
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o cliente
    return 0;
}

TipoCliente* buscarCliente(ListaCliente *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaCliente *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do cliente atual for o id q eu quero, retorna o endereco cliente
        if(atual->cliente.id == id){
            return &atual->cliente;
        }
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o cliente
    // portanto, retorna nulo
    return NULL;
}
