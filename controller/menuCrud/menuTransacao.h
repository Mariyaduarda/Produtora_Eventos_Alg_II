#ifndef MENU_TRANSACAO_H
#define MENU_TRANSACAO_H

#include "../../model/transacao.h"
#include "../../model/produtora.h"
#include "../../model/config.h"
#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"

#include "../../model/transacao.h"
#include "../../view/printMenu.h"
#include "../../view/mensagens.h"

void menuTransacao(TipoProdutora* produtora, TipoConfig *config);
// Subrotinas para cada opcao do menu principal
void menuTransacaoCaixa(ListaMovimentacao **listaMov, TipoConfig *config);
void menuTransacaoContaReceber(ListaContaReceber **listaCR, ListaMovimentacao **listaMov, TipoConfig *config);
// Subrotinas para Contas a Receber
void menuTransacaoContaReceber_GerarConta(ListaContaReceber **listaCR, TipoConfig *config);
void menuTransacaoContaReceber_BaixarConta(ListaContaReceber **listaCR, ListaMovimentacao **listaMov, TipoConfig *config);
void menuTransacaoContaReceber_ConsultarContaEspecifica(ListaContaReceber **listaCR, TipoConfig *config);
void menuTransacaoContaReceber_ListarTodas(ListaContaReceber **listaCR);
void menuTransacaoContaPagar(ListaContaPagar **listaCP, ListaMovimentacao **listaMov, TipoConfig *config);
// Subrotinas para Contas a Pagar
void menuTransacaoContaPagar_GerarContaManual(ListaContaPagar **listaCP, TipoConfig *config);
void menuTransacaoContaPagar_BaixarConta(ListaContaPagar **listaCP, ListaMovimentacao **listaMov, TipoConfig *config);
void menuTransacaoContaPagar_ConsultarContaEspecifica(ListaContaPagar **listaCP, TipoConfig *config);
void menuTransacaoContaPagar_ListarTodas(ListaContaPagar **listaCP);
void menuTransacaoNotaFiscal(TipoConfig *config);
void menuTransacaoRelatorio(ListaMovimentacao *listaMov, ListaContaReceber *listaCR, ListaContaPagar *listaCP, TipoConfig *config);


#endif // MENU_TRANSACAO_H