#include "menuEvento.h"

// ========== FUNÇÃO PARA RECEBER DADOS DO EVENTO ==========
TipoEvento menuEventoRecebe(TipoConfig *config, ListaCliente *listaCliente) {
    // Recebe um novo Evento do usuario e retorna o evento preenchido
    TipoEvento evento;
    eventoInit(&evento);

    // Recebe os dados do evento
    evento.id = 0; // ID sera atribuido automaticamente
    recebeString(evento.nome, 100, "Digite o Nome do Evento", "Max. 100", config->validar_dados);
    evento.codigoCliente = recebeInt(1, 1000000, "Digite o Codigo do Cliente", "#", config->validar_dados);
    recebeString(evento.localEvento, 150, "Digite o Local do Evento", "Max. 150", config->validar_dados);
    recebeString(evento.cidade, 50, "Digite a Cidade", "Max. 50", config->validar_dados);
    recebeString(evento.uf, 4, "Digite a UF", "Max. 4", config->validar_dados);
    evento.margemLucro = recebeFloat(0.0, 100.0, "Digite a Margem de Lucro (%)", "0.0 - 100.0", config->validar_dados);
    recebeString(evento.obs, 500, "Digite observacoes", "Max. 500", config->validar_dados);
    evento.status = STATUS_ORCAMENTO;

    // deixa as datas zeradas, implementar depois
    memset(&evento.dataInicio, 0, sizeof(struct tm));
    memset(&evento.dataFim, 0, sizeof(struct tm));

    return evento;
}

// ========== MENU PRINCIPAL DE EVENTOS ==========
void menuEvento(TipoEvento* evento,ListaEvento **listaEvento, ListaCliente *listaCliente,
                ListaRecurso *listaRecurso, ListaEquipe *listaEquipe, 
                ListaFornecedor *listaFornecedor, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        limparTela();
        printf(
            "\n======================================================================"
            "\n | # Gerenciamento de Eventos                                       | "
            "\n |==================================================================| "
            "\n |   1. Adicionar                                                   | "
            "\n |   2. Remover                                                     | "
            "\n |   3. Buscar/Editar                                               | "
            "\n |   4. Listar                                                      | "
            "\n |==================================================================| "
            "\n |   0. Voltar                                                      | "
            "\n======================================================================"
        );

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 4, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Adicionar Evento
                menuEventoAdicionar(listaEvento, listaCliente, config);
                esperaEnter();
                break;
            case 2:
                // Remover Evento
                menuEventoRemover(listaEvento, config);
                esperaEnter();
                break;
            case 3:
                // Buscar e editar evento
                menuEventoGerenciarCompleto(listaEvento, listaRecurso, listaEquipe, listaFornecedor, config);
                esperaEnter();
                break;
            case 4:
                // Listar Eventos
                menuEventoListar(*listaEvento, config);
                esperaEnter();
                break;
            case 0:
                // Voltar ao menu principal
                break;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }while (escolha != 0);
}

// CRUD DE EVENTOS
void menuEventoAdicionar(ListaEvento **listaEvento, ListaCliente *listaCliente, TipoConfig *config) {
    // Guarda o novo item
    TipoEvento novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuEventoRecebe(config, listaCliente); // Recebe os valores do usuario

        // Mostra os dados que foram inseridos
        printItemEvento(novo);

        if( recebeConfirma() ) break;  // Pergunta o usuario se ta td certo
    }

    // Realmente adiciona na lista
    if ( eventoAdicionar(listaEvento, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuEventoRemover(ListaEvento **listaEvento, TipoConfig *config) {
    int ID = recebeID(config->validar_dados); // recebe o ID do item que vai ser removido

    // Busca o Item q vai ser removido
    TipoEvento *evento; // Para guardar resultado de busca
    evento = eventoBuscar(*listaEvento, ID);
    if (evento == NULL){
        printNaoEncontrado();
        return;
    }

    // Mostra o Item que vai ser removido
    printItemEvento(*evento);

    // Pede confirmacao, se tiver ok, remove o evento
    if (recebeConfirma()){
        eventoRemover(listaEvento, ID);
        printRemoverSucesso();
    }
}

void menuEventoAtualizar(ListaEvento **listaEvento, ListaCliente *listaCliente, TipoConfig *config) {
    // Declara um novo item pra receber os dados atualizados
    TipoEvento novoEvento;
    TipoEvento* velhoEvento;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID(config->validar_dados);
    velhoEvento = eventoBuscar(*listaEvento, ID);

    // Se esse ID n existe, mostra erro
    if (velhoEvento == NULL){
        printNaoEncontrado();
        return;
    }

    // Caso contrario, recebe os novos dados
    novoEvento = menuEventoRecebe(config, listaCliente);

    // ===============================
    // Mostra as mudancas

    // Printa os antigos dados
    printMensagem("Dados Antigos","=");
    printItemEvento(*velhoEvento);

    // Printa os novos dados
    printMensagem("Dados Novos","=");
    printItemEvento(novoEvento);

    // ===============================
    // Confirma se o usuario realmente quer atualizar
    if (recebeConfirma()){
        eventoAtualizar(*listaEvento, novoEvento, ID);
        printAtualizarSucesso();
    }
}

void menuEventoBuscar(ListaEvento **listaEvento, TipoConfig *config) {
    TipoEvento *evento; // Para guardar resultado de busca
    evento = eventoBuscar(*listaEvento, recebeID(config->validar_dados));
    if (evento != NULL){
        printItemEvento(*evento);
    }
    else printNaoEncontrado();
}


void menuEventoListar(ListaEvento *listaEvento, TipoConfig *config) {
    limparTela();

    // Lista todos os eventos cadastrados
    if (listaEvento == NULL) {
        printMensagem("Nenhum item cadastrado","#");
        return;
    }

    ListaEvento *atual = listaEvento; // comeca auxiliar no comeco da lista
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->evento.ativo) printItemEvento(atual->evento);
        atual = atual->prox;
    }

    printf("\n");
}

