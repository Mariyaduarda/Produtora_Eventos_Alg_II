#ifndef EVENTO_H
#define EVENTO_H

#include "recurso.h"
#include <time.h>

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

typedef struct ListaRecurso{
    struct ListaRecurso *prox;
    TipoRecurso recurso;
} ListaRecursoEvento;

// Item de Equipe Interna alocada
typedef struct {
    int codigoFunc;
    double valorDiaria;
    int numDias;
    double subtotal; // numDias * diaria
} ItemEquipeEvento;

typedef struct ListaEquipe{
    struct ListaEquipe *prox;
    TipoEquipeEvento equipe;
} ListaEquipe;

// Item de Serviço de Fornecedor/Parceiro
typedef struct {
    int codigoFornecedor;
    char descricaoServico[150]; // desc planejada
    double valorServico;
} ItemFornecedorEvento;

typedef struct ListaFornecedor{
    struct ListaFornecedor *prox;
    TipoFornecedor fornecedor;
} ListaFornecedor;

// struct principal do evento
typedef struct {
    int id;
    bool ativo;

    char nome[100];

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
    // ListaRecursoEvento* listaRecursos;
    // ListaEquipeEvento* listaEquipes;
    // ListaFornecedorEvento* listaFornecedores;
    // removi qtdRecurso, qtdEquipes, qtdFornecedores

    // valores a serem calculaados
    double custoTotalRecursos;
    double custoTotalEquipe;
    double custoTotalForn;
    double custoTotal;         // soma dos custos
    double margemLucro;       // percentual (ex: 20.0 para 20%)
    double valorFinal;       // valor a cobrar do cliente

    char obs[500];
} TipoEvento;

typedef struct ListaEvento{
    struct ListaEvento *prox;
    TipoEvento evento;
} ListaEvento;

//=========== FUNCOES BASICAS ===========
void eventoInit(TipoEvento *evento);
void eventoListaInit(ListaEvento **listaEvento);

//=========== CRUD DO EEVENTO ===========
int eventoAdicionar(ListaEvento **listaEvento, TipoEvento evento);
int eventoRemover(ListaEvento **listaEvento, int id);
int eventoAtualizar(ListaEvento *listaEvento, TipoEvento eventoAtualizado, int id);
TipoEvento* eventoBuscar(ListaEvento *listaEvento, int id);
void eventoListaLiberar(ListaEvento* listaEvento);

//=========== GESTAO GERAL ===========
int eventoUnirRecurso(TipoEvento *evento, ListaRecurso *listaGlobalRecursos, int codigoRecurso,
    int qtd, int diasEvento);
int eventoUnirEquipe(TipoEvento *evento, ListaEquipe *listaGlobalEquipe, int codigoFunc,
    double valorDiaria, int numDias);
int eventoUnirFornecedor(TipoEvento *evento, ListaFornecedor *listaGlobalFornecedor, int codigoFornecedor,
    const char *descricaoServico, double valorServico);

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