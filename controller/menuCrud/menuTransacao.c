#include "menuTransacao.h"

TipoProdutora menuProdutoraRecebe(TipoConfig *config) {
    // Recebe uma nova Produtora do usuario e retorna a produtora preenchida
    TipoTransacao transacao;
    transacaoInit(&transacao);

    // Recebe os dados da produtora
    recebeString(produtora.nomeFantasia, 100, "Digite o Nome Fantasia","Max. 100", config->validar_dados);
    recebeString(produtora.razaoSocial, 100, "Digite a Razao Social","Max. 100", config->validar_dados);
    recebeString(produtora.inscricaoEstadual, 20, "Digite a Inscricao Estadual","9 Digitos", config->validar_dados);
    recebeCNPJ(produtora.cnpj, config->validar_dados);
    recebeString(produtora.endereco, 100, "Digite o Endereco","Max. 100", config->validar_dados);
    recebeTelefone(produtora.telefone, config->validar_dados);
    recebeEmail(produtora.email, config->validar_dados);
    recebeString(produtora.nomeDoResponsavel, 100, "Digite o Nome do Responsavel","Max. 100", config->validar_dados);
    recebeTelefone(produtora.telefoneDoResponsavel, config->validar_dados);
    produtora.margemDeLucro = recebeFloat(0, 1000000, "Digite a Margem de Lucro", "Entre 0 e 1m", config->validar_dados);

    return transacao;
}

void menuProdutoraAtualizar(TipoProdutora* produtora, TipoConfig *config) {
    // Atualiza os dados da produtora
    TipoProdutora novoProdutora;
    novoProdutora = menuProdutoraRecebe(config);
    *produtora = novoProdutora;
}

void menuProdutoraApagar(TipoProdutora* produtora, TipoConfig *config) {
    // Apaga os dados da produtora

    // Pede confirmacao
    if (recebeConfirma()) {
        produtoraInit(produtora);
        printMensagem("Dados apagados com sucesso","#");
    } else{
        printMensagem("Operacao cancelada","#");
    }

}

void menuTransacao(TipoProdutora* produtora, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha = 0;
    do{
        // Exibe o menu de Produtora
        printMenuTransacao(*produtora);

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 5, "Digite uma opcao", "#", config->validar_dados);

        switch(opcao) {
            case 1: {
                // Gerar conta a receber
                if(evento->status != STATUS_APROVADO) {
                    printf("Evento precisa estar aprovado!\n");
                    break;
                }

                int codigo = eventoGerarContaReceber(evento);
                if(codigo > 0) {
                    printf("\nConta #%d gerada com sucesso!\n", codigo);
                }
                break;
            }

            case 2: {
                // Receber pagamento
                float valor;
                int forma;

                printf("Valor a receber: R$ ");
                scanf("%f", &valor);

                printf("\nForma de pagamento:\n");
                printf("0-Dinheiro | 1-Débito | 2-Crédito | 3-PIX\n");
                printf("Escolha: ");
                scanf("%d", &forma);
                getchar();

                if(eventoReceberPagamento(evento->id, valor, (FormaPagamento)forma)) {
                    printf("\nPagamento recebido com sucesso!\n");
                }
                break;
            }

            case 3: {
                // Ver contas do evento
                printf("\n===== CONTAS A RECEBER DO EVENTO =====\n");
                extern ContaReceber contasReceber[];
                extern int totalContasReceber;

                int encontrou = 0;
                for(int i = 0; i < totalContasReceber; i++) {
                    if(contasReceber[i].codigoEvento == evento->id) {
                        encontrou = 1;
                        ContaReceber *cr = &contasReceber[i];
                        printf("\nConta #%d\n", cr->codigo);
                        printf("Valor Total: R$ %.2f\n", cr->valorTotal);
                        printf("Valor Pago: R$ %.2f\n", cr->valorPago);
                        printf("Valor Restante: R$ %.2f\n", cr->valorRestante);
                        printf("Status: %s\n", cr->pago ? "PAGO" : "EM ABERTO");
                        printf("Vencimento: %s\n", cr->dataVencimento);
                        printf("-----------------------------------\n");
                    }
                }

                if(!encontrou) {
                    printf("Nenhuma conta encontrada para este evento.\n");
                }
                break;
            }

            case 4: {
                // Atualizar margem de lucro
                float novaMargen;
                printf("Nova margem de lucro (%%): ");
                scanf("%f", &novaMargen);
                getchar();

                evento->margemLucro = novaMargen;
                eventoRecalcularTotais(evento);

                printf("Margem atualizada! Novo valor final: R$ %.2f\n",
                       evento->valorFinal);
                break;
            }

            case 0:
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
}

