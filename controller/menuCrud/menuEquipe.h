#ifndef MENU_EQUIPE_INTERNA_H
#define MENU_EQUIPE_INTERNA_H

#include "../../model/equipe.h"

#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"

#include "../../view/printMenu.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoEquipe menuEquipeRecebe(TipoConfig *config);
void menuEquipe(ListaEquipe **listaEquipe, TipoConfig *config);
void menuEquipeAdicionar(ListaEquipe **listaEquipe, TipoConfig *config);
void menuEquipeRemover(ListaEquipe **listaEquipe, TipoConfig *config);
void menuEquipeAtualizar(ListaEquipe **listaEquipe, TipoConfig *config);
void menuEquipeBuscar(ListaEquipe **listaEquipe, TipoConfig *config);
void menuEquipeListar(ListaEquipe *lista, TipoConfig *config);

#endif // MENU_EQUIPE_INTERNA_H