#ifndef MENU_CLIENTE_H
#define MENU_CLIENTE_H

#include "../../model/cliente.h"

#include "../../utils/utils_tela.h"

#include "../../view/recebeDados.h"
#include "../../view/menuView.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

void menuCliente(ListaCliente **listaCliente);
void menuClienteAdicionar(ListaCliente **listaCliente);
void menuClienteRemover(ListaCliente **listaCliente);
void menuClienteAtualizar(ListaCliente **listaCliente);
void menuClienteBuscar(ListaCliente **listaCliente);


#endif // MENU_CLIENTE_H