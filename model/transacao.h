#ifndef TRANSACAO_H
#define TRANSACAO_H

#include <stdbool.h>
#include "evento.h"
#include "../view/mensagens.h"

// ===== ENUMS =====
typedef enum {
    TIPO_ENTRADA,
    TIPO_SAIDA
} TipoTransacao;

typedef enum {
    FORMA_DINHEIRO,
    FORMA_DEBITO,
    FORMA_CREDITO,
    FORMA_PIX
} FormaPagamento;

// ===== ESTRUTURAS BASE =====

// Movimentacao de Caixa
typedef struct {
    int id;
    char data[11];          // dd/mm/aaaa
    char hora[6];           // hh:mm
    TipoTransacao tipo;
    float valor;
    FormaPagamento formaPagamento;
    char descricao[200];
    int codigoEvento;       // 0 se nao relacionado a evento
} MovimentacaoCaixa;

// Contas a Receber
typedef struct {
    int codigo;
    int codigoCliente;
    int codigoEvento;
    float valorTotal;
    float valorPago;
    float valorRestante;
    char dataEmissao[11];
    char dataVencimento[11];
    char dataPagamento[11];
    bool pago;              // false = nao pago, true = pago
    char observacoes[200];
} ContaReceber;

// Contas a Pagar
typedef struct {
    int codigo;
    int codigoFornecedor;
    float valorTotal;
    float valorPago;
    float valorRestante;
    char dataEmissao[11];
    char dataVencimento[11];
    char dataPagamento[11];
    bool pago;
    char descricao[200];
} ContaPagar;

// Nota Fiscal de Entrada
typedef struct {
    int codigoRecurso;
    char descricao[100];
    float precoCusto;
    int quantidade;
    float subtotal;
} ItemNotaFiscal;

typedef struct {
    int numero;
    int codigoFornecedor;
    char dataEmissao[11];
    float valorFrete;
    float valorImposto;
    ItemNotaFiscal* itens;
    int qtdItens;
    float valorTotal;
    int pagoAVista;
    float valorEntrada;
    int numeroParcelas;
} NotaFiscalEntrada;

// ===== ESTRUTURAS DE LISTAS ENCADEADAS =====

typedef struct ListaMovimentacao {
    MovimentacaoCaixa movimentacao;
    struct ListaMovimentacao *prox;
} ListaMovimentacao;

typedef struct ListaContaReceber {
    ContaReceber conta;
    struct ListaContaReceber *prox;
} ListaContaReceber;

typedef struct ListaContaPagar {
    ContaPagar conta;
    struct ListaContaPagar *prox;
} ListaContaPagar;

// ===== FUNCOES DE INICIALIZACAO =====
void movimentacaoCaixaInit(MovimentacaoCaixa *mov);
void contaReceberInit(ContaReceber *cr);
void contaPagarInit(ContaPagar *cp);

void listaMovimentacaoInit(ListaMovimentacao **lista);
void listaContaReceberInit(ListaContaReceber **lista);
void listaContaPagarInit(ListaContaPagar **lista);

// ===== FUNCOES AUXILIARES =====
void obterDataAtual(char *data);
void obterDataHoraAtual(char *data, char *hora);
void calcularDataVencimento(char *dataVenc, int dias);

// ===== CRUD MOVIMENTACAO DE CAIXA =====
int movimentacaoAdicionar(ListaMovimentacao **lista, MovimentacaoCaixa mov);
MovimentacaoCaixa* movimentacaoBuscar(ListaMovimentacao *lista, int id);
void movimentacaoListaLiberar(ListaMovimentacao *lista);

// ===== CRUD CONTA A RECEBER =====
int contaReceberAdicionar(ListaContaReceber **lista, ContaReceber conta);
ContaReceber* contaReceberBuscar(ListaContaReceber *lista, int codigo);
ContaReceber* contaReceberBuscarPorEvento(ListaContaReceber *lista, int codigoEvento);
void contaReceberListaLiberar(ListaContaReceber *lista);

