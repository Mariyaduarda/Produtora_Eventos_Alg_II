#ifndef MENU_EVENTO_H
#define MENU_EVENTO_H

#include "menuCliente.h"
#include "menuRecurso.h"
#include "menuEquipe.h"
#include "menuFornecedor.h"

#include "../../model/evento.h"
#include "../../model/cliente.h"
#include "../../model/recurso.h"
#include "../../model/equipe.h"
#include "../../model/fornecedor.h"
#include "../../model/transacao.h"

#include "../../utils/utils_tela.h"
#include "../../utils/recebeDados.h"
#include "../../utils/utils_validacoes.h"
#include "../../utils/utils_data.h"

#include "../../view/printMenu.h"
#include "../../view/mostrarItem.h"
#include "../../view/mensagens.h"

// Funcoes principais do menu
#include "menuEvento.h"

// ========== FUNCAO PARA RECEBER DADOS DO EVENTO ==========
TipoEvento menuEventoRecebe(TipoConfig *config, ListaCliente *listaCliente);

// ========== MENU PRINCIPAL DE EVENTOS ==========
void menuEvento(TipoEvento* evento,ListaEvento **listaEvento, ListaCliente *listaCliente,
                ListaRecurso *listaRecurso, ListaEquipe *listaEquipe, 
                ListaFornecedor *listaFornecedor, TipoConfig *config);

// CRUD DE EVENTOS
void menuEventoAdicionar(ListaEvento **listaEvento, ListaCliente *listaCliente, TipoConfig *config);

void menuEventoRemover(ListaEvento **listaEvento, TipoConfig *config);

void menuEventoAtualizar(ListaEvento **listaEvento, ListaCliente *listaCliente, TipoConfig *config);

void menuEventoBuscar(ListaEvento **listaEvento, TipoConfig *config);

void menuEventoListar(ListaEvento *listaEvento, TipoConfig *config);

//===============================================
// MENU DE GERENCIAR EVENTO COMPLETO
void menuEventoGerenciar(ListaEvento *listaEvento, ListaRecurso *listaRecurso, 
                         ListaEquipe *listaEquipe, ListaFornecedor *listaFornecedor, 
                         TipoConfig *config);

// ========== RECURSOS DO EVENTO ==========
void menuEventoRecurso(ListaEvento *listaEvento, TipoEvento *evento, ListaRecurso *listaRecurso, TipoConfig *config);

void menuEventoRecursoAdicionar(ListaEvento *listaEvento, TipoEvento *evento, ListaRecurso *listaRecurso, TipoConfig *config);

void menuEventoRecursoRemover(ListaRecurso *listaRecurso, TipoEvento *evento, TipoConfig *config);

void menuEventoRecursoListar(ListaRecurso *listaRecurso, TipoEvento *evento, TipoConfig *config);

// ========== EQUIPE DO EVENTO ==========
void menuEventoEquipe(ListaEvento *listaEvento, TipoEvento *evento, ListaEquipe *listaEquipe, TipoConfig *config);


void menuEventoEquipeAdicionar(ListaEvento *listaEvento, TipoEvento *evento, ListaEquipe *listaEquipe, TipoConfig *config);

void menuEventoEquipeRemover(ListaEquipe *listaEquipe, TipoEvento *evento, TipoConfig *config);

void menuEventoEquipeListar(ListaEquipe *listaEquipe, TipoEvento *evento, TipoConfig *config);


// ========== FORNECEDORES DO EVENTO ==========

void menuEventoFornecedor(ListaEvento *listaEvento, TipoEvento *evento, ListaFornecedor *listaFornecedor, TipoConfig *config);


void menuEventoFornecedorAdicionar(ListaEvento *listaEvento, TipoEvento *evento, ListaFornecedor *listaFornecedor, TipoConfig *config);

void menuEventoFornecedorRemover(ListaFornecedor *listaFornecedor, TipoEvento *evento, TipoConfig *config);

void menuEventoFornecedorListar(ListaFornecedor *listaFornecedor, TipoEvento *evento, TipoConfig *config);



// ========== EDITAR DADOS BASICOS ==========
void menuEventoEditarDados(TipoEvento *evento, ListaCliente *listaCliente, TipoConfig *config);

// ========== MUDAR STATUS ==========
void menuEventoMudarStatus(ListaEvento *listaEvento, TipoConfig *config);

// ========== RELATORIO ==========
void menuEventoRelatorio(TipoEvento *evento, TipoConfig *config);


#endif // MENU_EVENTO_H