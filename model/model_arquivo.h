#ifndef MODEL_ARQUIVO_H
#define MODEL_ARQUIVO_H

#include <stdio.h>

// pra ter as estruturas
#include "../model/config.h"
#include "../model/cliente.h"
#include "../model/fornecedor.h"
#include "../model/produtora.h"
#include "../model/equipe.h"
#include "../model/recurso.h"
#include "../model/operador.h"

// pra usar as funcoes de print
#include "../view/mensagens.h"

int lerMemoria(TipoConfig *config, TipoProdutora *produtora, ListaCliente **listaCliente, 
    ListaFornecedor **listaFornecedor, ListaEquipe **listaEquipe, 
    ListaRecurso **listaRecurso, ListaOperador **listaOperador);

int salvarMemoria(TipoConfig *config, TipoProdutora *produtora, ListaCliente *listaCliente, 
    ListaFornecedor *listaFornecedor, ListaEquipe *listaEquipe,
    ListaRecurso *listaRecurso, ListaOperador *listaOperador);

#endif // MODEL_ARQUIVO_H