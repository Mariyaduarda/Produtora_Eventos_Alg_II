#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include "../view/menuView.h"
#include "../utils/utils_tela.c"
#include "../view/mensagens.c"
#include "../model/cliente.h"
#include "../model/fornecedorParceiro.h"
#include "../model/produtora.h"
#include "../model/equipeInterna.h"
#include "../model/recursoEquipamento.h"
#include "../model/operadorSistema.h"

// Inclui todos os menus CRUD
#include "menuCrud/menuCrud.h"
#include "menuCrud/menuCliente.h"
#include "menuCrud/menuFornecedorParceiro.h"
#include "menuCrud/menuProdutora.h"
#include "menuCrud/menuEquipeInterna.h"
#include "menuCrud/menuRecursoEquipamento.h"
#include "menuCrud/menuOperadorSistema.h"

void menuPrincipal();

#endif // MENU_CONTROLLER_H