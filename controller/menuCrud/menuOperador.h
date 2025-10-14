#ifndef MENU_OPERADOR_H
#define MENU_OPERADOR_H

#include "../../model/operador.h"

#include "../../utils/utils_tela.h"

#include "../../view/recebeDados.h"
#include "../../view/menuView.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoOperador menuOperadorRecebe();
void menuOperador(ListaOperador **listaOperador);
void menuOperadorAdicionar(ListaOperador **listaOperador);
void menuOperadorRemover(ListaOperador **listaOperador);
void menuOperadorAtualizar(ListaOperador **listaOperador);
void menuOperadorBuscar(ListaOperador **listaOperador);
void menuOperadorListar(ListaOperador *lista);

#endif // MENU_OPERADOR_H