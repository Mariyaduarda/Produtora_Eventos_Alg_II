#include "transacao.h"

// ===== INICIALIZAÇÃO =====

void movimentacaoCaixaInit(MovimentacaoCaixa *mov) {
    mov->id = 0;
    strcpy(mov->data, "");
    strcpy(mov->hora, "");
    mov->tipo = TIPO_ENTRADA;
    mov->valor = 0.0;
    mov->formaPagamento = FORMA_DINHEIRO;
    strcpy(mov->descricao, "");
    mov->codigoEvento = 0;
}

void contaReceberInit(ContaReceber *cr) {
    cr->codigo = 0;
    cr->codigoCliente = 0;
    cr->codigoEvento = 0;
    cr->valorTotal = 0.0;
    cr->valorPago = 0.0;
    cr->valorRestante = 0.0;
    strcpy(cr->dataEmissao, "");
    strcpy(cr->dataVencimento, "");
    strcpy(cr->dataPagamento, "");
    cr->pago = false;
    strcpy(cr->observacoes, "");
}

void contaPagarInit(ContaPagar *cp) {
    cp->codigo = 0;
    cp->codigoFornecedor = 0;
    cp->valorTotal = 0.0;
    cp->valorPago = 0.0;
    cp->valorRestante = 0.0;
    strcpy(cp->dataEmissao, "");
    strcpy(cp->dataVencimento, "");
    strcpy(cp->dataPagamento, "");
    cp->pago = false;
    strcpy(cp->descricao, "");
}

// ===== INICIALIZAÇÃO DE LISTAS =====

void listaMovimentacaoInit(ListaMovimentacao **lista) {
    *lista = NULL;
}

void listaContaReceberInit(ListaContaReceber **lista) {
    *lista = NULL;
}

void listaContaPagarInit(ListaContaPagar **lista) {
    *lista = NULL;
}

// ===== FUNÇÕES AUXILIARES =====

void obterDataAtual(char *data) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void obterDataHoraAtual(char *data, char *hora) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    sprintf(hora, "%02d:%02d", tm.tm_hour, tm.tm_min);
}

