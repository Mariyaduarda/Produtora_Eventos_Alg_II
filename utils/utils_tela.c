#include <stdio.h>
// Funcoes de utilidade para mudar a tela

void LimparTela(){
    // funcao limpa a tela
    printf("\e[1;1H\e[2J");
}