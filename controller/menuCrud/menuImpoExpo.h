#ifndef IMPORTACAO_EXPORTACAO_VIEW_H
#define IMPORTACAO_EXPORTACAO_VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========== MENUS ==========
void viewMenuImportacaoExportacao();

// ========== SOLICITAÇÕES DE ENTRADA ==========
void viewSolicitarNomeArquivo(char* nomeArquivo, const char* titulo);

// ========== EXIBIÇÃO DE RESULTADOS ==========
void viewExibirSucessoExportacao(int quantidade, const char* nomeArquivo, const char* tipo);
void viewExibirResultadoImportacao(int resultado, int quantidade, const char* tipo);

// ========== MENSAGENS E CONTROLES ==========
void exibirCabecalhoExportacao(void);
void exibirMensagemSucesso(const char* mensagem);
void exibirMensagemErro(const char* mensagem);
void exibirMensagemInfo(const char* mensagem);
void exibirMensagemProcessando(const char* mensagem);
void exibirResumoExportacao(int totalClientes, int totalFornecedores, 
                           int totalEventos, int totalRecursos, int totalEquipes);
void viewAguardarContinuar(void);

#endif // IMPORTACAO_EXPORTACAO_VIEW_H
