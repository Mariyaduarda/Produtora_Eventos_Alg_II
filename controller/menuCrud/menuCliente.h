#ifndef MENU_CLIENTE_H
#define MENU_CLIENTE_H

#include "../../model/cliente.h"

#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"

#include "../../view/printMenu.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoCliente menuClienteRecebe(TipoConfig *config);
void menuCliente(ListaCliente **listaCliente, TipoConfig *config);
void menuClienteAdicionar(ListaCliente **listaCliente, TipoConfig *config);
void menuClienteRemover(ListaCliente **listaCliente, TipoConfig *config);
void menuClienteAtualizar(ListaCliente **listaCliente, TipoConfig *config);
void menuClienteBuscar(ListaCliente **listaCliente, TipoConfig *config);
void menuClienteListar(ListaCliente *lista, TipoConfig *config);

#endif // MENU_CLIENTE_H