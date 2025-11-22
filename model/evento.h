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
// Item de Recurso/Equipamento alocado

typedef struct {
    int codigoRecurso; // refrencia o id do recurso
    int qtd;
    int diasEvento;
    double valorUnitario; // negociacao especifica
    double subtotal;       // qnt * valor_uni * dias
} ItemRecursoEvento;

// Item de Equipe Interna alocada
typedef struct {
    int codigoFunc;
    double valorDiaria;
    int numDias;
    double subtotal; // numDias * diaria
} ItemEquipeEvento;

// Item de Serviço de Fornecedor/Parceiro
typedef struct {
    int codigoFornecedor;
    char descricaoServico[150];
    double valorServico;
} ItemFornecedorEvento;

// ===== LISTAS ENCADEADAS DOS ITENS =====
typedef struct ListaRecursoEvento{
    ItemRecursoEvento item;
    struct ListaRecursoEvento* proximo;
} ListaRecursoEvento;

typedef struct ListaEquipe {
    ItemEquipeEvento  item;
    struct ListaEquipe* proximo;
} ListaEquipe;

typedef struct ListaFornecedor {
    ItemFornecedorEvento  item;
    struct ListaFornecedor* proximo;
} ListaFornecedor;

// struct principal do evento
typedef struct {
    int id;
    bool ativo;

    char nome[100];
    int codigoCliente; //id do cliente

    // datas e locais do evento
    struct tm dataInicio; // formatar como dd/mm/aaaa
    struct tm dataFim;
    // char horaInicio[6];  // hh mm
    // char horaFim[6];

    char localEvento[150];
    char cidade[50];
    char uf[4];

    // status do evento
    StatusEvento status;

    // array dinamico para os itens
    // ponteiros para listas encadeadas
    ListaRecurso* listaRecursos;
    ListaEquipe* listaEquipes;
    ListaFornecedor* listaFornecedores;
    // removi qtdRecurso, qtdEquipes, qtdFornecedores

    // valores a serem calculados
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

//=========== FUNCOES BASICA ===========
void eventoInit(TipoEvento *evento);
void eventoListaInit(ListaEvento **listaEvento);

//=========== CRUD ===========
int eventoAdicionar(ListaEvento **listaEvento, TipoEvento evento);
int eventoRemover(ListaEvento **listaEvento, int id);
int eventoAtualizar(ListaEvento *listaEvento, TipoEvento eventoAtualizado, int id);
TipoEvento* eventoBuscar(ListaEvento *listaEvento, int id);
void eventoListaLiberar(ListaEvento* listaEvento);

//=========== GESTAO GERAL ===========
int eventoAdicionarRecurso(TipoEvento *evento, ItemRecursoEvento item);
int eventoRemoveRecurso(TipoEvento *evento, int codigoRecurso);
ItemRecursoEvento* eventoBuscarRecurso(TipoEvento *evento, int codigoRecurso);
void eventoLiberarRecursos(ListaRecurso *listaRecurso);

int eventoAdicionarEquipe(TipoEvento *evento, ItemEquipeEvento item);
int eventoRemoveEquipe(TipoEvento *evento, int codigoFunc);
ItemRecursoEvento* eventoBuscarEquipe(TipoEvento *evento, int codigoFunc);
void eventoLiberarEquipes(ListaRecurso *listaRecurso);

int eventoAdicionarFornecedor(TipoEvento *evento, ItemRecursoEvento item);
int eventoRemoveFornecedor(TipoEvento *evento, int codigoFornecedor);
ItemRecursoEvento* eventoBuscarFornecedor(TipoEvento *evento, int codigoFornecedor);
void eventoLiberarFornecedor(ListaRecurso *listaRecurso);

//=========== MUDANCA DE STAUS ===========
int eventoAprovar(TipoEvento *evento);
int eventoFinalizar(TipoEvento *evento);
int eventoCancelar(TipoEvento *evento);
int eventoOrcamento(TipoEvento *evento);

//=========== CALCULOS ===========
double  eventoCalcularTotalRecursos(TipoEvento *evento);
double  eventoCalcularTotalEquipe(TipoEvento *evento);
double  eventoCalcularTotalFornecedores(TipoEvento *evento);
void eventoRecalcularTotais(TipoEvento *evento);

//=========== PERSISTENCIA DE DADOS ===========
int eventoSalvarTXT(ListaEvento *listaEvento);
int eventoLerTXT(ListaEvento **listaEvento);

int eventoSalvarBIN(ListaEvento *listaEvento);
int eventoLerBIN(ListaEvento **listaEvento);


#endif //EVENTO_H