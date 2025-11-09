#ifndef INICIALIZAR_SISTEMA_H
#define INICIALIZAR_SISTEMA_H

#include <stdio.h>
#include "../model/config.h"

#include "../model/cliente.h"
#include "../model/fornecedor.h"
#include "../model/produtora.h"
#include "../model/equipe.h"
#include "../model/recurso.h"
#include "../model/operador.h"
#include "menuController.h"

#include "menuCrud/menuProdutora.h" // para receber os dados da produtora, caso n tenha nenhum

void inicializarSistema();

int lerMemoria(TipoConfig *config, TipoProdutora *produtora, ListaCliente **listaCliente, 
    ListaFornecedor **listaFornecedor, ListaEquipe **listaEquipe, 
    ListaRecurso **listaRecurso, ListaOperador **listaOperador);

int salvarMemoria(TipoConfig *config, TipoProdutora *produtora, ListaCliente *listaCliente, 
    ListaFornecedor *listaFornecedor, ListaEquipe *listaEquipe,
    ListaRecurso *listaRecurso, ListaOperador *listaOperador);

#endif // INICIALIZAR_SISTEMA_H