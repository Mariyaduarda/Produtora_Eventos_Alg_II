#ifndef MENU_FORNECEDOR_PARCEIRO_H
#define MENU_FORNECEDOR_PARCEIRO_H

#include "../../model/fornecedor.h"

#include "../../utils/utils_tela.h"

#include "../../view/recebeDados.h"
#include "../../view/menuView.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoFornecedor menuFornecedorRecebe();
void menuFornecedor(ListaFornecedor **listaFornecedor);
void menuFornecedorAdicionar(ListaFornecedor **listaFornecedor);
void menuFornecedorRemover(ListaFornecedor **listaFornecedor);
void menuFornecedorAtualizar(ListaFornecedor **listaFornecedor);
void menuFornecedorBuscar(ListaFornecedor **listaFornecedor);
void menuFornecedorListar(ListaFornecedor *lista);

#endif // MENU_FORNECEDOR_PARCEIRO_H