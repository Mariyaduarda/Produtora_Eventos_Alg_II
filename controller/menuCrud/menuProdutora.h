#ifndef MENU_PRODUTORA_H
#define MENU_PRODUTORA_H

#include "../../model/produtora.h"

#include "../../utils/utils_tela.h"

#include "../../view/recebeDados.h"
#include "../../view/menuView.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoProdutora menuProdutoraRecebe();
void menuProdutora(ListaProdutora **listaProdutora);
void menuProdutoraAdicionar(ListaProdutora **listaProdutora);
void menuProdutoraRemover(ListaProdutora **listaProdutora);
void menuProdutoraAtualizar(ListaProdutora **listaProdutora);
void menuProdutoraBuscar(ListaProdutora **listaProdutora);
void menuProdutoraListar(ListaProdutora *lista);

#endif // MENU_PRODUTORA_H