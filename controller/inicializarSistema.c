#include "inicializarSistema.h"

void inicializarListas(ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, ListaProdutora **listaProdutora, ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaOperador **listaOperador) {
    // Inicializa cada lista chamando a funcao correspondente
    clienteListaInit(*listaCliente);
    fornecedorListaInit(*listaFornecedor);
    produtoraListaInit(*listaProdutora);
    equipeListaInit(*listaEquipe);
    recursoListaInit(*listaRecurso);
    operadorListaInit(*listaOperador);
}


void inicializarSistema() {
    // Declara as listas e inicializa elas
    ListaCliente* listaCliente = (ListaCliente*)malloc(sizeof(ListaCliente));
    ListaFornecedor* listaFornecedor = (ListaFornecedor*)malloc(sizeof(ListaFornecedor));
    ListaProdutora* listaProdutora = (ListaProdutora*)malloc(sizeof(ListaProdutora));
    ListaEquipe* listaEquipe = (ListaEquipe*)malloc(sizeof(ListaEquipe));
    ListaRecurso* listaRecurso = (ListaRecurso*)malloc(sizeof(ListaRecurso));
    ListaOperador* listaOperador = (ListaOperador*)malloc(sizeof(ListaOperador));
    inicializarListas(&listaCliente, &listaFornecedor, &listaProdutora, &listaEquipe, &listaRecurso, &listaOperador);

    // Le da memoria
    clienteLerTXT(&listaCliente);
    equipeLerTXT(&listaEquipe);
    //fornecedorLerTXT(&listaFornecedor);
    //operadorLerTXT(&listaOperador);
    //produtoraLerTXT(&listaProdutora);
    //recursoLerTXT(&listaRecurso);

    // Roda o menu principal
    menuPrincipal(&listaCliente, &listaFornecedor, &listaProdutora, &listaEquipe, &listaRecurso, &listaOperador);

    // Salva na memoria
    clienteSalvarTXT(&listaCliente);
    equipeSalvarTXT(&listaEquipe);
    //fornecedorSalvarTXT(&listaFornecedor);
    //operadorSalvarTXT(&listaOperador);
    //produtoraSalvarTXT(&listaProdutora);
    //recursoSalvarTXT(&listaRecurso);

    // Liberar memoria de tds as listas
    clienteListaLiberar(listaCliente);
    equipeListaLiberar(listaEquipe);
    fornecedorListaLiberar(listaFornecedor);
    operadorListaLiberar(listaOperador);
    produtoraListaLiberar(listaProdutora);
    recursoListaLiberar(listaRecurso);
}