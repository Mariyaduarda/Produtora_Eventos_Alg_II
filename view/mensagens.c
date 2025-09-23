#include "mensagens.h"

// ====================================
// SUCESSO OU FALHA
void printAdicionarSucesso() {
    printf("\n [ Adicionado com sucesso! ]================================[SUCESSO] \n");
}

void printAdicionarFalha() {
    printf("\n [ Falha ao adicionar ]========================================[ERRO] \n");
}

void printRemoverSucesso() {
    printf("\n [ Removido com sucesso! ]==================================[SUCESSO] \n");
}

void printRemoverFalha() {
    printf("\n [ Falha ao remover ]==========================================[ERRO] \n");
}

void printAtualizarSucesso() {
    printf("\n [ Atualizado com sucesso! ]================================[SUCESSO] \n");
}

void printAtualizarFalha() {
    printf("\n [ Falha ao atualizar ]========================================[ERRO] \n");
}

// ====================================
// ERROS
void printListaVazia() {
    printf("\n [ A lista esta vazia ]========================================[ERRO] \n");
}

void printNaoEncontrado() {
    printf("\n [ Nao encontrado ]============================================[ERRO] \n");
}

void printOpcaoInvalida() {
    printf("\n [ Opcao Invalida ]============================================[ERRO] \n");
}

void printValorInvalido() {
    printf("\n [ Valor Invalido ]============================================[ERRO] \n");
}