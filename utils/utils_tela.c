#include "utils_bibliotecas.h"

// Funcoes de utilidade para mudar a tela

void limparTela() {
    // Limpa a tela do console
    printf("\e[1;1H\e[2J");
}

void esperaEnter() {
    // Espera o usuario apertar enter
    while (getchar() != '\n' && getchar() != EOF);
}

// Funcoes de formatacao

void formataCPF(const char *cpf, char *dest) {
    // formata a string como se fosse um cpf
    //  presupoe que ja e' um cpf
    sprintf(dest, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
}

void formataCNPJ(const char *cnpj, char *dest) {
    // formata a string como se fosse um cnpj
    //  presupoe que ja e' um cnpj
    sprintf(dest, "%.2s.%.3s.%.3s/%.4s-%.2s", cnpj, cnpj + 2, cnpj + 5, cnpj + 8, cnpj + 12);
}