#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>

#include "../view/printMenu.h"
#include "../view/mensagens.h"

#include "../utils/utils_tela.h"

#include "../model/config.h"

#include "../model/produtora.h"
#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/fornecedor.h"
#include "../model/operador.h"
#include "../model/recurso.h"

// Inclui todos os menus CRUD
#include "menuCRUD/menuConfig.h"
#include "menuCRUD/menuProdutora.h"
#include "menuCRUD/menuCliente.h"
#include "menuCRUD/menuEquipe.h"
#include "menuCRUD/menuFornecedor.h"
#include "menuCRUD/menuOperador.h"
#include "menuCRUD/menuRecurso.h"

void menuPrincipal(TipoConfig *config, TipoProdutora *produtora, ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaOperador **listaOperador);
void menuCRUD(TipoConfig *config, TipoProdutora *produtora, ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaOperador **listaOperador);

#endif // MENU_CONTROLLER_H