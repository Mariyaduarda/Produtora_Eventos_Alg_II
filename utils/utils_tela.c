#include <stdio.h>
// Funcoes de utilidade para mudar a tela

void limparTela() {
    // Limpa a tela do console
    printf("\e[1;1H\e[2J");
}

void esperaEnter() {
    // Espera o usuario apertar enter
    while (getchar() != '\n' && getchar() != EOF);
}