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

void formataCPF(char *cpf, char *dest) {
    // formata a string como se fosse um cpf
    //  presupoe que ja e' um cpf
    sprintf(dest, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
}

void formataCNPJ(char *cnpj, char *dest) {
    // formata a string como se fosse um cnpj
    //  presupoe que ja e' um cnpj
    sprintf(dest, "%.2s.%.3s.%.3s/%.4s-%.2s", cnpj, cnpj + 2, cnpj + 5, cnpj + 8, cnpj + 12);
}

void formataTelefone(char *numero, char *dest) {
    // formata a string como se fosse um numero de telefone
    //  presupoe que ja e' so' numeros

    if (strlen(numero) == 11) {
        // 11987654321 vira (11) 98765-4321
        sprintf(dest, "(%.2s) %.5s-%.4s", numero, numero+2, numero+7);
    } 
    else if (strlen(numero) == 10) {
        // 1134567890 vira (11) 3456-7890
        sprintf(dest, "(%.2s) %.4s-%.4s", numero, numero+2, numero+6);
    }
    else if (strlen(numero) == 8) {
        // 34567890 vira 3456-7890
        sprintf(dest, "%.4s-%.4s", numero, numero+4);
    }
    else {
        // se n segue nenhum desses padroes, so copia a original
        strcpy(dest, numero);
    }
}