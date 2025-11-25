#ifndef RECEBE_DADOS_H
#define RECEBE_DADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils_bibliotecas.h"
#include "../view/mensagens.h"


// Funcoes para receber dados do usuario
void recebeString(char *str, int maxTam, char *msg1, char *msg2, bool validacao);
int recebeInt(int min, int max, char *msg1, char *msg2, bool validacao);
float recebeFloat(float min, float max, char *msg1, char *msg2, bool validacao);

// Funcoes com validacao
void recebeCPF(char *str, bool validacao);
void recebeCNPJ(char *str, bool validacao);
void recebeCPFCNPJ(char *str, bool* usa_CNPJ, bool validacao);
void recebeEmail(char *str, bool validacao);
void recebeTelefone(char *str, bool validacao);
int recebeID(bool validacao);
void recebeData(char *dataStr, bool validacao);


#endif // RECEBE_DADOS_H