#include <stdio.h>
#include <string.h>
#include "operador.h"

void operadorInit(TipoOperador *operador){
    operador->ativo = true;
    operador->id = 0;
    strcpy(operador->nome, "");
    strcpy(operador->usuario, "");
    strcpy(operador->senha, "");
}

void operadorListaInit(ListaOperador *lista){
    lista->prox = NULL;
    operadorInit(&lista->operador);
}

int operadorAdicionar(ListaOperador **lista, TipoOperador operador){
    // aloca o espaco para um novo no'
    ListaOperador *novo = (ListaOperador *)malloc(sizeof(ListaOperador));
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->operador = operador;
    novo->operador.ativo = true;
    novo->prox = NULL;
    
    if(*lista == NULL){ // se a lista estiver vazia, e' so' substituir
        novo->operador.id = 1;
        *lista = novo;
    } else { // se n estiver vazia, percorre ate' o final da lista

        // variavel auxiliar para percorrer a lista
        ListaOperador *atual = *lista;
        // percorre ate' o final da lista
        while(atual->prox != NULL) atual = atual->prox;

        // atribui o ID do novo no' como o ID do ultimo mais um
        novo->operador.id = atual->operador.id + 1;
        // adiciona o novo no' no final da lista
        atual->prox = novo;

    }

    // retorna sucesso
    return 1;
}

int operadorRemover(ListaOperador **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaOperador *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do operador atual for o id q eu quero, marca como inativo
        if(atual->operador.id == id){
            // marca o operador como inativo
            atual->operador.ativo = false;
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o operador
    return 0;
}

int operadorAtualizar(ListaOperador *lista, TipoOperador operadorAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaOperador *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do operador atual for o id q eu quero, atualiza os dados
        if(atual->operador.id == id){
            atual->operador = operadorAtualizado;
            atual->operador.id = id; // garante q o id n vai ser alterado
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o operador
    return 0;
}

TipoOperador* operadorBuscar(ListaOperador *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaOperador *atual = lista;

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

void operadorListaLiberar(ListaOperador* lista){
    //auxiliar pra liberar cada no um por um
    ListaOperador* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

}

//==================================================
// Arquivos

int operadorSalvarTXT(ListaOperador *lista){
    // Abre o arquivo em um ponteiro de arquivo
    FILE* fp = fopen("dados/operador.txt", "w");

    // Confere se deu erro
    if(fp == NULL) return 0;

    // Aux pra percorrer a lista 
    if (lista == NULL) { fclose(fp); return 0; }
    ListaOperador* aux = lista; // primeiro elemento

    // Percorre a lista printando tudo no txt
    while (aux != NULL) {
        // Printa um item
        fprintf(fp, "%d,%d,%s,%s,%s\n",
        aux->operador.ativo,
        aux->operador.id,
        aux->operador.nome,
        aux->operador.usuario,
        aux->operador.senha);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int operadorLerTXT(ListaOperador **lista) {
    FILE *fp = fopen("dados/operador.txt", "r");
    if(fp == NULL) return 0;

    TipoOperador operadorTemp;
    
    while (fscanf(fp, "%d,%d,%99[^,],%49[^,],%49[^\n]\n",
                  (int*)&operadorTemp.ativo,
                  &operadorTemp.id,
                  operadorTemp.nome,
                  operadorTemp.usuario,
                  operadorTemp.senha) == 5) {
        // Adiciona o operador lido na lista
        operadorAdicionar(lista, operadorTemp);
    }

    // Fecha o arquivo e retorna sucesso
    fclose(fp);
    return 1;
}


int operadorSalvarBIN(ListaOperador* lista) {
    FILE* fp = fopen("dados/operador.bin", "wb");
    if (fp == NULL) return 0;

    // Aux pra percorrer a lista 
    if (lista == NULL) { fclose(fp); return 0; }
    ListaOperador* aux = lista;

    // Percorre a lista escrevendo tudo no binario
    while (aux != NULL) {
        // Escreve um item
        fwrite(&aux->operador, sizeof(TipoOperador), 1, fp);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int operadorLerBIN(ListaOperador** lista) {
    FILE* fp = fopen("dados/operador.bin", "rb");
    if (fp == NULL) return 0;

    TipoOperador temp;

    // Le o arquivo binario ate o final
    while (fread(&temp, sizeof(TipoOperador), 1, fp) == 1) {
        operadorAdicionar(lista, temp);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(fp);
    return 1;
}