// ========== GERENCIAR EVENTO ==========
void menuEventoGerenciar(ListaEvento *listaEvento, ListaRecurso *listaRecurso, 
                         ListaEquipe *listaEquipe, ListaFornecedor *listaFornecedor, 
                         TipoConfig *config) {
    int ID = recebeID(config->validar_dados); // Recebe o ID do evento
    TipoEvento *evento = eventoBuscar(listaEvento, ID);
    
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    // Menu para gerenciar recursos, equipes e fornecedores
    int escolha = 0;
    do {
        printMensagem("Gerenciar Evento", "=");
        printf("1. Adicionar Recurso\n");
        printf("2. Remover Recurso\n");
        printf("3. Listar Recursos\n");
        printf("4. Adicionar Equipe\n");
        printf("5. Remover Equipe\n");
        printf("6. Listar Equipes\n");
        printf("7. Adicionar Fornecedor\n");
        printf("8. Remover Fornecedor\n");
        printf("9. Listar Fornecedores\n");
        printf("0. Voltar\n");
        
        escolha = recebeInt(0, 9, "Digite uma opcao", "#", config->validar_dados);
        
        switch (escolha) {
            case 1:
                menuEventoAdicionarRecurso(evento, listaRecurso, config);
                esperaEnter();
                break;
            case 2:
                menuEventoRemoverRecurso(evento, config);
                esperaEnter();
                break;
            case 3:
                menuEventoListarRecursos(evento, config);
                esperaEnter();
                break;
            case 4:
                menuEventoAdicionarEquipe(evento, listaEquipe, config);
                esperaEnter();
                break;
            case 5:
                menuEventoRemoverEquipe(evento, config);
                esperaEnter();
                break;
            case 6:
                menuEventoListarEquipes(evento, config);
                esperaEnter();
                break;
            case 7:
                menuEventoAdicionarFornecedor(evento, listaFornecedor, config);
                esperaEnter();
                break;
            case 8:
                menuEventoRemoverFornecedor(evento, config);
                esperaEnter();
                break;
            case 9:
                menuEventoListarFornecedores(evento, config);
                esperaEnter();
                break;
        }
    } while (escolha != 0);
}

