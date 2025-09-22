#include "inicializarSistema.h"

void inicializarListas(ListaCliente **listaCliente, ListaFornecedorParceiro **listaFornecedoresParceiros, ListaProdutora **listaProdutoras, ListaEquipeInterna **listaEquipeInterna, ListaRecursoEquipamento **listaRecursosEquipamentos, ListaOperadorSistema **listaOperadoresSistema) {
    // Inicializa cada lista chamando a funcao correspondente
    inicializarListaCliente(*listaCliente);
    inicializarListaFornecedoresParceiros(*listaFornecedoresParceiros);
    inicializarListaProdutora(*listaProdutoras);
    inicializarListaEquipeInterna(*listaEquipeInterna);
    inicializarListaRecursosEquipamentos(*listaRecursosEquipamentos);
    inicializarListaOperadoresSistema(*listaOperadoresSistema);
}


void inicializarSistema() {
    // Declara as listas e inicializa elas
    ListaCliente* listaCliente = (ListaCliente*)malloc(sizeof(ListaCliente));
    ListaFornecedorParceiro* listaFornecedoresParceiros = (ListaFornecedorParceiro*)malloc(sizeof(ListaFornecedorParceiro));
    ListaProdutora* listaProdutoras = (ListaProdutora*)malloc(sizeof(ListaProdutora));
    ListaEquipeInterna* listaEquipeInterna = (ListaEquipeInterna*)malloc(sizeof(ListaEquipeInterna));
    ListaRecursoEquipamento* listaRecursosEquipamentos = (ListaRecursoEquipamento*)malloc(sizeof(ListaRecursoEquipamento));
    ListaOperadorSistema* listaOperadoresSistema = (ListaOperadorSistema*)malloc(sizeof(ListaOperadorSistema));
    inicializarListas(&listaCliente, &listaFornecedoresParceiros, &listaProdutoras, &listaEquipeInterna, &listaRecursosEquipamentos, &listaOperadoresSistema);

    //roda o menu principal
    menuPrincipal(&listaCliente, &listaFornecedoresParceiros, &listaProdutoras, &listaEquipeInterna, &listaRecursosEquipamentos, &listaOperadoresSistema);
    
}