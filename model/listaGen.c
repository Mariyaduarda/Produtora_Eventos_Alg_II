#include "listaGen.h"

// AINDA TESTANDO


// Inicializa uma lista
// - define ela como NULL pra ser vazia
void inicializarLista(No **lista) {
    *lista = NULL;
}

// Adicionar Elemento
// - dado    -> seria o tipo de dado    | 'TipoCliente' por exemplo
// - tamanho -> seria o tamanho do dado | 'sizeof(TipoCliente)' por exemplo
int adicionarElemento(No **lista, void *dado, size_t tamanho) {
    
    //=====================================================
    // ALOCACAO

    //  Precisa de alocar separado o no' e o conteudo, pois o tipo 'no'
    // nao contem os dados no seu tamanho, so' tem o ponteiro

    // aloca memoria pro novo no'
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return 0; // se deu ruim, retorna erro

    // aloca memoria pros dados do novo no'
    novo->dado = malloc(tamanho);
    if (novo->dado == NULL) {
        free(novo); // se deu ruim, libera memoria q deu certo e retorna erro
        return 0;
    }

    //=====================================================
    // ATRIBUICAO DE DADOS

    // Pega os dados de 'dado' e passa pro novo no'
    // memcpy( DESTINO , ORIGEM , TAMANHO DO Q EU VOU MOVER)
    memcpy(novo->dado, dado, tamanho);

    // Define ele como ativo e proximo como nulo
    // - Todo novo no' vai ter esses atributos
    novo->ativo = true;
    novo->prox = NULL;

    //=====================================================
    // INSERCAO NA LISTA

    // Se a lista estiver vazia, esse no' e' o primeiro!
    if (*lista == NULL) { 
        novo->id = 1;
        *lista = novo;
    } else {
        // Se a lista nao estiver, percorre ate' o ultimo no'
        No *atual = *lista;
        while (atual->prox != NULL) atual = atual->prox;

        // Novo ID vai ser o ultimo +1
        novo->id = atual->id + 1;
        atual->prox = novo;
    }

    // se ate agr n deu erro, retorna 1 pra Sucesso!
    return 1;
}

// Remover Elemento
// Funciona basicamente igual como os outros funcionavam antigamente
int removerElemento(No *lista, int id) {
    // variavel auxiliar pra percorrer a lista
    No *atual = lista;

    // enquanto n chegar no final, vai percorrendo a lista
    while (atual != NULL) {
        // Se achei o id q eu procuro, marco ele como inativo e retorna sucesso
        if (atual->id == id) {
            atual->ativo = false;
            return 1;
        }

        // Avanca
        atual = atual->prox;
    }

    // Se chegou aqui, e' pq n tem esse ID
    return 0;
}

// Atualizar Elemento
// Funciona bem parecido como funcionava antes
int atualizarElemento(No *lista, int id, void *novoDado, size_t tamanho) {
    // variavel auxiliar pra percorrer a lista
    No *atual = lista;
    
    // enquanto n chegar no final, vai percorrendo a lista
    while (atual != NULL) {
        // Se achei o id q eu procuro, copia os dados de 'novoDado' para dados do atual
        if (atual->id == id) {
            memcpy(atual->dado, novoDado, tamanho);
            return 1;
        }

        // Avanca
        atual = atual->prox;
    }

    // Se chegou aqui, e' pq n tem esse ID
    return 0;
}

// Buscar Elemento
// Mesmo role, vai percorrer a lista procurando um id
//  mas dessa vez posso so retornar quando achaar
void* buscarElemento(No *lista, int id) {
    // variavel auxiliar pra percorrer a lista
    No *atual = lista;
    
    // enquanto n chegar no final, vai percorrendo a lista
    while (atual != NULL) {
        // Se achei o id q eu procuro, retorna os dados
        if (atual->id == id) {
            return atual->dado;
        }

        // Avanca
        atual = atual->prox;
    }

    // Se chegou aqui, e' pq n tem esse ID
    return 0;
}
