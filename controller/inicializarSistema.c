#include "inicializarSistema.h"

int lerMemoria(TipoProdutora *produtora, ListaCliente** listaCliente, 
    ListaFornecedor** listaFornecedor, ListaEquipe** listaEquipe, 
    ListaRecurso** listaRecurso, ListaOperador** listaOperador) {
    // Tenta ler em TXT primeiro
    if (produtoraLerTXT(produtora)) {
        // se conseguiu ler txt, le tds os txt
        printMensagem("Lendo arquivos .txt","#");
        if(!clienteLerTXT(listaCliente)) printMensagem("Erro na leitura do cliente","ERRO");
        if(!equipeLerTXT(listaEquipe)) printMensagem("Erro na leitura do equipe","ERRO");
        if(!fornecedorLerTXT(listaFornecedor)) printMensagem("Erro na leitura do fornecedor","ERRO");
        if(!operadorLerTXT(listaOperador)) printMensagem("Erro na leitura do operador","ERRO");
        if(!recursoLerTXT(listaRecurso)) printMensagem("Erro na leitura do recurso","ERRO");
        return 1;
    } else if (produtoraLerBIN(produtora)){
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

int salvarMemoria(TipoProdutora *produtora, ListaCliente* listaCliente, 
    ListaFornecedor* listaFornecedor, ListaEquipe* listaEquipe, 
    ListaRecurso* listaRecurso, ListaOperador* listaOperador, int metodoDeSalvamento) {
    if (metodoDeSalvamento == 1) {
        // Salvar em txt
        printMensagem("Salvando arquivos .txt","#");
        produtoraSalvarTXT(produtora);
        clienteSalvarTXT(listaCliente);
        equipeSalvarTXT(listaEquipe);
        fornecedorSalvarTXT(listaFornecedor);
        operadorSalvarTXT(listaOperador);
        recursoSalvarTXT(listaRecurso);

        // Apaga arquivos binarios antigos
        remove("dados/produtora.bin");
        remove("dados/cliente.bin");
        remove("dados/equipe.bin");
        remove("dados/fornecedor.bin");
        remove("dados/operador.bin");
        remove("dados/recurso.bin");

        return 1;
    } else {
        // salvar em bin
        printMensagem("Salvando arquivos .bin","#");
        produtoraSalvarBIN(produtora);
        clienteSalvarBIN(listaCliente);
        equipeSalvarBIN(listaEquipe);
        fornecedorSalvarBIN(listaFornecedor);
        operadorSalvarBIN(listaOperador);
        recursoSalvarBIN(listaRecurso);

        // Apaga arquivos txt antigos
        remove("dados/produtora.txt");
        remove("dados/cliente.txt");
        remove("dados/equipe.txt");
        remove("dados/fornecedor.txt");
        remove("dados/operador.txt");
        remove("dados/recurso.txt");

        return 1;
    }

}

void inicializarSistema() {
    //===========================================
    // Limpa a tela do texto de compilacao
    limparTela();

    //===========================================
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
    
    // Tenta ler em TXT primeiro
    if (lerMemoria(&produtora, &listaCliente, &listaFornecedor, &listaEquipe, &listaRecurso, &listaOperador)) {
        // se conseguiu ler, avisa
        printMensagem("Dados carregados com sucesso","#");
    } else{
        // se n deu pra ler nenhum, recebe os dados iniciais da produtora
        printMensagem("Nenhuma produtora cadastrada","#");
        if(recebeInt(0, 1, "Cadastrar a produtora agora?", "1. Sim | 0. Nao") == 1)
            produtora = menuProdutoraRecebe();
    }

    //===========================================
    // Roda o menu principal
    menuPrincipal(&produtora, &listaCliente, &listaFornecedor, &listaEquipe, &listaRecurso, &listaOperador);

    //===========================================
    // Salva os dados na memoria
    salvarMemoria(&produtora, listaCliente, listaFornecedor, listaEquipe, listaRecurso, listaOperador, recebeMetodoDeSalvamento());

    //===========================================
    // Liberar memoria de tds as listas
    printMensagem("Liberando Memoria","#");
    clienteListaLiberar(listaCliente);
    equipeListaLiberar(listaEquipe);
    fornecedorListaLiberar(listaFornecedor);
    operadorListaLiberar(listaOperador);
    recursoListaLiberar(listaRecurso);
}