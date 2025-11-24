#include "model_arquivo.h"


// encapsulamento das funcoes de leitura e escrita de todas as estruturas

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
        eventoSalvarBIN(listaEvento);

        // Apaga arquivos txt antigos
        remove("dados/config.txt");
        remove("dados/produtora.txt");
        remove("dados/cliente.txt");
        remove("dados/equipe.txt");
        remove("dados/fornecedor.txt");
        remove("dados/operador.txt");
        remove("dados/recurso.txt");
        remove("dados/evento.txt");

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
        eventoSalvarTXT(ListaEvento *listaEvento);
        movimentacaoSalvarTXT(ListaMovimentacao *lista);

        // Apaga arquivos binarios antigos
        remove("dados/config.bin");
        remove("dados/produtora.bin");
        remove("dados/cliente.bin");
        remove("dados/equipe.bin");
        remove("dados/fornecedor.bin");
        remove("dados/operador.bin");
        remove("dados/recurso.bin");
        remove("dados/evento.bin");
        remove("dados/transacoes.bin");

        return 1;
    }

}
