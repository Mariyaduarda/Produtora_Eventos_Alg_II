#include <stdio.h>
// Funcoes de utilidade para mudar a tela

void limparTela() {
    // Limpa a tela do console
    printf("\e[1;1H\e[2J");
}

void opcaoInvalida() {
    // para quando o usuario digitar uma opcao invalida
    limparTela();
    printf("\n => Opcao invalida! Tente novamente");
    while (getchar() != '\n' && getchar() != EOF);
}

void esperaEnter() {
    // Espera o usuario apertar enter
    printf("\n => Pressione ENTER para continuar...");
    while (getchar() != '\n' && getchar() != EOF);
}