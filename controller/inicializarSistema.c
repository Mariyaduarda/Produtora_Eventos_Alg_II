#include "inicializarSistema.h"

void inicializarSistema() {
    //===========================================
    // Limpa a tela do texto de compilacao
    limparTela();

    //===========================================
    // Inicia as estruturas principais

    // Declara a Configuracao
    TipoConfig config;
    configInit(&config);

    // Declara a Produtora
    TipoProdutora produtora;
    produtoraInit(&produtora);

    // Declara as listas
    ListaCliente* listaCliente = NULL;
    ListaFornecedor* listaFornecedor = NULL;
    ListaEquipe* listaEquipe = NULL;
    ListaRecurso* listaRecurso = NULL;
    ListaOperador* listaOperador = NULL;
    ListaEvento* listaEvento = NULL;
    ListaMovimentacao* listaMovimentacao = NULL;
    ListaContaReceber* listaContaReceber = NULL;
    ListaContaPagar* listaContaPagar = NULL;

    //===========================================
    // Le da memoria
    
    // Le as configuracoes
    if (configLerBIN(&config))      printMensagem("Config carregadas do binario","#");
    else if (configLerTXT(&config)) printMensagem("Config carregadas do texto","#");
    else                            printMensagem("Nenhuma configuracao encontrada, usando padrao","#");

    // Le os dados
    if (lerMemoria(&config, &produtora, &listaCliente, &listaFornecedor, 
        &listaEquipe, &listaEvento, &listaRecurso, &listaOperador, 
        &listaMovimentacao, &listaContaReceber, &listaContaPagar)) {
        // se conseguiu ler, avisa
        printMensagem("Dados carregados com sucesso","#");
    } else{
        // se n deu pra ler nenhum, recebe os dados iniciais da produtora
        printMensagem("Nenhuma produtora cadastrada","#");
        if(recebeInt(0, 1, "Cadastrar a produtora agora?", "1. Sim | 0. Nao", config.validar_dados) == 1)
            produtora = menuProdutoraRecebe(&config);
    }

    //===========================================
    // Roda o menu principal
    menuPrincipal(&config, &produtora, &listaCliente, &listaFornecedor,
        &listaEquipe, &listaRecurso, &listaEvento, &listaOperador, 
        &listaMovimentacao, &listaContaReceber, &listaContaPagar);

    //===========================================
    // Salva as configuracoes
    if (config.salvar_como_binario) {
        configSalvarBIN(config);
        remove("config.txt");
        printMensagem("Configuracoes salvas em binario","#");
    } else {
        configSalvarTXT(config);
        remove("config.bin");
        printMensagem("Configuracoes salvas em texto","#");
    }
    // Salva os dados na memoria
    salvarMemoria(&config, &produtora, listaCliente, listaFornecedor,
        listaEquipe,  listaEvento, listaRecurso, listaOperador, 
        listaMovimentacao, listaContaReceber, listaContaPagar);

    //===========================================
    // Liberar memoria de tds as listas
    printMensagem("Liberando Memoria","#");
    clienteListaLiberar(listaCliente);
    equipeListaLiberar(listaEquipe);
    fornecedorListaLiberar(listaFornecedor);
    operadorListaLiberar(listaOperador);
    recursoListaLiberar(listaRecurso);
    eventoListaLiberar(listaEvento);
    movimentacaoListaLiberar(listaMovimentacao);
    contaReceberListaLiberar(listaContaReceber);
    contaPagarListaLiberar(listaContaPagar);

    printf("\n\n");
}