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
#include "../model/model_arquivo.h"

#include "menuController.h"

#include "menuCRUD/menuProdutora.h" // para receber os dados da produtora, caso n tenha nenhum

void inicializarSistema();

#endif // INICIALIZAR_SISTEMA_H