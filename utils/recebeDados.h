#ifndef RECEBE_DADOS_H
#define RECEBE_DADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils_bibliotecas.h"
#include "../view/mensagens.h"


// Funcoes para receber dados do usuario
void recebeString(char *str, int maxTam, char *msg1, char *msg2);
int recebeInt(int min, int max, char *msg1, char *msg2);
float recebeFloat(float min, float max, char *msg1, char *msg2);

// Funcoes com validacao
void recebeCPF(char *str);
void recebeCNPJ(char *str);
void recebeCPFCNPJ(char *str, bool* usa_CNPJ);
void recebeEmail(char *str);
void recebeTelefone(char *str);
int recebeID();

#endif // RECEBE_DADOS_H