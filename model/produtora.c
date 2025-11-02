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

    
    if(*lista == NULL){ // se a lista estiver vazia, e' so' substituir
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

//==================================================
// Arquivos

int produtoraSalvarTXT(ListaProdutora *lista){
    // Abre o arquivo em um ponteiro de arquivo
    FILE* fp = fopen("dados/produtora.txt", "w");

    // Confere se deu erro
    if(fp == NULL) return 0;

    // Aux pra percorrer a lista 
    if (lista == NULL) { fclose(fp); return 0; }
    ListaProdutora* aux = lista->prox; // primeiro elemento real

    // Percorre a lista printando tudo no txt
    while (aux != NULL) {
        // Printa um item
        fprintf(fp, "%d,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%.2f\n",
        aux->produtora.ativo,
        aux->produtora.id,
        aux->produtora.nomeFantasia,
        aux->produtora.razaoSocial,
        aux->produtora.inscricaoEstadual,
        aux->produtora.cnpj,
        aux->produtora.endereco,
        aux->produtora.telefone,
        aux->produtora.email,
        aux->produtora.nomeDoResponsavel,
        aux->produtora.telefoneDoResponsavel,
        aux->produtora.margemDeLucro);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int produtoraLerTXT(ListaProdutora **lista) {
    FILE *fp = fopen("dados/produtora.txt", "r");
    if(fp == NULL) return 0;

    TipoProdutora temp;
    
    while(fscanf(fp, "%d,%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%f",
                 &temp.ativo,
                 &temp.id,
                 temp.nomeFantasia,
                 temp.razaoSocial,
                 temp.inscricaoEstadual,
                 temp.cnpj,
                 temp.endereco,
                 temp.telefone,
                 temp.email,
                 temp.nomeDoResponsavel,
                 temp.telefoneDoResponsavel,
                 &temp.margemDeLucro) == 12) {
        produtoraAdicionar(lista, temp);
    }
    
    fclose(fp);
    return 1;
}


int produtoraSalvarBIN(ListaProdutora* lista) {
    FILE* fp = fopen("dados/produtora.bin", "wb");
    if (fp == NULL) return 0;

    // Aux pra percorrer a lista 
    if (lista == NULL) { fclose(fp); return 0; }
    ListaProdutora* aux = lista;

    // Percorre a lista escrevendo tudo no binario
    while (aux != NULL) {
        // Escreve um item
        fwrite(&aux->produtora, sizeof(TipoProdutora), 1, fp);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int produtoraLerBIN(ListaProdutora** lista) {
    FILE* fp = fopen("dados/produtora.bin", "rb");
    if (fp == NULL) return 0;

    TipoProdutora temp;

    // Le o arquivo binario ate o final
    while (fread(&temp, sizeof(TipoProdutora), 1, fp) == 1) {
        produtoraAdicionar(lista, temp);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(fp);
    return 1;
}