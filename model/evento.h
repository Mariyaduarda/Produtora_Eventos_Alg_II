#ifndef EVENTO_H
#define EVENTO_H

#include "recurso.h"
#include "equipe.h"
#include "fornecedor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Itens e listas internas por evento
typedef struct {
    int codigoRecurso;
    int qtd;
    int diasEvento;
    double valorUnitario;
    double subtotal;
} ItemRecursoEvento;

typedef struct ListaRecursoEvento{
    struct ListaRecursoEvento *prox;
    ItemRecursoEvento item;
} ListaRecursoEvento;

typedef struct {
    int codigoFunc;
    double valorDiaria;
    int numDias;
    double subtotal;
} ItemEquipeEvento;

typedef struct ListaEquipeEvento{
    struct ListaEquipeEvento *prox;
    ItemEquipeEvento item;
} ListaEquipeEvento;

typedef struct {
    int codigoFornecedor;
    char descricaoServico[200];
    double valorServico;
} ItemFornecedorEvento;

typedef struct ListaFornecedorEvento{
    struct ListaFornecedorEvento *prox;
    ItemFornecedorEvento item;
} ListaFornecedorEvento;

// tipo enumerado para status
typedef enum {
    STATUS_ORCAMENTO,
    STATUS_APROVADO,
    STATUS_FINALIZADO,
    STATUS_CANCELADO
} StatusEvento;

// struct principal do evento
typedef struct {
    int id;            //
    int codigoCliente; // Cliente relacionado ao evento
    bool ativo;        // se o evento esta ativo ou foi removido
    char nome[100];    //

    // Atributos do evento
    StatusEvento status;   // status do evento
    struct tm dataInicio;  //
    struct tm dataFim;     //
    char localEvento[150]; //
    char cidade[50];       //
    char uf[4];            //

    // valores a serem calculados
    double custoTotalRecursos; //
    double custoTotalEquipe;   //
    double custoTotalForn;     //
    double custoTotal;         // soma dos custos
    double margemLucro;        // percentual (ex: 20.0 para 20%)
    double valorFinal;         // valor a cobrar do cliente

    // listas de itens associados ao evento
    ListaRecursoEvento *listaRecursos;
    ListaEquipeEvento *listaEquipes;
    ListaFornecedorEvento *listaFornecedores;

    char obs[500];         // observacoes
} TipoEvento;

typedef struct ListaEvento{
    struct ListaEvento *prox;
    TipoEvento evento;
} ListaEvento;

//=========== FUNCOES BASICAS ===========
void eventoInit(TipoEvento *evento);
void eventoListaInit(ListaEvento *lista);

//=========== CRUD DO EEVENTO ===========
int eventoAdicionar(ListaEvento **listaEvento, TipoEvento evento);
int eventoRemover(ListaEvento **listaEvento, int id);
int eventoAtualizar(ListaEvento *listaEvento, TipoEvento eventoAtualizado, int id);
TipoEvento* eventoBuscar(ListaEvento *listaEvento, int id);
void eventoListaLiberar(ListaEvento* listaEvento);

// Liberar listas internas do evento
void eventoLiberarRecursos(TipoEvento *evento);
void eventoLiberarEquipes(TipoEvento *evento);
void eventoLiberarFornecedores(TipoEvento *evento);
void eventoLiberarTodosItens(TipoEvento *evento);

// Editar campos do evento
int eventoSetDatas(TipoEvento *evento, struct tm dataInicio, struct tm dataFim);

//=========== GESTAO GERAL ===========
int eventoUnirRecurso(TipoEvento *evento, ListaRecurso *listaGlobalRecursos, int codigoRecurso,
    int qtd, int diasEvento);
int eventoUnirEquipe(TipoEvento *evento, ListaEquipe *listaGlobalEquipe, int codigoFunc,
    double valorDiaria, int numDias);
int eventoUnirFornecedor(TipoEvento *evento, ListaFornecedor *listaGlobalFornecedor, int codigoFornecedor,
    const char *descricaoServico, double valorServico);

// Operacoes sobre listas internas do evento
int eventoAdicionarRecurso(TipoEvento *evento, ItemRecursoEvento item);
ItemRecursoEvento* eventoBuscarRecurso(TipoEvento *evento, int codigoRecurso);
int eventoRemoverRecurso(TipoEvento *evento, int codigoRecurso);

int eventoAdicionarEquipe(TipoEvento *evento, ItemEquipeEvento item);
ItemEquipeEvento* eventoBuscarEquipe(TipoEvento *evento, int codigoFunc);
int eventoRemoverEquipe(TipoEvento *evento, int codigoFunc);

int eventoAdicionarFornecedor(TipoEvento *evento, ItemFornecedorEvento item);
ItemFornecedorEvento* eventoBuscarFornecedor(TipoEvento *evento, int codigoFornecedor);
int eventoRemoverFornecedor(TipoEvento *evento, int codigoFornecedor);

//=========== MUDANCA DE STAUS ===========
int eventoAprovar(TipoEvento *evento);
int eventoFinalizar(TipoEvento *evento);
int eventoCancelar(TipoEvento *evento);
int eventoOrcamento(TipoEvento *evento);


//=========== CALCULOS ===========
double eventoCalcularTotalRecursos(TipoEvento *evento);
double eventoCalcularTotalEquipe(TipoEvento *evento);
double eventoCalcularTotalFornecedores(TipoEvento *evento);
void eventoRecalcularTotais(TipoEvento *evento);

//=========== PERSISTENCIA DE DADOS ===========
int eventoSalvarTXT(ListaEvento *listaEvento);
int eventoLerTXT(ListaEvento **listaEvento);

int eventoSalvarBIN(ListaEvento *listaEvento);
int eventoLerBIN(ListaEvento **listaEvento);


#endif //EVENTO_H