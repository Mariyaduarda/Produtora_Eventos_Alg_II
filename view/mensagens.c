#include "mensagens.h"
#include "../utils/utils_tela.h"

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

void viewMenuImportacaoExportacao() {
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Importacao e Exportacao de Dados                               |"
        "\n |==================================================================|"
        "\n |   1. Exportar Dados                                              |"
        "\n |   2. Importar Dados                                              |"
        "\n |==================================================================|"
        "\n |   0. Voltar                                                      |"
        "\n======================================================================"
    );
}

void viewSolicitarNomeArquivo(char* nomeArquivo, const char* titulo) {
    printf("\n%s\n", titulo);
    printf("Digite o nome do arquivo (sem extensao): ");
    fgets(nomeArquivo, 256, stdin);
    nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;
}

void exibirMensagemInfo(const char* mensagem) {
    printf("\n[INFO] %s\n", mensagem);
}

void exibirMensagemProcessando(const char* mensagem) {
    printf("\n[PROCESSANDO] %s\n", mensagem);
}

void exibirMensagemSucesso(const char* mensagem) {
    printf("\n[SUCESSO] %s\n", mensagem);
}

void exibirMensagemErro(const char* mensagem) {
    printf("\n[ERRO] %s\n", mensagem);
}

void viewAguardarContinuar(void) {
    printf("\nPressione ENTER para continuar...");
    getchar();
}