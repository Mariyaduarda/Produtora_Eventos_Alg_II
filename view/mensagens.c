#include "mensagens.h"

// ====================================
// SUCESSO OU FALHA
void printAdicionarSucesso() {
    printMensagem("Adicionado com sucesso","#");
}

void printAdicionarFalha() {
    printMensagem("Falha ao adicionar","ERRO");
}

void printRemoverSucesso() {
    printMensagem("Removido com sucesso","#");
}

void printRemoverFalha() {
    printMensagem("Falha ao remover","ERRO");
}

void printAtualizarSucesso() {
    printMensagem("Atualizado com sucesso","#");
}

void printAtualizarFalha() {
    printMensagem("Falha ao atualizar","ERRO");
}

// ====================================
// ERROS
void printListaVazia() {
    printMensagem("A lista esta vazia","ERRO");
}

void printNaoEncontrado() {
    printMensagem("Nao encontrado","ERRO");
}

void printOpcaoInvalida() {
    printMensagem("Opcao Invalida","ERRO");
}

void printValorInvalido() {
    printMensagem("Valor invalido","ERRO");
}

// ====================================
// OUTROS
void printMensagem(char *msg1, char *msg2){
    //printa msg no seguinte formato, com 70 chars no total
    // " [msg1]========================[msg2] "
    int total = 70;
    int tam1 = strlen(msg1);
    int tam2 = strlen(msg2);

    // Calcula quantos '=' vai ser colocado
    int n = total - tam1 - tam2 - 11;
    if (n<0) n = 0;

    printf("\n [ %s ]",msg1);                 //msg 1
    for (int i=0 ; i<=n ; i++) printf("="); // =
    printf("[ %s ] ",msg2);                 //msg 2
}