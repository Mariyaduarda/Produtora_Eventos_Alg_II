//
// Created by alunos on 07/10/2025.
//

#ifndef UTILS_BIBLIOTECAS_H
#define UTILS_BIBLIOTECAS_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "../model/cliente.h"

// Funcoes de validar dados
bool validarCPF(const char *cpf_cpnj);
bool validarCNPJ(const char *cpf_cpnj);
bool validarEmail(const char *email);
bool validarTelefone(const char *telefone);
bool validarNome(const char *nome);
bool validarSenha(const char *senha);
bool validarUsuario(const char *usuario);
int validarDadosCliente(TipoCliente *cliente, char *mensagemErro);
int validaCodigo(int codigo);
int ehBissexto(int ano);
bool validarData(const char *dataStr);

// Funcoes de utilidade para mudar a tela
void limparTela();
void esperaEnter();

#endif //UTILS_BIBLIOTECAS_H