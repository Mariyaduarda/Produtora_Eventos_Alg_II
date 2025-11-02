#include <stdio.h>
#include <string.h>
#include "fornecedor.h"

void fornecedorInit(TipoFornecedor *fornecedor){
    fornecedor->ativo = true;     // td objeto comeca como ativo
    fornecedor->usa_CNPJ = false; // por padrao usa cpf ao inves de cnpj
    fornecedor->id = 0;           // id vai ser calculado automaticamente
    
    strcpy(fornecedor->nomeFantasia, "");
    strcpy(fornecedor->razaoSocial,  "");
    strcpy(fornecedor->cpf_cnpj,     "");
    strcpy(fornecedor->endereco,     "");
    strcpy(fornecedor->telefone,     "");
    strcpy(fornecedor->tipoServico,  "");
}

void fornecedorListaInit(ListaFornecedor *lista){
    lista->prox = NULL;
    fornecedorInit(&lista->fornecedor);
}

int fornecedorAdicionar(ListaFornecedor **lista, TipoFornecedor fornecedor){
    // aloca o espaco para um novo no'
    ListaFornecedor *novo = (ListaFornecedor *)malloc(sizeof(ListaFornecedor));
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->fornecedor = fornecedor;
    novo->fornecedor.ativo = true;
    novo->prox = NULL;

    
    if(*lista == NULL){ // se a lista estiver vazia, e' so' substituir
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

int fornecedorRemover(ListaFornecedor **lista, int id){
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

int fornecedorAtualizar(ListaFornecedor *lista, TipoFornecedor fornecedorAtualizado, int id){
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

TipoFornecedor* fornecedorBuscar(ListaFornecedor *lista, int id){
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

void fornecedorListaLiberar(ListaFornecedor* lista){
    //auxiliar pra liberar cada no um por um
    ListaFornecedor* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

}

int fornecedorSalvarTXT(ListaFornecedor *lista){
    FILE *fp = fopen("dados/fornecedor.txt", "w");
    if(fp == NULL) return 0;

    if (lista == NULL) { fclose(fp); return 0; }
    ListaFornecedor *atual = lista->prox; // pular nó cabeça
    while(atual != NULL){
        fprintf(fp, "%d;%d;%d;%s;%s;%s;%s;%s;%s\n",
                atual->fornecedor.id,
                atual->fornecedor.ativo,
                atual->fornecedor.usa_CNPJ,
                atual->fornecedor.nomeFantasia,
                atual->fornecedor.razaoSocial,
                atual->fornecedor.cpf_cnpj,
                atual->fornecedor.endereco,
                atual->fornecedor.telefone,
                atual->fornecedor.tipoServico);
        atual = atual->prox;
    }

    fclose(fp);
    return 1;
}

int fornecedorLerTXT(ListaFornecedor **lista) {
    FILE *fp = fopen("dados/fornecedor.txt", "r");
    if(fp == NULL) return 0;

    TipoFornecedor temp;
    
    while(fscanf(fp, "%d;%d;%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
                 &temp.id,
                 &temp.ativo,
                 &temp.usa_CNPJ,
                 temp.nomeFantasia,
                 temp.razaoSocial,
                 temp.cpf_cnpj,
                 temp.endereco,
                 temp.telefone,
                 temp.tipoServico) == 9) { // Verifica se leu todos os 9 campos
        fornecedorAdicionar(lista, temp);
    }

    fclose(fp);
    return 1;
}

int fornecedorSalvarBIN(ListaFornecedor* lista) {
    FILE* fp = fopen("dados/fornecedor.bin", "wb");
    if (fp == NULL) return 0;

    // Aux pra percorrer a lista 
    if (lista == NULL) { fclose(fp); return 0; }
    ListaFornecedor* aux = lista;

    // Percorre a lista escrevendo tudo no binario
    while (aux != NULL) {
        // Escreve um item
        fwrite(&aux->fornecedor, sizeof(TipoFornecedor), 1, fp);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int fornecedorLerBIN(ListaFornecedor** lista) {
    FILE* fp = fopen("dados/fornecedor.bin", "rb");
    if (fp == NULL) return 0;

    TipoFornecedor temp;

    // Le o arquivo binario ate o final
    while (fread(&temp, sizeof(TipoFornecedor), 1, fp) == 1) {
        fornecedorAdicionar(lista, temp);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(fp);
    return 1;
}