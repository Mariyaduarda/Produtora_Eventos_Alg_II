#include "inicializarSistema.h"

void inicializarListas(ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, ListaProdutora **listaProdutora, ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaOperador **listaOperador) {
    // Inicializa cada lista chamando a funcao correspondente
    inicializarListaCliente(*listaCliente);
    inicializarListaFornecedor(*listaFornecedor);
    inicializarListaProdutora(*listaProdutora);
    inicializarListaEquipe(*listaEquipe);
    inicializarListaRecurso(*listaRecurso);
    inicializarListaOperador(*listaOperador);
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

    // Roda o menu principal
    menuPrincipal(&listaCliente, &listaFornecedor, &listaProdutora, &listaEquipe, &listaRecurso, &listaOperador);

    // Liberar memoria de tds as listas
    liberarListaCliente(listaCliente);
    liberarListaEquipe(listaEquipe);
    liberarListaFornecedor(listaFornecedor);
    liberarListaOperador(listaOperador);
    liberarListaProdutora(listaProdutora);
    liberarListaRecurso(listaRecurso);
}