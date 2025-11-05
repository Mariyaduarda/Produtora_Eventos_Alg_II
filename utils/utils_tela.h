#ifndef UTILS_TELA_H
#define UTILS_TELA_H
#include <stdio.h>

// Funcoes de utilidade para mudar a tela
void limparTela();
void esperaEnter();

void formataCPF(const char *cpf, char *dest);
void formataCNPJ(const char *cnpj, char *dest);

#endif //UTILS_TELA_H