// ===== CRUD CONTA A PAGAR =====
int contaPagarAdicionar(ListaContaPagar **lista, ContaPagar conta);
ContaPagar* contaPagarBuscar(ListaContaPagar *lista, int codigo);
void contaPagarListaLiberar(ListaContaPagar *lista);

// ===== FUNCOES DE CAIXA =====
float obterSaldoCaixa(ListaMovimentacao *lista);
int registrarEntradaCaixa(ListaMovimentacao **lista, float valor, FormaPagamento forma,
                          const char* descricao, int codigoEvento);
int registrarSaidaCaixa(ListaMovimentacao **lista, float valor, const char* descricao);

// ===== FUNCOES DE CONTAS A RECEBER =====
int gerarContaReceber(ListaContaReceber **lista, int codigoCliente, int codigoEvento, float valor);
int baixarContaReceber(ListaContaReceber *lista, ListaMovimentacao **listaMov,
                       int codigoConta, float valorPagamento, FormaPagamento forma);

// ===== FUNCOES DE CONTAS A PAGAR =====
int gerarContaPagar(ListaContaPagar **lista, int codigoFornecedor, float valor,
                    int diasVencimento, const char* descricao);
int baixarContaPagar(ListaContaPagar *lista, ListaMovimentacao **listaMov, int codigoConta);

// ===== INTEGRACAO COM EVENTOS =====
int eventoGerarContaReceber(TipoEvento *evento, ListaContaReceber **lista);
int eventoReceberPagamento(int codigoEvento, ListaContaReceber *lista,
                           ListaMovimentacao **listaMov, float valor, FormaPagamento forma);

// ===== RELATORIOS =====
void relatorioFluxoCaixa(ListaMovimentacao *lista);
void relatorioContasReceber(ListaContaReceber *lista);
void relatorioContasPagar(ListaContaPagar *lista);

// ===== PERSISTÊNCIA - MOVIMENTACOES =====
int movimentacaoSalvarTXT(ListaMovimentacao *lista);
int movimentacaoLerTXT(ListaMovimentacao **lista);
int movimentacaoSalvarBIN(ListaMovimentacao *lista);
int movimentacaoLerBIN(ListaMovimentacao **lista);

// ===== PERSISTÊNCIA - CONTAS A RECEBER =====
int contaReceberSalvarTXT(ListaContaReceber *lista);
int contaReceberLerTXT(ListaContaReceber **lista);
int contaReceberSalvarBIN(ListaContaReceber *lista);
int contaReceberLerBIN(ListaContaReceber **lista);

// ===== PERSISTÊNCIA - CONTAS A PAGAR =====
int contaPagarSalvarTXT(ListaContaPagar *lista);
int contaPagarLerTXT(ListaContaPagar **lista);
int contaPagarSalvarBIN(ListaContaPagar *lista);
int contaPagarLerBIN(ListaContaPagar **lista);

// ===== FUNCOES AUXILIARES DE PERSISTÊNCIA =====
int transacaoSalvarTudo(ListaMovimentacao *listaMov, ListaContaReceber *listaCR,
                        ListaContaPagar *listaCP, int tipoArquivo);
int transacaoCarregarTudo(ListaMovimentacao **listaMov, ListaContaReceber **listaCR,
                         ListaContaPagar **listaCP, int tipoArquivo);

// ===== NOTA FISCAL (implementacao futura) =====
NotaFiscalEntrada* criarNotaFiscal(int codigoFornecedor, float frete, float imposto);
int adicionarItemNotaFiscal(NotaFiscalEntrada* nf, int codigoRecurso,
                            const char* descricao, float precoCusto, int quantidade);
int finalizarNotaFiscal(NotaFiscalEntrada* nf, int pagoAVista,
                       float valorEntrada, int numeroParcelas);

#endif // TRANSACAO_H