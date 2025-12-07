/*
 * Módulo de Feedback - Sistema de Controle Gerencial para Produtora de Eventos
 * Disciplina: Algoritmos II
 * 
 * Este módulo implementa todas as funcionalidades de relatórios do sistema
 */

#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estruturas necessárias (incluir do seu sistema principal)
typedef struct {
    int codigo;
    char razaoSocial[200];
    char endereco[300];
    char cpfCnpj[20];
    char telefone[20];
    char email[100];
    char nomeContato[100];
} Cliente;

typedef struct {
    int codigo;
    char descricao[200];
    char categoria[50];
    int quantidadeEstoque;
    float precoCusto;
    float valorLocacao;
} Equipamento;

typedef struct {
    char codigoEvento[20];
    char nomeEvento[200];
    int codigoCliente;
    char dataInicio[11];
    char dataFim[11];
    char status[20]; // Orçamento, Aprovado, Finalizado
    float valorTotal;
    char localEvento[300];
} Evento;

typedef struct {
    int codigo;
    int codigoCliente;
    char dataVencimento[11];
    float valor;
    char status[20]; // Pendente, Pago
    char descricao[200];
} ContaReceber;

typedef struct {
    int codigo;
    int codigoFornecedor;
    char dataVencimento[11];
    float valor;
    char status[20]; // Pendente, Pago
    char descricao[200];
} ContaPagar;

typedef struct {
    int codigo;
    char data[11];
    char tipo[20]; // Entrada, Saída
    float valor;
    char descricao[200];
    char formaPagamento[30]; // Dinheiro, Débito, Crédito
} MovimentacaoCaixa;

typedef struct {
    char codigoEvento[20];
    int codigoRecurso;
    char dataInicio[11];
    char dataFim[11];
    int quantidade;
} AlocacaoRecurso;
