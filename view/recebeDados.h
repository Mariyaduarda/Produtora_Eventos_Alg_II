#ifndef RECEBE_DADOS_H
#define RECEBE_DADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mensagens.h"


//Funcoes para receber dados do usuario
void recebeString(char *str, int maxTam, char *msg1, char *msg2);
int recebeInt(int min, int max, char *msg1, char *msg2);

//VELHOS
int recebeID();
void recebeNome(char *nome, int maxTam);
void recebeCPF(char *cpf);
void recebeCNPJ(char *cnpj);
void recebeTelefone(char *telefone);
void recebeEmail(char *email, int maxTam);
void recebeNomeDoContato(char *nomeDoContato, int maxTam);
void recebeFuncao(char *funcao, int maxTam);
float recebeValorDiaria();
float recebeValorHora();
void recebeNomeFantasia(char *nomeFantasia, int maxTam);
void recebeRazaoSocial(char *razaoSocial, int maxTam);
void recebeEndereco(char *endereco, int maxTam);
void recebeTipoServico(char *tipoServico, int maxTam);
void recebeNomeUsuario(char *nomeUsuario, int maxTam);
void recebeSenha(char *senha, int maxTam);
void recebeInscricaoEstadual(char *inscricaoEstadual);
float recebeMargemDeLucro();
void recebeDescricao(char *descricao, int maxTam);
void recebeCategoria(char *categoria, int maxTam);
int recebeQuantidadeEstoque();
float recebePrecoCusto();
float recebeValorLocacao();

#endif // RECEBE_DADOS_H