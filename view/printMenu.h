#ifndef PRINT_MENU_H
#define PRINT_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "../utils/utils_tela.h"

#include "../view/mostrarItem.h" // pra mostrar os dados da produtora no seu menu

// Tem tds as funcoes de exibicao de menus

void printMenuPrincipal();
void printMenuCRUD();

void printMenuProdutora(TipoProdutora produtora);
void printMenuConfig(TipoConfig config);

void printMenuCliente();
void printMenuFornecedor();
void printMenuEquipe();
void printMenuRecurso();
void printMenuOperador();

#endif // PRINT_MENU_H