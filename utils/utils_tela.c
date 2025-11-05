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
    //  presupoe que ja e' so' numeros

    if (strlen(cpf) == 11){ // se tem o num certo de caracteres
        sprintf(dest, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
    } else{ // caso contrario, so' retorna ele normal
        strcpy(dest, cpf);
    }
}

void formataCNPJ(char *cnpj, char *dest) {
    // formata a string como se fosse um cnpj
    //  presupoe que ja e' so' numeros

    if (strlen(cnpj) == 11){ // se tem o num certo de caracteres
        sprintf(dest, "%.2s.%.3s.%.3s/%.4s-%.2s", cnpj, cnpj + 2, cnpj + 5, cnpj + 8, cnpj + 12);
    } else{ // caso contrario, so' retorna ele normal
        strcpy(dest, cnpj);
    }
}

void formataTelefone(char *numero, char *dest) {
    // formata a string como se fosse um numero de telefone
    //  presupoe que ja e' so' numeros

    if (strlen(numero) == 11) {
        // 12345678901 vira (12) 34567-8901
        sprintf(dest, "(%.2s) %.5s-%.4s", numero, numero + 2, numero + 7);
    } 
    else if (strlen(numero) == 10) {
        // 1234567890 vira (12) 3456-7890
        sprintf(dest, "(%.2s) %.4s-%.4s", numero, numero + 2, numero + 6);
    }
    else if (strlen(numero) == 9) {
        // 123456789 vira 12345-6789
        sprintf(dest, "%.5s-%.4s", numero, numero + 5);
    }
    else if (strlen(numero) == 8) {
        // 12345678 vira 1234-5678
        sprintf(dest, "%.4s-%.4s", numero, numero + 4);
    }
    else { // caso contrario, so' retorna ele normal
        strcpy(dest, numero);
    }
}