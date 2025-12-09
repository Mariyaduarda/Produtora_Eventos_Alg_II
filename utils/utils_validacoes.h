#ifndef UTILS_VALIDACOES_H
#define UTILS_VALIDACOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

bool validarCPF(const char *cpf_cnpj);
bool validarCNPJ(const char *cpf_cnpj);
bool validarCPF_CNPJ(const char *documento, bool usa_CPF);

bool validarEmail(const char *email);
bool validarTelefone(const char *telefone);
bool validarNome(const char *nome);
bool validarSenha(const char *senha);
bool validarUsuario(const char *usuario);

int validaCodigo(int codigo);

// ====== VALIDACAO DE DATA=====
// metodo de ano bissexto para incluir ao validar data
int ehBissexto(int ano);
bool validarData(const char *dataStr);
#endif //UTILS_VALIDACOES_H