#ifndef INICIALIZAR_SISTEMA_H
#define INICIALIZAR_SISTEMA_H

#include <stdio.h>
#include "../model/cliente.h"
#include "../model/fornecedorParceiro.h"
#include "../model/produtora.h"
#include "../model/equipeInterna.h"
#include "../model/recursoEquipamento.h"
#include "../model/operadorSistema.h"
#include "menuController.h"

void inicializarListas(ListaCliente **listaCliente, ListaFornecedorParceiro **listaFornecedoresParceiros, ListaProdutora **listaProdutoras, ListaEquipeInterna **listaEquipeInterna, ListaRecursoEquipamento **listaRecursosEquipamentos, ListaOperadorSistema **listaOperadoresSistema);
void inicializarSistema();

#endif // INICIALIZAR_SISTEMA_H