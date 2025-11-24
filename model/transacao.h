#ifndef TRANSACAO_H
#define TRANSACAO_H

#include "evento.h"
// enums para tipo de transação
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

// === ESTRUTURAS BASES ===
// movientação de caixa
typedef struct {
    int id;
    char data[11];
    char hora[6];
    TipoTransacao tipo;  // entrada ou saída
    float valor;
    FormaPagamento formaPagamento;
    char descricao[200];
    int codigoEvento;  // se relacionado a um evento
} MovimentacaoCaixa;

// === CONTAS A RECEBER ===
typedef struct {
    int codigo;
    int codigoCliente;
    int codigoEvento;
    float valorTotal;
    float valorPago;
    float valorRestante;
    char dataEmissao[11];
    char dataVencimento[11];
    char dataPagamento[11];  // vazio se não pago
    bool pago = true;  // 0 = não pago, 1(true) = pago
    char observacoes[200];
} ContaReceber;

// === CONTAS A PAGAR ===
typedef struct {
    int codigo;
    int codigoFornecedor;
    float valorTotal;
    float valorPago;
    float valorRestante;
    char dataEmissao[11];
    char dataVencimento[11];
    char dataPagamento[11];
    bool pago = true;  // 0 = não pago, 1(true) = pago
    char descricao[200];
} ContaPagar;

// === NOTA FISCAL DE ENTRADA ===
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

    // Forma de pagamento
    int pagoAVista;  // 1 = sim, 0 = não
    float valorEntrada;
    int numeroParcelas;
} NotaFiscalEntrada;

// ===== FUNÇÕES AUXILIARES =====
void obterDataAtual(char *data);
void obterDataHoraAtual(char *data, char *hora);
void calcularDataVencimento(char *dataVenc, int dias);

// ===== FUNÇÕES DE CAIXA =====
float obterSaldoCaixa();
int registrarEntradaCaixa(float valor, FormaPagamento forma,
                          const char* descricao, int codigoEvento);
int registrarSaidaCaixa(float valor, const char* descricao);

// ===== FUNÇÕES DE CONTAS A RECEBER =====
ContaReceber* buscarContaReceberPorCodigo(int codigo);
int gerarContaReceber(int codigoCliente, int codigoEvento, float valor);
int baixarContaReceber(int codigoConta, float valorPagamento, FormaPagamento forma);

// ===== FUNÇÕES DE CONTAS A PAGAR =====
ContaPagar* buscarContaPagarPorCodigo(int codigo);
int gerarContaPagar(int codigoFornecedor, float valor, int diasVencimento,
                    const char* descricao);
int baixarContaPagar(int codigoConta);

// ===== INTEGRAÇÃO COM EVENTOS =====
int eventoGerarContaReceber(TipoEvento *evento);
int eventoReceberPagamento(int codigoEvento, float valor, FormaPagamento forma);

// ===== RELATÓRIOS =====
void relatorioFluxoCaixa();
void relatorioContasReceber();
void relatorioContasPagar();

// ===== PERSISTÊNCIA =====
int salvarTransacoesTXT();
int carregarTransacoesTXT();

// ===== NOTA FISCAL (se você for implementar) =====
NotaFiscalEntrada* criarNotaFiscal(int codigoFornecedor, float frete, float imposto);
int adicionarItemNotaFiscal(NotaFiscalEntrada* nf, int codigoRecurso,
                            const char* descricao, float precoCusto, int quantidade);
int finalizarNotaFiscal(NotaFiscalEntrada* nf, int pagoAVista,
                       float valorEntrada, int numeroParcelas);

#endif //TRANSACAO_H