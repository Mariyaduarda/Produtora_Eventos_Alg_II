#include "inicializarSistema.h"

int lerMemoria(TipoConfig *config, TipoProdutora *produtora, ListaCliente** listaCliente, 
    ListaFornecedor** listaFornecedor, ListaEquipe** listaEquipe, 
    ListaRecurso** listaRecurso, ListaOperador** listaOperador) {
    // Tenta ler em TXT primeiro
    if (configLerTXT(config)) {
        // se conseguiu ler txt, le tds os txt
        printMensagem("Lendo arquivos .txt","#");
        if(!produtoraLerTXT(produtora)) printMensagem("Erro na leitura da produtora","ERRO");
        if(!clienteLerTXT(listaCliente)) printMensagem("Erro na leitura do cliente","ERRO");
        if(!equipeLerTXT(listaEquipe)) printMensagem("Erro na leitura do equipe","ERRO");
        if(!fornecedorLerTXT(listaFornecedor)) printMensagem("Erro na leitura do fornecedor","ERRO");
        if(!operadorLerTXT(listaOperador)) printMensagem("Erro na leitura do operador","ERRO");
        if(!recursoLerTXT(listaRecurso)) printMensagem("Erro na leitura do recurso","ERRO");
        return 1;
    } else if (configLerBIN(config)) {
        // se conseguiu ler binario, le tds os binarios

        printMensagem("Lendo arquivos .bin","#");
        clienteLerBIN(listaCliente);
        equipeLerBIN(listaEquipe);
        fornecedorLerBIN(listaFornecedor);
        operadorLerBIN(listaOperador);
        recursoLerBIN(listaRecurso);
        return 1;
    } else{
        // se n deu pra ler nenhum, retorna 0
        return 0;
    }
}

int salvarMemoria(TipoConfig *config, TipoProdutora *produtora, ListaCliente* listaCliente, 
    ListaFornecedor* listaFornecedor, ListaEquipe* listaEquipe, 
    ListaRecurso* listaRecurso, ListaOperador* listaOperador) {
    if (config->salvar_como_binario) {
        // salvar em bin
        printMensagem("Salvando arquivos .bin","#");
        produtoraSalvarBIN(produtora);
        clienteSalvarBIN(listaCliente);
        equipeSalvarBIN(listaEquipe);
        fornecedorSalvarBIN(listaFornecedor);
        operadorSalvarBIN(listaOperador);
        recursoSalvarBIN(listaRecurso);

        // Apaga arquivos txt antigos
        remove("dados/config.txt");
        remove("dados/produtora.txt");
        remove("dados/cliente.txt");
        remove("dados/equipe.txt");
        remove("dados/fornecedor.txt");
        remove("dados/operador.txt");
        remove("dados/recurso.txt");

        return 1;
    } else {
        // Salvar em txt
        printMensagem("Salvando arquivos .txt","#");
        produtoraSalvarTXT(produtora);
        clienteSalvarTXT(listaCliente);
        equipeSalvarTXT(listaEquipe);
        fornecedorSalvarTXT(listaFornecedor);
        operadorSalvarTXT(listaOperador);
        recursoSalvarTXT(listaRecurso);

        // Apaga arquivos binarios antigos
        remove("dados/config.bin");
        remove("dados/produtora.bin");
        remove("dados/cliente.bin");
        remove("dados/equipe.bin");
        remove("dados/fornecedor.bin");
        remove("dados/operador.bin");
        remove("dados/recurso.bin");

        return 1;
    }

}

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

    //===========================================
    // Le da memoria
    
    // Le as configuracoes
    if (configLerBIN(&config))      printMensagem("Config carregadas do binario","#");
    else if (configLerTXT(&config)) printMensagem("Config carregadas do texto","#");
    else                            printMensagem("Nenhuma configuracao encontrada, usando padrao","#");

    // Le os dados
    if (lerMemoria(&config, &produtora, &listaCliente, &listaFornecedor, &listaEquipe, &listaRecurso, &listaOperador)) {
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
    menuPrincipal(&config, &produtora, &listaCliente, &listaFornecedor, &listaEquipe, &listaRecurso, &listaOperador);

    //===========================================
    // Salva os dados na memoria
    salvarMemoria(&config, &produtora, 
        listaCliente, listaFornecedor, 
        listaEquipe, listaRecurso, listaOperador);

    //===========================================
    // Liberar memoria de tds as listas
    printMensagem("Liberando Memoria","#");
    clienteListaLiberar(listaCliente);
    equipeListaLiberar(listaEquipe);
    fornecedorListaLiberar(listaFornecedor);
    operadorListaLiberar(listaOperador);
    recursoListaLiberar(listaRecurso);
}