#ifndef UTILS_TELA_H
#define UTILS_TELA_H
#include <stdio.h>

// Funcoes de utilidade para mudar a tela
void limparTela();
void esperaEnter();

void formataCPFouCNPJ(char *str, char *dest);
void formataTelefone(char *numero, char *dest);

#endif //UTILS_TELA_H