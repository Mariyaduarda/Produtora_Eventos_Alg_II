//
// Created by alunos on 19/11/2025.
//

#ifndef EVENTO_H
#define EVENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recurso.h"
#include <time.h>
#include <stdbool.h>

// tipo enumerado para status
typedef enum {
    STATUS_ORCAMENTO,
    STATUS_APROVADO,
    STATUS_FINALIZADO,
    STATUS_CANCELADO
} StatusEvento;

// structs de referencia ao evento
typedef struct {
    int codigoRecurso; // refrencia o id do recurso
    int qtd;
    int diasEvento;
    double valorUnitario; // negociacao especifica
    double subtotal;       // qnt * valor_uni * dias
} ItemRecursoEvento;

typedef struct {
    int codigoFunc;
    double valorDiaria;
    int numDias;
    double subtotal; // numDias * diaria
} ItemEquipeEvento;

typedef struct {
    int codigoFornecedor;
    char descricaoServico[150];
    double valorServico;
} ItemFornecedorEvento;

// struct principal do evento
typedef struct {
    int codigo;
    bool ativo;
    char nome[100];
    int codigoCliente;

    // datas e locais do evento
    char dataInicio[11]; // formatar como dd/mm/aaaa
    char dataFim[11];
    char horaInicio[6];  // hh mm
    char horaFim[6];
    char localEvento[150];
    char cidade[50];
    char uf[4];

    // status do evento
    StatusEvento status;

    // array dinamico para os itens
    ItemRecursoEvento* listaRecursos;
    int qtdRecurso;
    ItemEquipeEvento* listaEquipes;
    int qtdEquipes;
    ItemFornecedorEvento* listaFornecedores;
    int qtdFornecedores;

    // valores a seremcalculados
    double custoTotalRecursos;
    double custoTotalEquipe;
    double custoTotalServicos;
    double custoTotal;         // soma dos custos
    double margemLucro;       // percentual (ex: 20.0 para 20%)
    double valorFinal;       // valor a cobrar do cliente

    char obs[500];
} TipoEvento;

typedef struct ListaEvento{
    struct ListaEvento *prox;
    TipoEvento evento;
} ListaEvento;

#endif //EVENTO_H