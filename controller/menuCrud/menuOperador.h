#ifndef MENU_OPERADOR_H
#define MENU_OPERADOR_H

#include "../../model/operador.h"

#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"

#include "../../view/printMenu.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoOperador menuOperadorRecebe(TipoConfig *config);
void menuOperador(ListaOperador **listaOperador, TipoConfig *config);
void menuOperadorAdicionar(ListaOperador **listaOperador, TipoConfig *config);
void menuOperadorRemover(ListaOperador **listaOperador, TipoConfig *config);
void menuOperadorAtualizar(ListaOperador **listaOperador, TipoConfig *config);
void menuOperadorBuscar(ListaOperador **listaOperador, TipoConfig *config);
void menuOperadorListar(ListaOperador *lista, TipoConfig *config);

#endif // MENU_OPERADOR_H