#ifndef MENU_RECURSO_H
#define MENU_RECURSO_H

#include "../../model/recurso.h"

#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"

#include "../../view/printMenu.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoRecurso menuRecursoRecebe(TipoConfig *config);
void menuRecurso(ListaRecurso **listaRecurso, TipoConfig *config);
void menuRecursoAdicionar(ListaRecurso **listaRecurso, TipoConfig *config);
void menuRecursoRemover(ListaRecurso **listaRecurso, TipoConfig *config);
void menuRecursoAtualizar(ListaRecurso **listaRecurso, TipoConfig *config);
void menuRecursoBuscar(ListaRecurso **listaRecurso, TipoConfig *config);
void menuRecursoListar(ListaRecurso *lista, TipoConfig *config);

#endif // MENU_RECURSO_H