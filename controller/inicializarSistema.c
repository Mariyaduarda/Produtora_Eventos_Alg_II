#include "inicializarSistema.h"

void inicializarListas(ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, ListaProdutora **listaProdutoras, ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaOperador **listaOperador) {
    // Inicializa cada lista chamando a funcao correspondente
    inicializarListaCliente(*listaCliente);
    inicializarListaFornecedor(*listaFornecedor);
    inicializarListaProdutora(*listaProdutoras);
    inicializarListaEquipe(*listaEquipe);
    inicializarListaRecurso(*listaRecurso);
    inicializarListaOperador(*listaOperador);
}


void inicializarSistema() {
    // Declara as listas e inicializa elas
    ListaCliente* listaCliente = (ListaCliente*)malloc(sizeof(ListaCliente));
    ListaFornecedor* listaFornecedor = (ListaFornecedor*)malloc(sizeof(ListaFornecedor));
    ListaProdutora* listaProdutoras = (ListaProdutora*)malloc(sizeof(ListaProdutora));
    ListaEquipe* listaEquipe = (ListaEquipe*)malloc(sizeof(ListaEquipe));
    ListaRecurso* listaRecurso = (ListaRecurso*)malloc(sizeof(ListaRecurso));
    ListaOperador* listaOperador = (ListaOperador*)malloc(sizeof(ListaOperador));
    inicializarListas(&listaCliente, &listaFornecedor, &listaProdutoras, &listaEquipe, &listaRecurso, &listaOperador);

    // roda o menu principal
    menuPrincipal(&listaCliente, &listaFornecedor, &listaProdutoras, &listaEquipe, &listaRecurso, &listaOperador);
}