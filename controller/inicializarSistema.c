#include "inicializarSistema.h"

void inicializarSistema() {
    
    //===========================================
    // Declara as listas
    ListaCliente* listaCliente = NULL;
    ListaFornecedor* listaFornecedor = NULL;
    ListaProdutora* listaProdutora = NULL;
    ListaEquipe* listaEquipe = NULL;
    ListaRecurso* listaRecurso = NULL;
    ListaOperador* listaOperador = NULL;

    //===========================================
    // Le da memoria
    
    // Tenta ler em TXT primeiro
    if (produtoraLerTXT(&listaProdutora)) {
        // se conseguiu ler txt, le tds os txt
        printMensagem("Lendo arquivos .txt","#");
        clienteLerTXT(&listaCliente);
        equipeLerTXT(&listaEquipe);
        fornecedorLerTXT(&listaFornecedor);
        operadorLerTXT(&listaOperador);
        recursoLerTXT(&listaRecurso);

    } else if (produtoraLerBIN(&listaProdutora)){
        // se conseguiu ler binario, le tds os binarios
        printMensagem("Lendo arquivos .bin","#");
        clienteLerBIN(&listaCliente);
        equipeLerBIN(&listaEquipe);
        fornecedorLerBIN(&listaFornecedor);
        operadorLerBIN(&listaOperador);
        recursoLerBIN(&listaRecurso);

    } else{
        // se n deu pra ler nenhum, recebe os dados iniciais da produtora
        
    }

    //===========================================
    // Roda o menu principal
    menuPrincipal(&listaCliente, &listaFornecedor, &listaProdutora, &listaEquipe, &listaRecurso, &listaOperador);

    //===========================================
    // Salva os dados na memoria

    // Decide se vai salvar em TXT ou BIN
    if (recebeMetodoDeSalvamento() == 1) {
        // Salvar em txt
        printMensagem("Salvando arquivos .txt","#");
        clienteSalvarTXT(listaCliente);
        equipeSalvarTXT(listaEquipe);
        fornecedorSalvarTXT(listaFornecedor);
        operadorSalvarTXT(listaOperador);
        produtoraSalvarTXT(listaProdutora);
        recursoSalvarTXT(listaRecurso);

        // Apaga os arquivos bin
        remove("dados/cliente.bin");
        remove("dados/equipe.bin");
        remove("dados/fornecedor.bin");
        remove("dados/operador.bin");
        remove("dados/produtora.bin");
        remove("dados/recurso.bin");
    } else {
        // salvar em bin
        printMensagem("Salvando arquivos .bin","#");
        clienteSalvarBIN(listaCliente);
        equipeSalvarBIN(listaEquipe);
        fornecedorSalvarBIN(listaFornecedor);
        operadorSalvarBIN(listaOperador);
        produtoraSalvarBIN(listaProdutora);
        recursoSalvarBIN(listaRecurso);
        
        // Apaga os arquivos txt
        remove("dados/cliente.txt");
        remove("dados/equipe.txt");
        remove("dados/fornecedor.txt");
        remove("dados/operador.txt");
        remove("dados/produtora.txt");
        remove("dados/recurso.txt");
    }


    //===========================================
    // Liberar memoria de tds as listas
    printMensagem("Liberando Memoria","#");
    clienteListaLiberar(listaCliente);
    equipeListaLiberar(listaEquipe);
    fornecedorListaLiberar(listaFornecedor);
    operadorListaLiberar(listaOperador);
    produtoraListaLiberar(listaProdutora);
    recursoListaLiberar(listaRecurso);
}