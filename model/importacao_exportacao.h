/*
 * Módulo de Importação/Exportação - Sistema de Controle Gerencial para Produtora de Eventos
 * Disciplina: Algoritmos II
 * 
 * Este módulo implementa funcionalidades de importação e exportação de dados em formato XML
 */

#ifndef IMPORTACAO_EXPORTACAO_H
#define IMPORTACAO_EXPORTACAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "fornecedor.h"
#include "evento.h"
#include "recurso.h"

// Funções auxiliares para XML
void escreverTagXML(FILE* arquivo, const char* tag, const char* valor, int nivel);

void escreverTagXMLInt(FILE* arquivo, const char* tag, int valor, int nivel);

void escreverTagXMLFloat(FILE* arquivo, const char* tag, float valor, int nivel);

void abrirTagXML(FILE* arquivo, const char* tag, int nivel);

void fecharTagXML(FILE* arquivo, const char* tag, int nivel);

// ========== EXPORTAÇÃO ==========

int exportarClientes(TipoCliente* clientes, int totalClientes, FILE* arquivo);

int exportarEventos(TipoEvento* eventos, int totalEventos, FILE* arquivo);
int exportarFornecedores(TipoFornecedor* fornecedores, int totalFornecedores, FILE* arquivo);
int exportarRecurso(TipoRecurso* recursos, int totalRecursos, FILE* arquivo);
int exportarEquipe(TipoEquipe* equipes, int totalEquipes, FILE* arquivo);
// Função principal de exportação
void exportarDados(TipoCliente* cliente, int totalClientes,
                   TipoFornecedor* fornecedores, int totalFornecedores,  // era: forncedores
                   TipoEvento* eventos,  int totalEventos, 
                   TipoRecurso* recursos, int totalRecursos,            // era: rescursos
                   TipoEquipe* equipes, int totalEquipes, 
                   int exportarCli, int exportarEquip, int exportarEv);
// ========== IMPORTAÇÃO ==========

// Função auxiliar para extrair valor de uma tag XML
int extrairValorTag(const char* linha, const char* tag, char* destino);

int extrairValorTagInt(const char* linha, const char* tag);

float extrairValorTagFloat(const char* linha, const char* tag);

int importarClientes(const char* nomeArquivo, TipoCliente** clientes, int* totalClientes);

int importarFornecedores(const char* nomeArquivo, TipoFornecedor** fornecedores, int* totalFornecedores);

int importarEventos(const char* nomeArquivo, TipoEvento** eventos, int* totalEventos);

// Menu de importação/exportação
void menuImportacaoExportacao();
#endif // IMPORTACAO_EXPORTACAO_H