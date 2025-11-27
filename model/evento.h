#ifndef EVENTO_H
#define EVENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "recurso.h"
#include "equipe.h"
#include "fornecedor.h"

#include "../utils/utils_validacoes.h"
#include "../utils/utils_data.h"

//===============================================
// Itens do que foi usado nesse evento

typedef struct {
    // id do recurso
    int idRecurso;
    
    // dados relevantes
    int qtdTempo;        // quantidade de dias que vai usar
    int qtd;             // qtd de itens desse q foram usados
    float precoUnitario; // preco de um so item
    float precoTotal;    // preco total (precoUnitario * qtd * qtdTempo)
} ItemRecursoEvento;

typedef struct {
    // id da equipe
    int idEquipe;

    // dados relevantes
    int qtdTempo;     // quantidade de horas ou dias que vai usar
    int precoTipo;    // 0: Fixo, 1: Por hora, 2: Por Dia
    float precoValor; // Valor fixo/hora/dia
    float precoTotal; // Preco Total ( calculado diferente dependendo do tipo)
} ItemEquipeEvento;

typedef struct {
    // id do fornecedor
    int idFornecedor;

    // dados relevantes
    int qtdTempo;     // quantidade de horas ou dias que vai usar
    int precoTipo;    // 0: Fixo, 1: Por hora, 2: Por Dia
    float precoValor; // Valor fixo/hora/dia
    float precoTotal; // Preco Total ( calculado diferente dependendo do tipo)
} ItemFornecedorEvento;

//===============================================
// Listas do que foi usado nesse evento

typedef struct ListaRecursoEvento{
    struct ListaRecursoEvento *prox;
    ItemRecursoEvento item;
} ListaRecursoEvento;

typedef struct ListaEquipeEvento{
    struct ListaEquipeEvento *prox;
    ItemEquipeEvento item;
} ListaEquipeEvento;

typedef struct ListaFornecedorEvento{
    struct ListaFornecedorEvento *prox;
    ItemFornecedorEvento item;
} ListaFornecedorEvento;

//===============================================
// Estruturas para o evento em si

typedef enum {
    STATUS_ORCAMENTO,  // em analize
    STATUS_APROVADO,   // foi aprovado mas n terminou
    STATUS_FINALIZADO, // ja terminou, pd mandar as contas
    STATUS_CANCELADO   // evento foi cancelado
} StatusEvento;

// struct principal do evento
typedef struct {
    int id;            // ID do evento
    int idCliente; // ID do cliente associado
    bool ativo;        // se o evento esta ativo ou foi removido
    char nome[100];    // nome do evento

    // Atributos do evento
    StatusEvento status;   // status do evento
    struct tm dataInicio;  // data de inicio do evento
    struct tm dataFim;     // data de fim do evento
    char localEvento[150]; // local do evento
    char cidade[50];       // cidade do evento
    char uf[4];            // estado (UF) do evento

    // valores a serem calculados
    double custoTotalRecurso;     //
    double custoTotalEquipe;       //
    double custoTotalFornecedor; //

    double custoTotal;  // soma dos custos
    double margemLucro; // percentual de lucro
    double valorFinal;  // valor a cobrar do cliente ( custo + margem )

    // listas de itens associados ao evento
    ListaRecursoEvento *listaRecursos;        // Recursos
    ListaEquipeEvento *listaEquipes;          // Equipes
    ListaFornecedorEvento *listaFornecedores; // Fornecedores
    
    // observacoes
    char obs[500]; 

} TipoEvento;

typedef struct ListaEvento{
    struct ListaEvento *prox;
    TipoEvento evento;
} ListaEvento;

//=========== FUNCOES BASICAS ===========
void eventoInit(TipoEvento *evento);
void eventoListaInit(ListaEvento *lista);

//=========== CRUD DO EEVENTO ===========
ListaEvento* eventoAdicionar(ListaEvento **listaEvento, TipoEvento evento);
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

int recursoContarUsoPeriodo(ListaEvento *listaEventos, int idRecurso, struct tm inicioConsulta, struct tm fimConsulta);

int equipeEstaAlocadaPeriodo(ListaEvento *listaEventos, int idEquipe, struct tm inicioConsulta, struct tm fimConsulta);


// Operacoes sobre listas internas do evento
int eventoAdicionarRecurso(TipoEvento *evento, ItemRecursoEvento item);
ItemRecursoEvento* eventoBuscarRecurso(TipoEvento *evento, int idRecurso);
int eventoRemoverRecurso(TipoEvento *evento, int idRecurso);

int eventoAdicionarEquipe(TipoEvento *evento, ItemEquipeEvento item);
ItemEquipeEvento* eventoBuscarEquipe(TipoEvento *evento, int codigoFunc);
int eventoRemoverEquipe(TipoEvento *evento, int codigoFunc);

int eventoAdicionarFornecedor(TipoEvento *evento, ItemFornecedorEvento item);
ItemFornecedorEvento* eventoBuscarFornecedor(TipoEvento *evento, int idFornecedor);
int eventoRemoverFornecedor(TipoEvento *evento, int idFornecedor);

//=========== MUDANCA DE STAUS ===========
int eventoAprovar(TipoEvento *evento);
int eventoFinalizar(TipoEvento *evento);
int eventoCancelar(TipoEvento *evento);
int eventoOrcamento(TipoEvento *evento);


//=========== CALCULOS ===========
double eventoCalcularTotalRecursos(TipoEvento *evento);
double eventoCalcularTotalEquipe(TipoEvento *evento);
double eventoCalcularTotalFornecedores(TipoEvento *evento);
void eventoCalcularTotal(TipoEvento *evento);

//=========== PERSISTENCIA DE DADOS ===========

void eventoSalvarTXTLinha(FILE *f, TipoEvento *evento);
void eventoSalvarTXTRecurso(FILE *f, ItemRecursoEvento *item);
void eventoSalvarTXTEquipe(FILE *f, ItemEquipeEvento *item);
void eventoSalvarTXTFornecedor(FILE *f, ItemFornecedorEvento *item);
void eventoSalvarTXT(ListaEvento *lista);

void eventoLerTXTLinha(char *linha, TipoEvento *evento);
void eventoLerTXTRecurso(char *linha, ItemRecursoEvento *item);
void eventoLerTXTEquipe(char *linha, ItemEquipeEvento *item);
void eventoLerTXTFornecedor(char *linha, ItemFornecedorEvento *item);
int eventoLerTXT(ListaEvento **lista);

int eventoSalvarBIN(ListaEvento *lista);
int eventoLerBIN(ListaEvento **lista);



#endif //EVENTO_H