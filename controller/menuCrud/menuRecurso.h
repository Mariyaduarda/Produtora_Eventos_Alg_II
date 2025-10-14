#ifndef MENU_RECURSO_H
#define MENU_RECURSO_H

#include "../../model/recurso.h"

#include "../../utils/utils_tela.h"

#include "../../view/recebeDados.h"
#include "../../view/menuView.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

TipoRecurso menuRecursoRecebe();
void menuRecurso(ListaRecurso **listaRecurso);
void menuRecursoAdicionar(ListaRecurso **listaRecurso);
void menuRecursoRemover(ListaRecurso **listaRecurso);
void menuRecursoAtualizar(ListaRecurso **listaRecurso);
void menuRecursoBuscar(ListaRecurso **listaRecurso);
void menuRecursoListar(ListaRecurso *lista);

#endif // MENU_RECURSO_H