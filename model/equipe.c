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

    
    if(*lista == NULL){ // se a lista estiver vazia, e' so' substituir
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

    // Aux pra percorrer a lista 
    if (lista == NULL) { fclose(fp); return 0; }
    ListaEquipe* aux = lista;

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

int equipeLerTXT(ListaEquipe **lista) {
    FILE *fp = fopen("dados/equipe.txt", "r");
    if(fp == NULL) return 0;

    TipoEquipe temp;
    // como nao tem assinatura de bool, le como int e atribui depois
    int ativoTemp;
    
    while (fscanf(fp, "%d,%d,%[^,],%[^,],%[^,],%f\n",
        &ativoTemp,
        &temp.id,
        temp.nome,
        temp.cpf,
        temp.funcao,
        &temp.valorDiariaHora) == 6)
    {
        // atribui os booleanos
        temp.ativo = ativoTemp;
        
        //adiciona na lista
        equipeAdicionar(lista, temp);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(fp);
    return 1;
}

int equipeSalvarBIN(ListaEquipe* lista) {
    FILE* fp = fopen("dados/equipe.bin", "wb");
    if (fp == NULL) return 0;

    // Aux pra percorrer a lista 
    if (lista == NULL) { fclose(fp); return 0; }
    ListaEquipe* aux = lista;

    // Percorre a lista escrevendo tudo no binario
    while (aux != NULL) {
        // Escreve um item
        fwrite(&aux->equipe, sizeof(TipoEquipe), 1, fp);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int equipeLerBIN(ListaEquipe** lista) {
    FILE* fp = fopen("dados/equipe.bin", "rb");
    if (fp == NULL) return 0;

    TipoEquipe temp;

    // Le o arquivo binario ate o final
    while (fread(&temp, sizeof(TipoEquipe), 1, fp) == 1) {
        equipeAdicionar(lista, temp);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(fp);
    return 1;
}