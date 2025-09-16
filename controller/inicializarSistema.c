#include <stdio.h>
#include "../model/entities/cliente.h"
#include "../model/entities/fornecedorParceiro.h"
#include "../model/entities/produtora.h"
#include "../model/entities/equipeInterna.h"
#include "../model/entities/recursoEquipamento.h"
#include "../model/entities/operadorSistema.h"
#include "menuController.h"

void inicializarSistema() {
    // Declara as listas e inicializa elas
    ListaCliente* listaCliente = NULL;
    ListaFornecedorParceiro* listaFornecedoresParceiros = NULL;
    ListaProdutora* listaProdutoras = NULL;
    ListaEquipeInterna* listaEquipeInterna = NULL;
    ListaRecursoEquipamento* listaRecursosEquipamentos = NULL;
    ListaOperadorSistema* listaOperadoresSistema = NULL;
    inicializarListas(&listaCliente, &listaFornecedoresParceiros, &listaProdutoras, &listaEquipeInterna, &listaRecursosEquipamentos, &listaOperadoresSistema);

    //roda o menu principal
    menuPrincipal(&listaCliente, &listaFornecedoresParceiros, &listaProdutoras, &listaEquipeInterna, &listaRecursosEquipamentos, &listaOperadoresSistema);
    
}

void inicializarListas(ListaCliente **listaCliente, ListaFornecedorParceiro **listaFornecedoresParceiros, ListaProdutora **listaProdutoras, ListaEquipeInterna **listaEquipeInterna, ListaRecursoEquipamento **listaRecursosEquipamentos, ListaOperadorSistema **listaOperadoresSistema) {
    // Inicializa cada lista chamando a funcao correspondente
    inicializarListaCliente(*listaCliente);
    inicializarListaFornecedoresParceiros(*listaFornecedoresParceiros);
    inicializarListaProdutora(*listaProdutoras);
    inicializarListaEquipeInterna(*listaEquipeInterna);
    inicializarListaRecursosEquipamentos(*listaRecursosEquipamentos);
    inicializarListaOperadoresSistema(*listaOperadoresSistema);
}