void calcularDataVencimento(char *dataVenc, int dias) {
    time_t t = time(NULL);
    t += dias * 24 * 60 * 60; // adiciona dias em segundos
    struct tm tm = *localtime(&t);
    sprintf(dataVenc, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// ===== CRUD MOVIMENTAÇÃO DE CAIXA =====

int movimentacaoAdicionar(ListaMovimentacao **lista, MovimentacaoCaixa mov) {
    ListaMovimentacao *novo = (ListaMovimentacao *)malloc(sizeof(ListaMovimentacao));
    if (novo == NULL) return 0;

    novo->movimentacao = mov;
    novo->prox = NULL;

    if (*lista == NULL) {
        novo->movimentacao.id = 1;
        *lista = novo;
    } else {
        ListaMovimentacao *atual = *lista;
        while (atual->prox != NULL) atual = atual->prox;

        novo->movimentacao.id = atual->movimentacao.id + 1;
        atual->prox = novo;
    }

    return novo->movimentacao.id;
}

MovimentacaoCaixa* movimentacaoBuscar(ListaMovimentacao *lista, int id) {
    ListaMovimentacao *atual = lista;

    while (atual != NULL) {
        if (atual->movimentacao.id == id) {
            return &atual->movimentacao;
        }
        atual = atual->prox;
    }

    return NULL;
}

void movimentacaoListaLiberar(ListaMovimentacao *lista) {
    while (lista != NULL) {
        ListaMovimentacao *aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

// ===== CRUD CONTA A RECEBER =====

int contaReceberAdicionar(ListaContaReceber **lista, ContaReceber conta) {
    ListaContaReceber *novo = (ListaContaReceber *)malloc(sizeof(ListaContaReceber));
    if (novo == NULL) return 0;

    novo->conta = conta;
    novo->prox = NULL;

    if (*lista == NULL) {
        novo->conta.codigo = 1;
        *lista = novo;
    } else {
        ListaContaReceber *atual = *lista;
        while (atual->prox != NULL) atual = atual->prox;

        novo->conta.codigo = atual->conta.codigo + 1;
        atual->prox = novo;
    }

    return novo->conta.codigo;
}

ContaReceber* contaReceberBuscar(ListaContaReceber *lista, int codigo) {
    ListaContaReceber *atual = lista;

    while (atual != NULL) {
        if (atual->conta.codigo == codigo) {
            return &atual->conta;
        }
        atual = atual->prox;
    }

    return NULL;
}

ContaReceber* contaReceberBuscarPorEvento(ListaContaReceber *lista, int codigoEvento) {
    ListaContaReceber *atual = lista;

    while (atual != NULL) {
        if (atual->conta.codigoEvento == codigoEvento && !atual->conta.pago) {
            return &atual->conta;
        }
        atual = atual->prox;
    }

    return NULL;
}

void contaReceberListaLiberar(ListaContaReceber *lista) {
    while (lista != NULL) {
        ListaContaReceber *aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

// ===== CRUD CONTA A PAGAR =====

int contaPagarAdicionar(ListaContaPagar **lista, ContaPagar conta) {
    ListaContaPagar *novo = (ListaContaPagar *)malloc(sizeof(ListaContaPagar));
    if (novo == NULL) return 0;

    novo->conta = conta;
    novo->prox = NULL;

    if (*lista == NULL) {
        novo->conta.codigo = 1;
        *lista = novo;
    } else {
        ListaContaPagar *atual = *lista;
        while (atual->prox != NULL) atual = atual->prox;

        novo->conta.codigo = atual->conta.codigo + 1;
        atual->prox = novo;
    }

    return novo->conta.codigo;
}

ContaPagar* contaPagarBuscar(ListaContaPagar *lista, int codigo) {
    ListaContaPagar *atual = lista;

    while (atual != NULL) {
        if (atual->conta.codigo == codigo) {
            return &atual->conta;
        }
        atual = atual->prox;
    }

    return NULL;
}

void contaPagarListaLiberar(ListaContaPagar *lista) {
    while (lista != NULL) {
        ListaContaPagar *aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

// ===== FUNÇÕES DE CAIXA =====

float obterSaldoCaixa(ListaMovimentacao *lista) {
    float saldo = 0.0;
    ListaMovimentacao *atual = lista;

    while (atual != NULL) {
        if (atual->movimentacao.tipo == TIPO_ENTRADA) {
            saldo += atual->movimentacao.valor;
        } else {
            saldo -= atual->movimentacao.valor;
        }
        atual = atual->prox;
    }

    return saldo;
}

int registrarEntradaCaixa(ListaMovimentacao **lista, float valor, FormaPagamento forma,
                          const char* descricao, int codigoEvento) {
    MovimentacaoCaixa mov;
    movimentacaoCaixaInit(&mov);

    obterDataHoraAtual(mov.data, mov.hora);
    mov.tipo = TIPO_ENTRADA;
    mov.valor = valor;
    mov.formaPagamento = forma;
    strncpy(mov.descricao, descricao, 199);
    mov.descricao[199] = '\0';
    mov.codigoEvento = codigoEvento;

    return movimentacaoAdicionar(lista, mov);
}

int registrarSaidaCaixa(ListaMovimentacao **lista, float valor, const char* descricao) {
    float saldo = obterSaldoCaixa(*lista);

    if (saldo < valor) {
        printf("Erro: Saldo insuficiente em caixa (Saldo: R$ %.2f | Necessario: R$ %.2f)!\n",
               saldo, valor);
        return 0;
    }

    MovimentacaoCaixa mov;
    movimentacaoCaixaInit(&mov);

    obterDataHoraAtual(mov.data, mov.hora);
    mov.tipo = TIPO_SAIDA;
    mov.valor = valor;
    mov.formaPagamento = FORMA_DINHEIRO;
    strncpy(mov.descricao, descricao, 199);
    mov.descricao[199] = '\0';
    mov.codigoEvento = 0;

    return movimentacaoAdicionar(lista, mov);
}

// ===== FUNÇÕES DE CONTAS A RECEBER =====

int gerarContaReceber(ListaContaReceber **lista, int codigoCliente, int codigoEvento, float valor) {
    ContaReceber cr;
    contaReceberInit(&cr);

    cr.codigoCliente = codigoCliente;
    cr.codigoEvento = codigoEvento;
    cr.valorTotal = valor;
    cr.valorPago = 0.0;
    cr.valorRestante = valor;
    obterDataAtual(cr.dataEmissao);
    calcularDataVencimento(cr.dataVencimento, 30); // 30 dias
    cr.pago = false;
    strcpy(cr.dataPagamento, "");
    strcpy(cr.observacoes, "");

    return contaReceberAdicionar(lista, cr);
}

int baixarContaReceber(ListaContaReceber *lista, ListaMovimentacao **listaMov,
                       int codigoConta, float valorPagamento, FormaPagamento forma) {
    ContaReceber* cr = contaReceberBuscar(lista, codigoConta);
    if (cr == NULL) {
        printf("Erro: Conta não encontrada!\n");
        return 0;
    }

    if (cr->pago) {
        printf("Erro: Conta ja esta paga!\n");
        return 0;
    }

    if (valorPagamento > cr->valorRestante) {
        printf("Erro: Valor de pagamento (R$ %.2f) maior que o devido (R$ %.2f)!\n",
               valorPagamento, cr->valorRestante);
        return 0;
    }

    cr->valorPago += valorPagamento;
    cr->valorRestante -= valorPagamento;

    // Se pagou tudo (margem de 0.01 para erros de ponto flutuante)
    if (cr->valorRestante <= 0.01) {
        cr->pago = true;
        obterDataAtual(cr->dataPagamento);
    }

    // Registra entrada no caixa (exceto credito)
    if (forma != FORMA_CREDITO) {
        char desc[200];
        snprintf(desc, 200, "Recebimento cliente - Conta %d - Evento %d",
                codigoConta, cr->codigoEvento);
        registrarEntradaCaixa(listaMov, valorPagamento, forma, desc, cr->codigoEvento);
    }

    printf("Pagamento de R$ %.2f registrado com sucesso!\n", valorPagamento);
    if (cr->pago) {
        printf("Conta totalmente quitada!\n");
    } else {
        printf("Valor restante: R$ %.2f\n", cr->valorRestante);
    }

    return 1;
}

// ===== FUNÇÕES DE CONTAS A PAGAR =====

int gerarContaPagar(ListaContaPagar **lista, int codigoFornecedor, float valor,
                    int diasVencimento, const char* descricao) {
    ContaPagar cp;
    contaPagarInit(&cp);

    cp.codigoFornecedor = codigoFornecedor;
    cp.valorTotal = valor;
    cp.valorPago = 0.0;
    cp.valorRestante = valor;
    obterDataAtual(cp.dataEmissao);
    calcularDataVencimento(cp.dataVencimento, diasVencimento);
    cp.pago = false;
    strcpy(cp.dataPagamento, "");
    strncpy(cp.descricao, descricao, 199);
    cp.descricao[199] = '\0';

    return contaPagarAdicionar(lista, cp);
}

int baixarContaPagar(ListaContaPagar *lista, ListaMovimentacao **listaMov, int codigoConta) {
    ContaPagar* cp = contaPagarBuscar(lista, codigoConta);
    if (cp == NULL) {
        printMensagem("Conta nao encontrada!", "ERRO");
        return 0;
    }

    if (cp->pago) {
        printMensagem("Conta ja esta paga!", "ERRO");
        return 0;
    }

    float valor = cp->valorRestante;

    // Registra saída no caixa
    char desc[200];
    snprintf(desc, 200, "Pagamento - %s", cp->descricao);

    if (!registrarSaidaCaixa(listaMov, valor, desc)) {
        return 0;
    }

    cp->valorPago = cp->valorTotal;
    cp->valorRestante = 0.0;
    cp->pago = true;
    obterDataAtual(cp->dataPagamento);

    printMensagem("Conta paga com sucesso!", "SUCESSO");
    return 1;
}

// ===== INTEGRAÇÃO COM EVENTOS =====

int eventoGerarContaReceber(TipoEvento *evento, ListaContaReceber **lista) {
    if (evento == NULL) {
        printMensagem("Evento invalido!", "ERRO");
        return 0;
    }

    if (evento->status != STATUS_APROVADO) {
        printMensagem("Evento precisa estar aprovado para gerar conta a receber!", "ERRO");
        return 0;
    }

    // Gera conta a receber
    int codigoConta = gerarContaReceber(
        lista,
        evento->codigoCliente,
        evento->id,
        evento->valorFinal
    );

    if (codigoConta > 0) {
        printMensagem("Conta a receber gerada com sucesso!", "SUCESSO");
        printf("Cliente: %d | Evento: %d | Valor: R$ %.2f\n",
               evento->codigoCliente, evento->id, evento->valorFinal);
        return codigoConta;
    }

    return 0;
}

int eventoReceberPagamento(int codigoEvento, ListaContaReceber *lista,
                           ListaMovimentacao **listaMov, float valor, FormaPagamento forma) {
    // Busca conta a receber relacionada ao evento
    ContaReceber *cr = contaReceberBuscarPorEvento(lista, codigoEvento);

    if (cr == NULL) {
        printf("Erro: Nenhuma conta a receber em aberto para este evento!\n");
        return 0;
    }

    return baixarContaReceber(lista, listaMov, cr->codigo, valor, forma);
}

// ===== RELATÓRIOS =====
void relatorioFluxoCaixa(ListaMovimentacao *lista) {
    printf("\n========== FLUXO DE CAIXA ==========\n");
    printf("Saldo Atual: R$ %.2f\n\n", obterSaldoCaixa(lista));

    printf("%-6s %-12s %-8s %-10s %-10s %-15s %-30s\n",
           "ID", "Data", "Hora", "Tipo", "Valor", "Forma Pgto", "Descrição");
    printf("----------------------------------------------------------------------------------------\n");

    ListaMovimentacao *atual = lista;
    while (atual != NULL) {
        MovimentacaoCaixa *m = &atual->movimentacao;
        const char *tipo = (m->tipo == TIPO_ENTRADA) ? "ENTRADA" : "SAÍDA";
        const char *forma = (m->formaPagamento == FORMA_DINHEIRO) ? "Dinheiro" :
                           (m->formaPagamento == FORMA_PIX) ? "PIX" :
                           (m->formaPagamento == FORMA_DEBITO) ? "Debito" : "Credito";

        printf("%-6d %-12s %-8s %-10s R$ %8.2f %-15s %-30s\n",
               m->id, m->data, m->hora, tipo, m->valor, forma, m->descricao);

        atual = atual->prox;
    }
}

void relatorioContasReceber(ListaContaReceber *lista) {
    printf("\n========== CONTAS A RECEBER ==========\n");

    float totalAberto = 0.0;
    float totalRecebido = 0.0;

    ListaContaReceber *atual = lista;
    while (atual != NULL) {
        ContaReceber *cr = &atual->conta;
        totalRecebido += cr->valorPago;
        totalAberto += cr->valorRestante;

        printf("\nConta: %d | Cliente: %d | Evento: %d\n",
               cr->codigo, cr->codigoCliente, cr->codigoEvento);
        printf("Valor Total: R$ %.2f | Pago: R$ %.2f | Restante: R$ %.2f\n",
               cr->valorTotal, cr->valorPago, cr->valorRestante);
        printf("Emissão: %s | Vencimento: %s | Status: %s\n",
               cr->dataEmissao, cr->dataVencimento, cr->pago ? "PAGO" : "EM ABERTO");
        printf("---------------------------------------------------\n");

        atual = atual->prox;
    }

    printf("\nTotal Recebido: R$ %.2f\n", totalRecebido);
    printf("Total em Aberto: R$ %.2f\n", totalAberto);
}

void relatorioContasPagar(ListaContaPagar *lista) {
    printf("\n========== CONTAS A PAGAR ==========\n");

    float totalAberto = 0.0;
    float totalPago = 0.0;

    ListaContaPagar *atual = lista;
    while (atual != NULL) {
        ContaPagar *cp = &atual->conta;
        totalPago += cp->valorPago;
        totalAberto += cp->valorRestante;

        printf("\nConta: %d | Fornecedor: %d\n", cp->codigo, cp->codigoFornecedor);
        printf("Descrição: %s\n", cp->descricao);
        printf("Valor Total: R$ %.2f | Pago: R$ %.2f | Restante: R$ %.2f\n",
               cp->valorTotal, cp->valorPago, cp->valorRestante);
        printf("Emissão: %s | Vencimento: %s | Status: %s\n",
               cp->dataEmissao, cp->dataVencimento, cp->pago ? "PAGO" : "EM ABERTO");
        printf("---------------------------------------------------\n");

        atual = atual->prox;
    }

    printf("\nTotal Pago: R$ %.2f\n", totalPago);
    printf("Total em Aberto: R$ %.2f\n", totalAberto);
}

// Adicione estas funções ao arquivo transacao.c

// ===== PERSISTÊNCIA - MOVIMENTAÇÕES =====

int movimentacaoSalvarTXT(ListaMovimentacao *lista){
    FILE* fp = fopen("dados/movimentacoes.txt", "w");
    if(fp == NULL) return 0;
    if (lista == NULL) { fclose(fp); return 0; }
    ListaMovimentacao* aux = lista;
    while (aux != NULL) {
        fprintf(fp, "%d,%s,%s,%d,%.2f,%d,%s,%d\n",
        aux->movimentacao.id,
        aux->movimentacao.data,
        aux->movimentacao.hora,
        aux->movimentacao.tipo,
        aux->movimentacao.valor,
        aux->movimentacao.formaPagamento,
        aux->movimentacao.descricao,
        aux->movimentacao.codigoEvento);
        aux = aux->prox;
    }
    fclose(fp);
    return 1;
}

int movimentacaoLerTXT(ListaMovimentacao **lista) {
    FILE *fp = fopen("dados/movimentacoes.txt", "r");
    if(fp == NULL) return 0;
    MovimentacaoCaixa temp;
    int tipo, forma;
    while(fscanf(fp, "%d,%[^,],%[^,],%d,%f,%d,%[^,],%d\n",
        &temp.id,
        temp.data,
        temp.hora,
        &tipo,
        &temp.valor,
        &forma,
        temp.descricao,
        &temp.codigoEvento) == 8)
    {
        temp.tipo = (TipoTransacao)tipo;
        temp.formaPagamento = (FormaPagamento)forma;
        movimentacaoAdicionar(lista, temp);
    }
    fclose(fp);
    return 1;
}

int movimentacaoSalvarBIN(ListaMovimentacao* lista) {
    FILE* fp = fopen("dados/movimentacoes.bin", "wb");
    if (fp == NULL) return 0;
    if (lista == NULL) { fclose(fp); return 0; }
    ListaMovimentacao* aux = lista;
    while (aux != NULL) {
        fwrite(&aux->movimentacao, sizeof(MovimentacaoCaixa), 1, fp);
        aux = aux->prox;
    }
    fclose(fp);
    return 1;
}

int movimentacaoLerBIN(ListaMovimentacao** lista) {
    FILE* fp = fopen("dados/movimentacoes.bin", "rb");
    if (fp == NULL) return 0;
    MovimentacaoCaixa temp;
    while (fread(&temp, sizeof(MovimentacaoCaixa), 1, fp) == 1) {
        movimentacaoAdicionar(lista, temp);
    }
    fclose(fp);
    return 1;
}

// ===== PERSISTÊNCIA - CONTAS A RECEBER =====

int contaReceberSalvarTXT(ListaContaReceber *lista){
    FILE* fp = fopen("dados/contas_receber.txt", "w");
    if(fp == NULL) return 0;
    if (lista == NULL) { fclose(fp); return 0; }
    ListaContaReceber* aux = lista;
    while (aux != NULL) {
        fprintf(fp, "%d,%d,%d,%.2f,%.2f,%.2f,%s,%s,%s,%d,%s\n",
        aux->conta.codigo,
        aux->conta.codigoCliente,
        aux->conta.codigoEvento,
        aux->conta.valorTotal,
        aux->conta.valorPago,
        aux->conta.valorRestante,
        aux->conta.dataEmissao,
        aux->conta.dataVencimento,
        aux->conta.dataPagamento,
        aux->conta.pago ? 1 : 0,
        aux->conta.observacoes);
        aux = aux->prox;
    }
    fclose(fp);
    return 1;
}

int contaReceberLerTXT(ListaContaReceber **lista) {
    FILE *fp = fopen("dados/contas_receber.txt", "r");
    if(fp == NULL) return 0;
    ContaReceber temp;
    int pago;
    while(fscanf(fp, "%d,%d,%d,%f,%f,%f,%[^,],%[^,],%[^,],%d,%[^\n]\n",
        &temp.codigo,
        &temp.codigoCliente,
        &temp.codigoEvento,
        &temp.valorTotal,
        &temp.valorPago,
        &temp.valorRestante,
        temp.dataEmissao,
        temp.dataVencimento,
        temp.dataPagamento,
        &pago,
        temp.observacoes) == 11)
    {
        temp.pago = (pago == 1);
        contaReceberAdicionar(lista, temp);
    }
    fclose(fp);
    return 1;
}

int contaReceberSalvarBIN(ListaContaReceber* lista) {
    FILE* fp = fopen("dados/contas_receber.bin", "wb");
    if (fp == NULL) return 0;
    if (lista == NULL) { fclose(fp); return 0; }
    ListaContaReceber* aux = lista;
    while (aux != NULL) {
        fwrite(&aux->conta, sizeof(ContaReceber), 1, fp);
        aux = aux->prox;
    }
    fclose(fp);
    return 1;
}

int contaReceberLerBIN(ListaContaReceber** lista) {
    FILE* fp = fopen("dados/contas_receber.bin", "rb");
    if (fp == NULL) return 0;
    ContaReceber temp;
    while (fread(&temp, sizeof(ContaReceber), 1, fp) == 1) {
        contaReceberAdicionar(lista, temp);
    }
    fclose(fp);
    return 1;
}

// ===== PERSISTÊNCIA - CONTAS A PAGAR =====

int contaPagarSalvarTXT(ListaContaPagar *lista){
    FILE* fp = fopen("dados/contas_pagar.txt", "w");
    if(fp == NULL) return 0;
    if (lista == NULL) { fclose(fp); return 0; }
    ListaContaPagar* aux = lista;
    while (aux != NULL) {
        fprintf(fp, "%d,%d,%.2f,%.2f,%.2f,%s,%s,%s,%d,%s\n",
        aux->conta.codigo,
        aux->conta.codigoFornecedor,
        aux->conta.valorTotal,
        aux->conta.valorPago,
        aux->conta.valorRestante,
        aux->conta.dataEmissao,
        aux->conta.dataVencimento,
        aux->conta.dataPagamento,
        aux->conta.pago ? 1 : 0,
        aux->conta.descricao);
        aux = aux->prox;
    }
    fclose(fp);
    return 1;
}

int contaPagarLerTXT(ListaContaPagar **lista) {
    FILE *fp = fopen("dados/contas_pagar.txt", "r");
    if(fp == NULL) return 0;
    ContaPagar temp;
    int pago;
    while(fscanf(fp, "%d,%d,%f,%f,%f,%[^,],%[^,],%[^,],%d,%[^\n]\n",
        &temp.codigo,
        &temp.codigoFornecedor,
        &temp.valorTotal,
        &temp.valorPago,
        &temp.valorRestante,
        temp.dataEmissao,
        temp.dataVencimento,
        temp.dataPagamento,
        &pago,
        temp.descricao) == 10)
    {
        temp.pago = (pago == 1);
        contaPagarAdicionar(lista, temp);
    }
    fclose(fp);
    return 1;
}

int contaPagarSalvarBIN(ListaContaPagar* lista) {
    FILE* fp = fopen("dados/contas_pagar.bin", "wb");
    if (fp == NULL) return 0;
    if (lista == NULL) { fclose(fp); return 0; }
    ListaContaPagar* aux = lista;
    while (aux != NULL) {
        fwrite(&aux->conta, sizeof(ContaPagar), 1, fp);
        aux = aux->prox;
    }
    fclose(fp);
    return 1;
}

int contaPagarLerBIN(ListaContaPagar** lista) {
    FILE* fp = fopen("dados/contas_pagar.bin", "rb");
    if (fp == NULL) return 0;
    ContaPagar temp;
    while (fread(&temp, sizeof(ContaPagar), 1, fp) == 1) {
        contaPagarAdicionar(lista, temp);
    }
    fclose(fp);
    return 1;
}

// ===== FUNÇÃO AUXILIAR PARA SALVAR TUDO =====

int transacaoSalvarTudo(ListaMovimentacao *listaMov, ListaContaReceber *listaCR,
                        ListaContaPagar *listaCP, int tipoArquivo) {
    // tipoArquivo: 0 = TXT, 1 = BIN

    int sucesso = 1;

    if (tipoArquivo == 0) {
        // Salvar em TXT
        sucesso &= movimentacaoSalvarTXT(listaMov);
        sucesso &= contaReceberSalvarTXT(listaCR);
        sucesso &= contaPagarSalvarTXT(listaCP);
    } else {
        // Salvar em BIN
        sucesso &= movimentacaoSalvarBIN(listaMov);
        sucesso &= contaReceberSalvarBIN(listaCR);
        sucesso &= contaPagarSalvarBIN(listaCP);
    }

    return sucesso;
}

int transacaoCarregarTudo(ListaMovimentacao **listaMov, ListaContaReceber **listaCR,
                         ListaContaPagar **listaCP, int tipoArquivo) {
    // tipoArquivo: 0 = TXT, 1 = BIN

    int sucesso = 1;

    if (tipoArquivo == 0) {
        // Carregar de TXT
        sucesso &= movimentacaoLerTXT(listaMov);
        sucesso &= contaReceberLerTXT(listaCR);
        sucesso &= contaPagarLerTXT(listaCP);
    } else {
        // Carregar de BIN
        sucesso &= movimentacaoLerBIN(listaMov);
        sucesso &= contaReceberLerBIN(listaCR);
        sucesso &= contaPagarLerBIN(listaCP);
    }

    return sucesso;
}