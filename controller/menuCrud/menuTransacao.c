#include "menuTransacao.h"
#include "../../model/transacao.h"
#include "../../view/printMenu.h"
#include "../../view/mensagens.h"

void menuTransacao(TipoProdutora* produtora, TipoConfig *config) {
	// Listas locais para movimentacoes e contas
	ListaMovimentacao *listaMov = NULL;
	ListaContaReceber *listaCR = NULL;
	ListaContaPagar *listaCP = NULL;

	// Carrega dados existentes (0 = txt, 1 = binario)
	int tipoArquivo = config->salvar_como_binario ? 1 : 0;
	transacaoCarregarTudo(&listaMov, &listaCR, &listaCP, tipoArquivo);

	int escolha = 0;
	while (1) {
		printMenuTransacaoPrincipal();
		escolha = recebeInt(0, 5, "Digite uma opcao", "#", config->validar_dados);

		if (escolha == 0) break;

		switch (escolha) {
			case 1: { // Movimentacao de Caixa
				int sub;
				float saldo = obterSaldoCaixa(listaMov);
				do {
					printMenuMovimentacaoCaixa(saldo);
					sub = recebeInt(0, 3, "Digite uma opcao", "#", config->validar_dados);
					switch (sub) {
						case 1: { // Registrar Entrada
							float valor = recebeFloat(0.01f, 100000000.0f, "Valor da entrada", "", config->validar_dados);
							int forma = recebeInt(0, 3, "Forma de pagamento (0-Dinheiro,1-Debito,2-Credito,3-PIX)", "#", config->validar_dados);
							char descricao[200];
							recebeString(descricao, 200, "Descricao", "Max.200", config->validar_dados);
							int codigoEvento = recebeID(config->validar_dados);
							int id = registrarEntradaCaixa(&listaMov, valor, (FormaPagamento)forma, descricao, codigoEvento);
							if (id) printAdicionarSucesso(); else printAdicionarFalha();
							esperaEnter();
							saldo = obterSaldoCaixa(listaMov);
							break;
						}
						case 2: { // Registrar Saida
							float valor = recebeFloat(0.01f, 100000000.0f, "Valor da saida", "", config->validar_dados);
							char descricao[200];
							recebeString(descricao, 200, "Descricao", "Max.200", config->validar_dados);
							int ok = registrarSaidaCaixa(&listaMov, valor, descricao);
							if (ok) printAdicionarSucesso(); else printAdicionarFalha();
							esperaEnter();
							saldo = obterSaldoCaixa(listaMov);
							break;
						}
						case 3: { // Consultar Movimentacoes
							limparTela();
							ListaMovimentacao *it = listaMov;
							if (it == NULL) { printMensagem("Nenhuma movimentacao cadastrada","#"); }
							while (it != NULL) {
								MovimentacaoCaixa m = it->movimentacao;
								printf("\n=[ ID: %d ]-----------------------------------------\n", m.id);
								printf(" Data: %s %s\n", m.data, m.hora);
								printf(" Tipo: %s\n", m.tipo==TIPO_ENTRADA?"Entrada":"Saida");
								printf(" Valor: R$ %.2f\n", m.valor);
								printf(" Forma: %d\n", m.formaPagamento);
								printf(" Descricao: %s\n", m.descricao);
								printf(" Evento (ID): %d\n", m.codigoEvento);
								it = it->prox;
							}
							esperaEnter();
							break;
						}
					}
				} while (sub != 0);
				break;
			}
			case 2: { // Contas a Receber
				int sub;
				do {
					printMenuContasReceber();
					sub = recebeInt(0, 4, "Digite uma opcao", "#", config->validar_dados);
					switch (sub) {
						case 1: { // Gerar Conta (via Evento)
							int codigoCliente = recebeID(config->validar_dados);
							int codigoEvento = recebeID(config->validar_dados);
							float valor = recebeFloat(0.0f, 100000000.0f, "Valor total", "", config->validar_dados);
							int codigo = gerarContaReceber(&listaCR, codigoCliente, codigoEvento, valor);
							if (codigo) printAdicionarSucesso(); else printAdicionarFalha();
							esperaEnter();
							break;
						}
						case 2: { // Baixar Conta (Receber Pagamento)
							int codigoConta = recebeID(config->validar_dados);
							float valorPago = recebeFloat(0.0f, 100000000.0f, "Valor do pagamento", "", config->validar_dados);
							int forma = recebeInt(0, 3, "Forma de pagamento", "#", config->validar_dados);
							int ok = baixarContaReceber(listaCR, &listaMov, codigoConta, valorPago, (FormaPagamento)forma);
							if (ok) printAdicionarSucesso(); else printAdicionarFalha();
							esperaEnter();
							break;
						}
						case 3: { // Consultar Conta especifica
							int codigo = recebeID(config->validar_dados);
							ContaReceber *cr = contaReceberBuscar(listaCR, codigo);
							if (cr == NULL) { printNaoEncontrado(); }
							else {
								limparTela();
								printf("\nConta: %d\nCliente: %d\nEvento: %d\nValor Total: R$ %.2f\nValor Pago: R$ %.2f\nValor Restante: R$ %.2f\nPago: %s\n",
									cr->codigo, cr->codigoCliente, cr->codigoEvento, cr->valorTotal, cr->valorPago, cr->valorRestante, cr->pago?"Sim":"Nao");
							}
							esperaEnter();
							break;
						}
						case 4: { // Listar Todas as Contas
							limparTela();
							ListaContaReceber *it = listaCR;
							if (it == NULL) { printMensagem("Nenhuma conta cadastrada","#"); }
							while (it != NULL) {
								ContaReceber c = it->conta;
								printf("\n=[ Codigo: %d ]---------------------------------\n", c.codigo);
								printf(" Cliente: %d\n Evento: %d\n Valor Total: R$ %.2f\n Valor Pago: R$ %.2f\n Restante: R$ %.2f\n Pago: %s\n",
									c.codigoCliente, c.codigoEvento, c.valorTotal, c.valorPago, c.valorRestante, c.pago?"Sim":"Nao");
								it = it->prox;
							}
							esperaEnter();
							break;
						}
					}
				} while (sub != 0);
				break;
			}
			case 3: { // Contas a Pagar
				int sub;
				do {
					printMenuContasPagar();
					sub = recebeInt(0, 4, "Digite uma opcao", "#", config->validar_dados);
					switch (sub) {
						case 1: { // Gerar Conta Manual
							int codigoFornecedor = recebeID(config->validar_dados);
							float valor = recebeFloat(0.0f, 100000000.0f, "Valor total", "", config->validar_dados);
							int dias = recebeInt(0, 3650, "Dias para vencimento", "#", config->validar_dados);
							char descricao[200];
							recebeString(descricao, 200, "Descricao", "Max.200", config->validar_dados);
							int codigo = gerarContaPagar(&listaCP, codigoFornecedor, valor, dias, descricao);
							if (codigo) printAdicionarSucesso(); else printAdicionarFalha();
							esperaEnter();
							break;
						}
						case 2: { // Baixar Conta (Efetuar Pagamento)
							int codigoConta = recebeID(config->validar_dados);
							int ok = baixarContaPagar(listaCP, &listaMov, codigoConta);
							if (ok) printAdicionarSucesso(); else printAdicionarFalha();
							esperaEnter();
							break;
						}
						case 3: { // Consultar Conta especifica
							int codigo = recebeID(config->validar_dados);
							ContaPagar *cp = contaPagarBuscar(listaCP, codigo);
							if (cp == NULL) { printNaoEncontrado(); }
							else {
								limparTela();
								printf("\nConta: %d\nFornecedor: %d\nValor Total: R$ %.2f\nValor Pago: R$ %.2f\nValor Restante: R$ %.2f\nPago: %s\n",
									cp->codigo, cp->codigoFornecedor, cp->valorTotal, cp->valorPago, cp->valorRestante, cp->pago?"Sim":"Nao");
							}
							esperaEnter();
							break;
						}
						case 4: { // Listar Todas as Contas
							limparTela();
							ListaContaPagar *it = listaCP;
							if (it == NULL) { printMensagem("Nenhuma conta cadastrada","#"); }
							while (it != NULL) {
								ContaPagar c = it->conta;
								printf("\n=[ Codigo: %d ]---------------------------------\n", c.codigo);
								printf(" Fornecedor: %d\n Valor Total: R$ %.2f\n Valor Pago: R$ %.2f\n Restante: R$ %.2f\n Pago: %s\n",
									c.codigoFornecedor, c.valorTotal, c.valorPago, c.valorRestante, c.pago?"Sim":"Nao");
								it = it->prox;
							}
							esperaEnter();
							break;
						}
					}
				} while (sub != 0);
				break;
			}
			case 4: { // Nota Fiscal de Entrada (implementacao simplificada)
				limparTela();
				printMensagem("Funcionalidade em desenvolvimento","#");
				esperaEnter();
				break;
			}
			case 5: { // Relatorios
				int sub;
				do {
					printMenuRelatorios();
					sub = recebeInt(0, 3, "Digite uma opcao", "#", config->validar_dados);
					switch (sub) {
						case 1: relatorioFluxoCaixa(listaMov); esperaEnter(); break;
						case 2: relatorioContasReceber(listaCR); esperaEnter(); break;
						case 3: relatorioContasPagar(listaCP); esperaEnter(); break;
					}
				} while (sub != 0);
				break;
			}
			default:
				printOpcaoInvalida();
				esperaEnter();
		}
	}

	// Ao sair, salva tudo
	transacaoSalvarTudo(listaMov, listaCR, listaCP, tipoArquivo);

	// Liberar memoria
	movimentacaoListaLiberar(listaMov);
	contaReceberListaLiberar(listaCR);
	contaPagarListaLiberar(listaCP);
}