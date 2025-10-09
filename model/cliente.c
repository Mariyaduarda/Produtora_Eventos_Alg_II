#include "cliente.h"

void inicializarCliente(TipoCliente *cliente){
    cliente->ativo = true;     // td cliente comeca como ativo
    cliente->usa_CNPJ = false; // por padrao usa cpf ao inves de cnpj
    cliente->id = 0;           // id vai ser calculado automaticamente

    // Atributos comecam vazios pra tirar lixo de memoria
    strcpy(cliente->nome,          "");
    strcpy(cliente->endereco,      "");
    strcpy(cliente->cpf_cnpj,      "");
    strcpy(cliente->telefone,      "");
    strcpy(cliente->email,         "");
    strcpy(cliente->nomeDoContato, "");
}

void inicializarListaCliente(ListaCliente *lista){
    lista->prox = NULL;
    inicializarCliente(&lista->cliente);
}

int adicionarCliente(ListaCliente **lista, TipoCliente cliente){
    // aloca o espaco para um novo no'
    ListaCliente *novo = (ListaCliente *)malloc(sizeof(ListaCliente));
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->cliente = cliente;
    novo->cliente.ativo = true;
    novo->prox = NULL;

    
    if(*lista == NULL){ // se a lista estiver vazia, o novo no' sera o primeiro
        novo->cliente.id = 1;
        *lista = novo;
    } else { // se n estiver vazia, percorre ate' o final da lista

        // variavel auxiliar para percorrer a lista
        ListaCliente *atual = *lista;
        // percorre ate' o final da lista
        while(atual->prox != NULL) atual = atual->prox;

        // atribui o ID do novo no' como o ID do ultimo mais um
        novo->cliente.id = atual->cliente.id + 1;
        // adiciona o novo no' no final da lista
        atual->prox = novo;

    }

    // retorna sucesso
    return 1;

}

int removerCliente(ListaCliente **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaCliente *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do cliente atual for o id q eu quero, marca como inativo
        if(atual->cliente.id == id){
            // marca o cliente como inativo
            atual->cliente.ativo = false;
            return 1;
        }
        atual = atual->prox;

    }

    // se chegar aqui, n achei o cliente
    return 0;
}

int atualizarCliente(ListaCliente *lista, TipoCliente clienteAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaCliente *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do cliente atual for o id q eu quero, atualiza os dados
        if(atual->cliente.id == id){
            atual->cliente = clienteAtualizado;
            atual->cliente.id = id; // garante q o id n vai ser alterado
            return 1; // sucesso
        }
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

        // se o id do cliente atual for o id q eu quero, retorna os dados
        if(atual->cliente.id == id){
            return &atual->cliente;
        }
        atual = atual->prox;
    }

    // se chegar aqui, n achei o cliente
    return NULL;
}

void liberarListaCliente(ListaCliente* lista){
    //auxiliar pra liberar cada no um por um
    ListaCliente* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

}