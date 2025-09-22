#ifndef MENU_CLIENTE_H
#define MENU_CLIENTE_H

#include "../../model/cliente.h"

#include "../../utils/utils_tela.h"

#include "../../view/recebeDados.h"
#include "../../view/menuView.h"
#include "../../view/mostrarItem.h"

void menuCliente(ListaCliente **listaCliente);
void listarClientes(ListaCliente *lista);


#endif // MENU_CLIENTE_H