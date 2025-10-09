#include "equipe.h"

void inicializarEquipe(TipoEquipe *equipe){
    equipe->ativo = true;
    equipe->id = 0;
    strcpy(equipe->nome, "");
    strcpy(equipe->cpf, "");
    strcpy(equipe->funcao, "");
    equipe->valorDiariaHora = 0.0;
}

void inicializarListaEquipe(ListaEquipe *lista){
    lista->prox = NULL;
    inicializarEquipe(&lista->equipe);
}

int adicionarEquipe(ListaEquipe **lista, TipoEquipe equipe){
    // aloca o espaco para um novo no'
    ListaEquipe *novo = (ListaEquipe *)malloc(sizeof(ListaEquipe));
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->equipe = equipe;
    novo->equipe.ativo = true;
    novo->prox = NULL;

    
    if(*lista == NULL){ // se a lista estiver vazia, o novo no' sera o primeiro
        novo->equipe.id = 1;
        *lista = novo;
    } else { // se n estiver vazia, percorre ate' o final da lista

        // variavel auxiliar para percorrer a lista
        ListaEquipe *atual = *lista;
        // percorre ate' o final da lista
        while(atual->prox != NULL) atual = atual->prox;

        // atribui o ID do novo no' como o ID do ultimo mais um
        novo->equipe.id = atual->equipe.id + 1;
        // adiciona o novo no' no final da lista
        atual->prox = novo;

    }

    // retorna sucesso
    return 1;

}

int removerEquipe(ListaEquipe **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaEquipe *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do cliente atual for o id q eu quero, marca como inativo
        if(atual->equipe.id == id){
            // marca o cliente como inativo
            atual->equipe.ativo = false;
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o cliente
    return 0;
}

int atualizarEquipe(ListaEquipe *lista, TipoEquipe equipeAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaEquipe *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do cliente atual for o id q eu quero, atualiza os dados
        if(atual->equipe.id == id){
            atual->equipe = equipeAtualizado;
            atual->equipe.id = id; // garante q o id n vai ser alterado
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o cliente
    return 0;
}

TipoEquipe* buscarEquipe(ListaEquipe *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaEquipe *atual = lista;

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

void liberarListaEquipe(ListaEquipe* lista){
    //auxiliar pra liberar cada no um por um
    ListaEquipe* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

}