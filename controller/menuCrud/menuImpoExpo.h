/*
 * View de Importação/Exportação - Sistema de Controle Gerencial
 * Disciplina: Algoritmos II
 * 
 * Responsável pela interface com o usuário nas operações de importação/exportação
 */

#ifndef IMPORTACAO_EXPORTACAO_VIEW_H
#define IMPORTACAO_EXPORTACAO_VIEW_H

#include "../../model/cliente.h"
#include "../../model/fornecedor.h"
#include "../../model/evento.h"
#include "../../model/recurso.h"
#include "../../model/equipe.h"

#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"
#include "../../view/mensagens.h"

#include "../../view/printMenu.h"
#include "../../view/mostrarItem.h"

// ========== MENUS ==========
int viewMenuImportacaoExportacao();

// ========== SOLICITAÇÕES DE ENTRADA ==========
int viewSolicitarOpcoesExportacao(int* exportarCli, int* exportarForn, 
                                   int* exportarEv, int* exportarRec, 
                                   int* exportarEquip);

void viewSolicitarNomeArquivo(char* nomeArquivo, const char* titulo);

int viewSolicitarOpcaoImportacao();

// ========== EXIBIÇÃO DE RESULTADOS ==========
void viewExibirSucessoExportacao(int quantidade, const char* nomeArquivo, const char* tipo);

void viewExibirResultadoImportacao(int resultado, int quantidade, const char* tipo);

// ========== MENSAGENS E CONTROLES ==========
void exibirCabecalhoExportacao();

void exibirMensagemSucesso(const char* mensagem);

void exibirMensagemErro(const char* mensagem);

void exibirMensagemInfo(const char* mensagem);

void exibirMensagemProcessando(const char* mensagem);

void exibirResumoExportacao(int totalClientes, int totalFornecedores, 
                           int totalEventos, int totalRecursos, int totalEquipes);

void viewAguardarContinuar();

#endif // IMPORTACAO_EXPORTACAO_VIEW_H