#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>

#include "../view/menuView.h"
#include "../view/mensagens.h"

#include "../utils/utils_tela.h"

#include "../model/produtora.h"
#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/fornecedor.h"
#include "../model/operador.h"
#include "../model/recurso.h"

// Inclui todos os menus CRUD
#include "menuCrud/menuProdutora.h"
#include "menuCrud/menuCliente.h"
#include "menuCrud/menuEquipe.h"
#include "menuCrud/menuFornecedor.h"
#include "menuCrud/menuOperador.h"
#include "menuCrud/menuRecurso.h"

void menuPrincipal(TipoProdutora *produtora, ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaOperador **listaOperador);

#endif // MENU_CONTROLLER_H