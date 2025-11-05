#ifndef UTILS_TELA_H
#define UTILS_TELA_H
#include <stdio.h>

// Funcoes de utilidade para mudar a tela
void limparTela();
void esperaEnter();

void formataCPF(char *cpf, char *dest);
void formataCNPJ(char *cnpj, char *dest);
void formataTelefone(char *numero, char *dest);

#endif //UTILS_TELA_H