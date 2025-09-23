#ifndef MENSAGENS_H
#define MENSAGENS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sucesso ou falha
void printAdicionarSucesso();
void printAdicionarFalha();
void printRemoverSucesso();
void printRemoverFalha();
void printAtualizarSucesso();
void printAtualizarFalha();

// erros
void printOpcaoInvalida();
void printListaVazia();
void printNaoEncontrado();
void printValorInvalido();

// gen
void printMensagem(char *msg1, char *msg2);
int printConfirma();

#endif // MENSAGENS_H