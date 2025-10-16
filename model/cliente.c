#include "cliente.h"

void clienteInit(TipoCliente *cliente){
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

void clienteListaInit(ListaCliente *lista){
    lista->prox = NULL;
    clienteInit(&lista->cliente);
}

int clienteAdicionar(ListaCliente **lista, TipoCliente cliente){
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

int clienteRemover(ListaCliente **lista, int id){
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

int clienteAtualizar(ListaCliente *lista, TipoCliente clienteAtualizado, int id){
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

TipoCliente* clienteBuscar(ListaCliente *lista, int id){
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

void clienteListaLiberar(ListaCliente* lista){
    //auxiliar pra liberar cada no um por um
    ListaCliente* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

}

//==================================================
// Arquivos

int clienteSalvarTXT(ListaCliente *lista){
    // Abre o arquivo em um ponteiro de arquivo
    FILE* fp = fopen("dados/cliente.txt", "w");

    // Confere se deu erro
    if (fp == NULL) {
        // N conseguiu abrir o arquivo
        return 0;
    }

    // Aux pra percorrer a lista, tem q pular o no' cabeca
    ListaCliente* aux = lista->prox->prox;

    // Percorre a lista printando tudo no txt
    while (aux != NULL) {
        // Printa um item
        fprintf(fp, "%d,%d,%d,%s,%s,%s,%s,%s,%s\n",
        aux->cliente.ativo,
        aux->cliente.id,
        aux->cliente.usa_CNPJ,
        aux->cliente.nome,
        aux->cliente.endereco,
        aux->cliente.cpf_cnpj,
        aux->cliente.telefone,
        aux->cliente.email,
        aux->cliente.nomeDoContato);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int clienteLerTXT(ListaCliente *lista) {
    // Abre o arquivo ou retorna erro se n deu
    FILE *file = fopen("dados/cliente.txt", "r");
    if (file == NULL) return 0;

    // Cliente temporario pra guardar os dados lidos
    TipoCliente temp;

    // le cada linha do arquivo, enquanto n chegar no final, n para de ler
    while (fscanf(file, "%d,%d,%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
                  &temp.ativo,
                  &temp.id,
                  &temp.usa_CNPJ,
                  temp.nome,
                  temp.endereco,
                  temp.cpf_cnpj,
                  temp.telefone,
                  temp.email,
                  temp.nomeDoContato) != EOF) {
        // Adiciona o cliente na lista
        clienteAdicionar(&lista, temp);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(file);
    return 1;
}