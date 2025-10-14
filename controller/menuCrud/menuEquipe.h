#ifndef MENU_EQUIPE_INTERNA_H
#define MENU_EQUIPE_INTERNA_H

#include "../../model/equipe.h"

#include "../../utils/utils_tela.h"

#include "../../view/recebeDados.h"
#include "../../view/menuView.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoEquipe menuEquipeRecebe();
void menuEquipe(ListaEquipe **listaEquipe);
void menuEquipeAdicionar(ListaEquipe **listaEquipe);
void menuEquipeRemover(ListaEquipe **listaEquipe);
void menuEquipeAtualizar(ListaEquipe **listaEquipe);
void menuEquipeBuscar(ListaEquipe **listaEquipe);
void menuEquipeListar(ListaEquipe *lista);

#endif // MENU_EQUIPE_INTERNA_H