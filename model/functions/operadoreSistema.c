#include <stdio.h>
#include <string.h>
#include "../entities/operadorSistema.h"

void inicializarOperadoresSistema(TipoOperadorSistema *operador){
    operador->id = 0;
    strcpy(operador->nome, "");
    strcpy(operador->usuario, "");
    strcpy(operador->senha, "");
}

void cadastrarOperadoresSistema(TipoOperadorSistema *operador, int id, const char *nome, const char *usuario, const char *senha){
    operador->id = id;
    strcpy(operador->nome, nome);
    strcpy(operador->usuario, usuario);
    strcpy(operador->senha, senha);
}

void inicializarListaOperadoresSistema(ListaOperadorSistema *lista){
    lista->prox = NULL;
    inicializarOperadoresSistema(&lista->operador);
}

int adicionarOperadoresSistema(ListaOperadorSistema **lista, TipoOperadorSistema operador){
    // aloca o espaco para um novo no'
    ListaOperadorSistema *novo = (ListaOperadorSistema *)malloc(sizeof(ListaOperadorSistema));
    
    // se n conseguir alocar, retorna erro
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->operador = operador;
    novo->prox = *lista;

    // atribui o novo no' como o inicio da lista
    *lista = novo;

    // retorna sucesso
    return 1;
}

int removerOperadoresSistema(ListaOperadorSistema **lista, int id){
    // variaveis auxiliares para percorrer a lista
    ListaOperadorSistema *atual = *lista;
    ListaOperadorSistema *anterior = NULL;

    // percorre a lista ate' encontrar o operador com o id ou o final da lista
    // - se oq eu to olhando n e' nulo e o id atual n e' oq eu quero, avanca
    while(atual != NULL && atual->operador.id != id){
        anterior = atual;
        atual = atual->prox;
    }

    // quando sair do loop, ou achou o operador q eu quero ou chegou no final da lista
    // - se n for nulo, achei o operador
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

    // se chegar aqui, n achei o operador
    return 0;
}

int atualizarOperadoresSistema(ListaOperadorSistema *lista, int id, const char *novoNome, const char *novoUsuario, const char *novaSenha){
    // variavel auxiliar para percorrer a lista
    ListaOperadorSistema *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do operador atual for o id q eu quero, atualiza os dados
        if(atual->operador.id == id){
            strcpy(atual->operador.nome, novoNome);
            strcpy(atual->operador.usuario, novoUsuario);
            strcpy(atual->operador.senha, novaSenha);
            return 1; // retorna sucesso
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