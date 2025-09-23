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

    printf(" [ %s ]",msg1);                 //msg 1
    for (int i=0 ; i<=n ; i++) printf("="); // =
    printf("[ %s ] ",msg2);                 //msg 2
}

int printConfirma(){
    // guarda a escolha
    int confirma; 

    // Enquanto usuario n digitar 1 ou 0, fica perguntando
    do{
        printMensagem("Voce tem certeza?", "1.Sim | 0.Nao");
        scanf("%d",&confirma);
        getchar(); // Limpa o buffer do teclado

    }while ( confirma != 1 && confirma != 0);
    
    //retorna a escolha
    return confirma;
}