// ========== RECURSOS DO EVENTO ==========
void menuEventoAdicionarRecurso(TipoEvento *evento, ListaRecurso *listaRecurso, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    int codigo = recebeID(config->validar_dados);
    TipoRecurso *rec = recursoBuscar(listaRecurso, codigo);
    if (rec == NULL) {
        printNaoEncontrado();
        return;
    }

    int qtd = recebeInt(1, rec->qtdEstoque, "Quantidade a alocar (estoque disponivel)", "#", config->validar_dados);
    int dias = recebeInt(1, 365, "Numero de dias do evento", "#", config->validar_dados);

    if ( eventoUnirRecurso(evento, listaRecurso, codigo, qtd, dias) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuEventoRemoverRecurso(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    int codigo = recebeID(config->validar_dados);
    if ( eventoRemoverRecurso(evento, codigo) ) printRemoverSucesso();
    else printRemoverFalha();
}

void menuEventoListarRecursos(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Recursos do Evento", "=");
    ListaRecursoEvento *atual = evento->listaRecursos;
    if (atual == NULL) {
        printf("Nenhum recurso associado a este evento.\n");
    } else {
        printf("Codigo | Qtd | Dias | ValorUnit | Subtotal\n");
        while (atual != NULL) {
            printf("%6d | %3d | %4d | R$ %8.2f | R$ %8.2f\n",
                atual->item.codigoRecurso,
                atual->item.qtd,
                atual->item.diasEvento,
                atual->item.valorUnitario,
                atual->item.subtotal);
            atual = atual->prox;
        }
    }
    printf("\nCusto Total de Recursos: R$ %.2f\n", evento->custoTotalRecursos);
}

// ========== EQUIPE DO EVENTO ==========
void menuEventoAdicionarEquipe(TipoEvento *evento, ListaEquipe *listaEquipe, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    int codigo = recebeID(config->validar_dados);
    TipoEquipe *eq = equipeBuscar(listaEquipe, codigo);
    if (eq == NULL) { printNaoEncontrado(); return; }

    int numDias = recebeInt(1, 365, "Numero de dias (ou dias de contrato)", "#", config->validar_dados);
    double valorDiaria = eq->valorDiariaHora; // usa valor cadastrado

    if ( eventoUnirEquipe(evento, listaEquipe, codigo, valorDiaria, numDias) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuEventoRemoverEquipe(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    int codigo = recebeID(config->validar_dados);
    if ( eventoRemoverEquipe(evento, codigo) ) printRemoverSucesso();
    else printRemoverFalha();
}

void menuEventoListarEquipes(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Equipes do Evento", "=");
    ListaEquipeEvento *atual = evento->listaEquipes;
    if (atual == NULL) printf("Nenhuma equipe associada a este evento.\n");
    else {
        printf("Codigo | ValorDiaria | Dias | Subtotal\n");
        while (atual != NULL) {
            printf("%6d | R$ %10.2f | %3d | R$ %8.2f\n",
                atual->item.codigoFunc,
                atual->item.valorDiaria,
                atual->item.numDias,
                atual->item.subtotal);
            atual = atual->prox;
        }
    }
    printf("\nCusto Total de Equipe: R$ %.2f\n", evento->custoTotalEquipe);
}

// ========== FORNECEDORES DO EVENTO ==========
void menuEventoAdicionarFornecedor(TipoEvento *evento, ListaFornecedor *listaFornecedor, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    int codigo = recebeID(config->validar_dados);
    TipoFornecedor *forn = fornecedorBuscar(listaFornecedor, codigo);
    if (forn == NULL) { printNaoEncontrado(); return; }

    char descricao[200];
    recebeString(descricao, 200, "Descricao do servico", "Max. 200", config->validar_dados);
    double valor = recebeFloat(0.0, 1000000.0, "Valor do servico (R$)", "#", config->validar_dados);

    if ( eventoUnirFornecedor(evento, listaFornecedor, codigo, descricao, valor) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuEventoRemoverFornecedor(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    int codigo = recebeID(config->validar_dados);
    if ( eventoRemoverFornecedor(evento, codigo) ) printRemoverSucesso();
    else printRemoverFalha();
}

void menuEventoListarFornecedores(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Fornecedores do Evento", "=");
    ListaFornecedorEvento *atual = evento->listaFornecedores;
    if (atual == NULL) printf("Nenhum fornecedor associado a este evento.\n");
    else {
        printf("Codigo | Descricao | Valor\n");
        while (atual != NULL) {
            printf("%6d | %s | R$ %.2f\n",
                atual->item.codigoFornecedor,
                atual->item.descricaoServico,
                atual->item.valorServico);
            atual = atual->prox;
        }
    }
    printf("\nCusto Total de Fornecedores: R$ %.2f\n", evento->custoTotalForn);
}

// ========== EDITAR DATAS ==========
void menuEventoEditarDatas(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Editar Datas do Evento", "=");
    printItemEvento(*evento);
    
    printf("\n1. Editar Data de Inicio\n");
    printf("2. Editar Data de Fim\n");
    printf("3. Voltar\n");
    
    int escolha = recebeInt(1, 3, "Escolha", "#", config->validar_dados);
    
    if (escolha == 1) {
        printf("\nData de Inicio atual: %02d/%02d/%04d %02d:%02d\n",
            evento->dataInicio.tm_mday,
            evento->dataInicio.tm_mon + 1,
            evento->dataInicio.tm_year + 1900,
            evento->dataInicio.tm_hour,
            evento->dataInicio.tm_min);
        
        int dia = recebeInt(1, 31, "Dia", "#", config->validar_dados);
        int mes = recebeInt(1, 12, "Mes", "#", config->validar_dados);
        int ano = recebeInt(2000, 2100, "Ano", "#", config->validar_dados);
        int hora = recebeInt(0, 23, "Hora", "#", config->validar_dados);
        int minuto = recebeInt(0, 59, "Minuto", "#", config->validar_dados);
        
        evento->dataInicio.tm_mday = dia;
        evento->dataInicio.tm_mon = mes - 1;
        evento->dataInicio.tm_year = ano - 1900;
        evento->dataInicio.tm_hour = hora;
        evento->dataInicio.tm_min = minuto;
        
        printAtualizarSucesso();
    } else if (escolha == 2) {
        printf("\nData de Fim atual: %02d/%02d/%04d %02d:%02d\n",
            evento->dataFim.tm_mday,
            evento->dataFim.tm_mon + 1,
            evento->dataFim.tm_year + 1900,
            evento->dataFim.tm_hour,
            evento->dataFim.tm_min);
        
        int dia = recebeInt(1, 31, "Dia", "#", config->validar_dados);
        int mes = recebeInt(1, 12, "Mes", "#", config->validar_dados);
        int ano = recebeInt(2000, 2100, "Ano", "#", config->validar_dados);
        int hora = recebeInt(0, 23, "Hora", "#", config->validar_dados);
        int minuto = recebeInt(0, 59, "Minuto", "#", config->validar_dados);
        
        evento->dataFim.tm_mday = dia;
        evento->dataFim.tm_mon = mes - 1;
        evento->dataFim.tm_year = ano - 1900;
        evento->dataFim.tm_hour = hora;
        evento->dataFim.tm_min = minuto;
        
        printAtualizarSucesso();
    }
}

// ========== EDITAR DADOS BÁSICOS ==========
void menuEventoEditarDados(TipoEvento *evento, ListaCliente *listaCliente, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Editar Dados do Evento", "=");
    printItemEvento(*evento);
    
    printf("\n1. Editar Nome\n");
    printf("2. Editar Local\n");
    printf("3. Editar Cidade\n");
    printf("4. Editar UF\n");
    printf("5. Editar Margem de Lucro\n");
    printf("6. Editar Observacoes\n");
    printf("7. Voltar\n");
    
    int escolha = recebeInt(1, 7, "Escolha", "#", config->validar_dados);
    
    switch (escolha) {
        case 1:
            recebeString(evento->nome, 100, "Digite o novo Nome", "Max. 100", config->validar_dados);
            printAtualizarSucesso();
            break;
        case 2:
            recebeString(evento->localEvento, 150, "Digite o novo Local", "Max. 150", config->validar_dados);
            printAtualizarSucesso();
            break;
        case 3:
            recebeString(evento->cidade, 50, "Digite a nova Cidade", "Max. 50", config->validar_dados);
            printAtualizarSucesso();
            break;
        case 4:
            recebeString(evento->uf, 4, "Digite a nova UF", "Max. 4", config->validar_dados);
            printAtualizarSucesso();
            break;
        case 5:
            evento->margemLucro = recebeFloat(0.0, 100.0, "Digite a nova Margem (%)", "0.0 - 100.0", config->validar_dados);
            eventoRecalcularTotais(evento);
            printAtualizarSucesso();
            break;
        case 6:
            recebeString(evento->obs, 500, "Digite as novas Observacoes", "Max. 500", config->validar_dados);
            printAtualizarSucesso();
            break;
        case 7:
            break;
    }
}

// ========== GERENCIAR COMPLETO ==========
void menuEventoGerenciarCompleto(ListaEvento **listaEvento, ListaRecurso *listaRecurso,
                                  ListaEquipe *listaEquipe, ListaFornecedor *listaFornecedor,
                                  TipoConfig *config) {
    int ID = recebeID(config->validar_dados);
    TipoEvento *evento = eventoBuscar(*listaEvento, ID);
    
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    int escolha = 0;
    do {
        
        printMenuEventoGerenciar(evento, config);

        escolha = recebeInt(0, 7, "Escolha", "#", config->validar_dados);
        
        switch (escolha) {
            case 1:
                menuEventoEditarDados(evento, NULL, config);
                esperaEnter();
                break;
            case 2:
                menuEventoEditarDatas(evento, config);
                esperaEnter();
                break;
            case 3: {
                int subOpcao = 0;
                do {
                    limparTela();
                    printf("1. Adicionar Recurso\n");
                    printf("2. Remover Recurso\n");
                    printf("3. Listar Recursos\n");
                    printf("4. Voltar\n");
                    subOpcao = recebeInt(1, 4, "Escolha", "#", config->validar_dados);
                    
                    switch (subOpcao) {
                        case 1:
                            menuEventoAdicionarRecurso(evento, listaRecurso, config);
                            esperaEnter();
                            break;
                        case 2:
                            menuEventoRemoverRecurso(evento, config);
                            esperaEnter();
                            break;
                        case 3:
                            menuEventoListarRecursos(evento, config);
                            esperaEnter();
                            break;
                        case 4:
                            break;
                    }
                } while (subOpcao != 4);
                break;
            }
            case 4: {
                int subOpcao = 0;
                do {
                    limparTela();
                    printf("1. Adicionar Equipe\n");
                    printf("2. Remover Equipe\n");
                    printf("3. Listar Equipes\n");
                    printf("4. Voltar\n");
                    subOpcao = recebeInt(1, 4, "Escolha", "#", config->validar_dados);
                    
                    switch (subOpcao) {
                        case 1:
                            menuEventoAdicionarEquipe(evento, listaEquipe, config);
                            esperaEnter();
                            break;
                        case 2:
                            menuEventoRemoverEquipe(evento, config);
                            esperaEnter();
                            break;
                        case 3:
                            menuEventoListarEquipes(evento, config);
                            esperaEnter();
                            break;
                        case 4:
                            break;
                    }
                } while (subOpcao != 4);
                break;
            }
            case 5: {
                int subOpcao = 0;
                do {
                    limparTela();
                    printf("1. Adicionar Fornecedor\n");
                    printf("2. Remover Fornecedor\n");
                    printf("3. Listar Fornecedores\n");
                    printf("4. Voltar\n");
                    subOpcao = recebeInt(1, 4, "Escolha", "#", config->validar_dados);
                    
                    switch (subOpcao) {
                        case 1:
                            menuEventoAdicionarFornecedor(evento, listaFornecedor, config);
                            esperaEnter();
                            break;
                        case 2:
                            menuEventoRemoverFornecedor(evento, config);
                            esperaEnter();
                            break;
                        case 3:
                            menuEventoListarFornecedores(evento, config);
                            esperaEnter();
                            break;
                        case 4:
                            break;
                    }
                } while (subOpcao != 4);
                break;
            }
            case 6:
                menuEventoMudarStatus(*listaEvento, config);
                esperaEnter();
                break;
            case 7:
                menuEventoRelatorio(evento, config);
                esperaEnter();
                break;
            case 0:
                break;
            default:
                printOpcaoInvalida();
                esperaEnter();
        }
    } while (escolha != 0);
}

// ========== MUDAR STATUS ==========
void menuEventoMudarStatus(ListaEvento *listaEvento, TipoConfig *config) {
    int ID = recebeID(config->validar_dados);
    TipoEvento *evento = eventoBuscar(listaEvento, ID);
    
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    printItemEvento(*evento);
    
    printf("\n1. Orcamento\n");
    printf("2. Aprovado\n");
    printf("3. Finalizado\n");
    printf("4. Cancelado\n");
    
    int escolha = recebeInt(1, 4, "Escolha o novo status", "#", config->validar_dados);
    
    int sucesso = 0;
    switch (escolha) {
        case 1:
            sucesso = eventoOrcamento(evento);
            break;
        case 2:
            sucesso = eventoAprovar(evento);
            break;
        case 3:
            sucesso = eventoFinalizar(evento);
            break;
        case 4:
            sucesso = eventoCancelar(evento);
            break;
    }
    
    if (sucesso) printAtualizarSucesso();
    else printAtualizarFalha();
}
// ========== RELATÓRIO ==========
void menuEventoRelatorio(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Relatorio do Evento", "=");
    printItemEvento(*evento);
    printf("\nCustos:\n");
    printf("  Recursos: R$ %.2f\n", evento->custoTotalRecursos);
    printf("  Equipe: R$ %.2f\n", evento->custoTotalEquipe);
    printf("  Fornecedores: R$ %.2f\n", evento->custoTotalForn);
    printf("  TOTAL: R$ %.2f\n", evento->custoTotal);
    printf("\nMargem de Lucro: %.2f%%\n", evento->margemLucro);
    printf("Valor Final: R$ %.2f\n", evento->valorFinal);
}