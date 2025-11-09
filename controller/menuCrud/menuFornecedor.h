#ifndef MENU_FORNECEDOR_PARCEIRO_H
#define MENU_FORNECEDOR_PARCEIRO_H

#include "../../model/fornecedor.h"

#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"

#include "../../view/printMenu.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoFornecedor menuFornecedorRecebe(TipoConfig *config);
void menuFornecedor(ListaFornecedor **listaFornecedor, TipoConfig *config);
void menuFornecedorAdicionar(ListaFornecedor **listaFornecedor, TipoConfig *config);
void menuFornecedorRemover(ListaFornecedor **listaFornecedor, TipoConfig *config);
void menuFornecedorAtualizar(ListaFornecedor **listaFornecedor, TipoConfig *config);
void menuFornecedorBuscar(ListaFornecedor **listaFornecedor, TipoConfig *config);
void menuFornecedorListar(ListaFornecedor *lista, TipoConfig *config);

#endif // MENU_FORNECEDOR_PARCEIRO_H