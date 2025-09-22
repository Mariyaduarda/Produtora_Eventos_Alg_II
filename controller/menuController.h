#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>

#include "../view/menuView.h"
#include "../view/mensagens.h"

#include "../utils/utils_tela.h"

#include "../model/cliente.h"
#include "../model/fornecedor.h"
#include "../model/produtora.h"
#include "../model/equipe.h"
#include "../model/recurso.h"
#include "../model/operador.h"

// Inclui todos os menus CRUD
#include "menuCrud/menuCliente.h"
#include "menuCrud/menuFornecedor.h"
#include "menuCrud/menuProdutora.h"
#include "menuCrud/menuEquipe.h"
#include "menuCrud/menuRecurso.h"
#include "menuCrud/menuOperador.h"

void menuPrincipal();

#endif // MENU_CONTROLLER_H