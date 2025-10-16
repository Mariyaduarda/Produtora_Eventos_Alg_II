#include "equipe.h"

void equipeInit(TipoEquipe *equipe){
    equipe->ativo = true;
    equipe->id = 0;
    strcpy(equipe->nome, "");
    strcpy(equipe->cpf, "");
    strcpy(equipe->funcao, "");
    equipe->valorDiariaHora = 0.0;
}

void equipeListaInit(ListaEquipe *lista){
    lista->prox = NULL;
    equipeInit(&lista->equipe);
}

int equipeAdicionar(ListaEquipe **lista, TipoEquipe equipe){
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

int equipeRemover(ListaEquipe **lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaEquipe *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do equipe atual for o id q eu quero, marca como inativo
        if(atual->equipe.id == id){
            // marca o equipe como inativo
            atual->equipe.ativo = false;
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o equipe
    return 0;
}

int equipeAtualizar(ListaEquipe *lista, TipoEquipe equipeAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaEquipe *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do equipe atual for o id q eu quero, atualiza os dados
        if(atual->equipe.id == id){
            atual->equipe = equipeAtualizado;
            atual->equipe.id = id; // garante q o id n vai ser alterado
            return 1; // sucesso
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o equipe
    return 0;
}

TipoEquipe* equipeBuscar(ListaEquipe *lista, int id){
    // variavel auxiliar para percorrer a lista
    ListaEquipe *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do equipe atual for o id q eu quero, retorna os dados
        if(atual->equipe.id == id){
            return &atual->equipe;
        }
        
        // avanca
        atual = atual->prox;
    }

    // se chegar aqui, n achei o equipe
    return NULL;
}

void equipeListaLiberar(ListaEquipe* lista){
    //auxiliar pra liberar cada no um por um
    ListaEquipe* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

}


//==================================================
// Arquivos

int equipeSalvarTXT(ListaEquipe *lista){
    // Abre o arquivo em um ponteiro de arquivo
    FILE* fp = fopen("dados/equipe.txt", "w");

    // Confere se deu erro
    if (fp == NULL) {
        // N conseguiu abrir o arquivo
        return 0;
    }

    // Aux pra percorrer a lista, tem q pular o no' cabeca
    ListaEquipe* aux = lista->prox->prox;

    // Percorre a lista printando tudo no txt
    while (aux != NULL) {
        // Printa um item
        fprintf(fp, "%d,%d,%s,%s,%s,%f\n",
        aux->equipe.ativo,
        aux->equipe.id,
        aux->equipe.nome,
        aux->equipe.cpf,
        aux->equipe.funcao,
        aux->equipe.valorDiariaHora);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int equipeLerTXT(ListaEquipe *lista) {
    // Abre o arquivo ou retorna erro se n deu
    FILE *file = fopen("dados/equipe.txt", "r");
    if (file == NULL) return 0;

    // equipe temporario pra guardar os dados lidos
    TipoEquipe temp;

    // le cada linha do arquivo, enquanto n chegar no final, n para de ler
    while (fscanf(file, "%d,%d,%[^,],%[^,],%[^,],%f\n",
        &temp.ativo,
        &temp.id,
        temp.nome,
        temp.cpf,
        temp.funcao,
        &temp.valorDiariaHora) == 6) {
        // Adiciona o equipe na lista
        equipeAdicionar(lista, temp);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(file);
    return 1;
}