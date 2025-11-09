#ifndef MENU_PRODUTORA_H
#define MENU_PRODUTORA_H

#include "../../model/produtora.h"

#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"

#include "../../view/printMenu.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoProdutora menuProdutoraRecebe(TipoConfig *config);
void menuProdutoraAtualizar(TipoProdutora* produtora, TipoConfig *config);
void menuProdutora(TipoProdutora* produtora, TipoConfig *config);

#endif // MENU_PRODUTORA_H