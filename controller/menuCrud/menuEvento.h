#ifndef MENU_EVENTO_H
#define MENU_EVENTO_H

#include "../../model/evento.h"
#include "../../model/cliente.h"
#include "../../model/recurso.h"
#include "../../model/equipe.h"
#include "../../model/fornecedor.h"
#include "../../model/transacao.h"

#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"

#include "../../view/printMenu.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

// Funcoes principais do menu
TipoEvento menuEventoRecebe(TipoConfig *config, ListaCliente *listaCliente);
void menuEvento(TipoEvento* evento,ListaEvento **listaEvento, ListaCliente *listaCliente,
                ListaRecurso *listaRecurso, ListaEquipe *listaEquipe, 
                ListaFornecedor *listaFornecedor, TipoConfig *config);

// CRUD basico
void menuEventoAdicionar(ListaEvento **listaEvento, ListaCliente *listaCliente, TipoConfig *config);
void menuEventoRemover(ListaEvento **listaEvento, TipoConfig *config);
void menuEventoAtualizar(ListaEvento **listaEvento, ListaCliente *listaCliente, TipoConfig *config);
void menuEventoBuscar(ListaEvento **listaEvento, TipoConfig *config);
void menuEventoListar(ListaEvento *listaEvento, TipoConfig *config);

// Gestao de recursos, equipe e fornecedores do evento
void menuEventoGerenciar(ListaEvento *listaEvento, ListaRecurso *listaRecurso, 
                         ListaEquipe *listaEquipe, ListaFornecedor *listaFornecedor, 
                         TipoConfig *config);

void menuEventoAdicionarRecurso(TipoEvento *evento, ListaRecurso *listaRecurso, TipoConfig *config);
void menuEventoRemoverRecurso(TipoEvento *evento, TipoConfig *config);
void menuEventoListarRecursos(TipoEvento *evento, TipoConfig *config);

void menuEventoAdicionarEquipe(TipoEvento *evento, ListaEquipe *listaEquipe, TipoConfig *config);
void menuEventoRemoverEquipe(TipoEvento *evento, TipoConfig *config);
void menuEventoListarEquipes(TipoEvento *evento, TipoConfig *config);

void menuEventoAdicionarFornecedor(TipoEvento *evento, ListaFornecedor *listaFornecedor, TipoConfig *config);
void menuEventoRemoverFornecedor(TipoEvento *evento, TipoConfig *config);
void menuEventoListarFornecedores(TipoEvento *evento, TipoConfig *config);

// Edicao de dados e datas
void menuEventoEditarDados(TipoEvento *evento, ListaCliente *listaCliente, TipoConfig *config);
void menuEventoEditarDatas(TipoEvento *evento, TipoConfig *config);
void menuEventoGerenciarCompleto(ListaEvento **listaEvento, ListaRecurso *listaRecurso,
                                  ListaEquipe *listaEquipe, ListaFornecedor *listaFornecedor,
                                  TipoConfig *config);

// Mudanca de status
void menuEventoMudarStatus(ListaEvento *listaEvento, TipoConfig *config);

// Relatorios
void menuEventoRelatorio(TipoEvento *evento, TipoConfig *config);

#endif // MENU_EVENTO_H