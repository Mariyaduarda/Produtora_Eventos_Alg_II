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

void formataCPFouCNPJ(char *str, char *dest) {
    // formata a string como se fosse um cpf
    //  presupoe que ja e' so' numeros e e' um cpf ou cnpj

    if (strlen(str) == 11){ 
        // se tem caracteres pra ser cpf
        sprintf(dest, "%.3s.%.3s.%.3s-%.2s", str, str + 3, str + 6, str + 9);
    } else if (strlen(str) == 14){ 
        // se tem caracteres pra ser cnpj
        sprintf(dest, "%.2s.%.3s.%.3s/%.4s-%.2s", str, str + 2, str + 5, str + 8, str + 12);
    } else{ 
        // caso contrario, so' retorna ele normal
        strcpy(dest, str);
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