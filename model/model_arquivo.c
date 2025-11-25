#include "model_arquivo.h"


// encapsulamento das funcoes de leitura e escrita de todas as estruturas

int lerMemoria(TipoConfig *config, TipoProdutora *produtora, ListaCliente** listaCliente, 
    ListaFornecedor** listaFornecedor, ListaEquipe** listaEquipe, ListaEvento** listaEvento,
    ListaRecurso** listaRecurso, ListaOperador** listaOperador, ListaMovimentacao** listaMovimentacao,
    ListaContaReceber** listaContaReceber, ListaContaPagar** listaContaPagar) {
    // Tenta ler em TXT primeiro
    if (configLerTXT(config)) {
        // se conseguiu ler txt, le tds os txt
        printMensagem("Lendo arquivos .txt","#");
        // produtora
        if(!produtoraLerTXT(produtora)) printMensagem("Erro na leitura da produtora","ERRO");
        // listas
        if(!clienteLerTXT(listaCliente)) printMensagem("Erro na leitura do cliente","ERRO");
        if(!equipeLerTXT(listaEquipe)) printMensagem("Erro na leitura do equipe","ERRO");
        if(!fornecedorLerTXT(listaFornecedor)) printMensagem("Erro na leitura do fornecedor","ERRO");
        if(!operadorLerTXT(listaOperador)) printMensagem("Erro na leitura do operador","ERRO");
        if(!recursoLerTXT(listaRecurso)) printMensagem("Erro na leitura do recurso","ERRO");
        if(!eventoLerTXT(listaEvento)) printMensagem("Erro na leitura do evento","ERRO");
        // transacoes
        if(!movimentacaoLerTXT(listaMovimentacao)) printMensagem("Erro na leitura da movimentacao","ERRO");
        if(!contaReceberLerTXT(listaContaReceber)) printMensagem("Erro na leitura da conta a receber","ERRO");
        if(!contaPagarLerTXT(listaContaPagar)) printMensagem("Erro na leitura da conta a pagar","ERRO");

        return 1;
    } else if (configLerBIN(config)) {
        // se conseguiu ler binario, le tds os binarios

        printMensagem("Lendo arquivos .bin","#");
        clienteLerBIN(listaCliente);
        equipeLerBIN(listaEquipe);
        fornecedorLerBIN(listaFornecedor);
        operadorLerBIN(listaOperador);
        recursoLerBIN(listaRecurso);
        eventoLerBIN(listaEvento);
        movimentacaoLerBIN(listaMovimentacao);
        contaReceberLerBIN(listaContaReceber);
        contaPagarLerBIN(listaContaPagar);
        return 1;
    } else{
        // se n deu pra ler nenhum, retorna 0
        return 0;
    }
}

int salvarMemoria(TipoConfig *config, TipoProdutora *produtora, ListaCliente *listaCliente, 
    ListaFornecedor *listaFornecedor, ListaEquipe *listaEquipe, ListaEvento *listaEvento,
    ListaRecurso *listaRecurso, ListaOperador *listaOperador, ListaMovimentacao *listaMovimentacao,
    ListaContaReceber *listaContaReceber, ListaContaPagar *listaContaPagar) {
    if (config->salvar_como_binario) {
        // salvar em bin
        printMensagem("Salvando arquivos .bin","#");
        // produtora
        produtoraSalvarBIN(produtora);
        // listas
        clienteSalvarBIN(listaCliente);
        equipeSalvarBIN(listaEquipe);
        fornecedorSalvarBIN(listaFornecedor);
        operadorSalvarBIN(listaOperador);
        recursoSalvarBIN(listaRecurso);
        eventoSalvarBIN(listaEvento);
        // transacoes
        movimentacaoSalvarBIN(listaMovimentacao);
        contaReceberSalvarBIN(listaContaReceber);
        contaPagarSalvarBIN(listaContaPagar);

        // Apaga arquivos txt antigos
        remove("dados/config.txt");
        remove("dados/produtora.txt");
        remove("dados/cliente.txt");
        remove("dados/equipe.txt");
        remove("dados/fornecedor.txt");
        remove("dados/operador.txt");
        remove("dados/recurso.txt");
        remove("dados/evento.txt");
        remove("dados/movimentacao.txt");
        remove("dados/contaReceber.txt");
        remove("dados/contaPagar.txt");

        return 1;
    } else {
        // Salvar em txt
        printMensagem("Salvando arquivos .txt","#");
        // produtora
        produtoraSalvarTXT(produtora);
        // listas
        clienteSalvarTXT(listaCliente);
        equipeSalvarTXT(listaEquipe);
        fornecedorSalvarTXT(listaFornecedor);
        operadorSalvarTXT(listaOperador);
        recursoSalvarTXT(listaRecurso);
        eventoSalvarTXT(listaEvento);
        // transacoes
        movimentacaoSalvarTXT(listaMovimentacao);
        contaReceberSalvarTXT(listaContaReceber);
        contaPagarSalvarTXT(listaContaPagar);

        // Apaga arquivos binarios antigos
        remove("dados/config.bin");
        remove("dados/produtora.bin");
        remove("dados/cliente.bin");
        remove("dados/equipe.bin");
        remove("dados/fornecedor.bin");
        remove("dados/operador.bin");
        remove("dados/recurso.bin");
        remove("dados/evento.bin");
        remove("dados/movimentacao.bin");
        remove("dados/contaReceber.bin");
        remove("dados/contaPagar.bin");

        return 1;
    }

}
