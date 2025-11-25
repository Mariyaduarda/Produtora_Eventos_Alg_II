#ifndef MOSTRAR_ITEM_H
#define MOSTRAR_ITEM_H

#include <stdio.h>
#include <stdlib.h>

#include "../model/config.h"
#include "../model/cliente.h"
#include "../model/equipe.h"
#include "../model/fornecedor.h"
#include "../model/operador.h"
#include "../model/produtora.h"
#include "../model/recurso.h"
#include "../model/evento.h"

#include "../utils/utils_tela.h"

void printItemCliente(TipoCliente cliente);
void printItemEquipe(TipoEquipe equipe);
void printItemFornecedor(TipoFornecedor fornecedor);
void printItemOperador(TipoOperador operador);
void printItemProdutora(TipoProdutora produtora);
void printItemRecurso(TipoRecurso recurso);
void printItemEvento(TipoEvento evento);

#endif // MOSTRAR_ITEM_H
