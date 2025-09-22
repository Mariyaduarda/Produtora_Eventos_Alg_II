#ifndef INICIALIZAR_SISTEMA_H
#define INICIALIZAR_SISTEMA_H

#include <stdio.h>
#include "../model/cliente.h"
#include "../model/fornecedor.h"
#include "../model/produtora.h"
#include "../model/equipe.h"
#include "../model/recurso.h"
#include "../model/operador.h"
#include "menuController.h"

void inicializarListas(ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, ListaProdutora **listaProdutoras, ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaOperador **listaOperador);
void inicializarSistema();

#endif // INICIALIZAR_SISTEMA_H