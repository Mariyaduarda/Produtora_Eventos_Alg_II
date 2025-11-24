#include "menuEvento.h"

// ========== FUNÇÃO PARA RECEBER DADOS DO EVENTO ==========
TipoEvento menuEventoRecebe(TipoConfig *config, ListaCliente *listaCliente) {
    // vai receber um novo evento do usuario e retorna o evento pronto
    TipoEvento evento;
    eventoInit(&evento);
    
    limparTela();
    imprimirCabecalho("CADASTRO DE EVENTO", config);
    char entradaInicio[11], entradaFim[11];

    // Nome do evento
    printf("\n%sNome do Evento:%s ", config->cor, RESET);
    recebeString(evento.nome, 100, "Digite o nome do evento", "Max. 100", config->validar_dados);

    evento.dataInicio.tm_mday = recebeInt();
    evento.dataInicio.tm_mday = recebeInt();
    evento.dataInicio.tm_year = recebeInt() - 1900;

    printf("\n%s=== DATA DE FIM ===%s\n", config->cor, RESET);
    printf("%sDia:%s ", config->cor, RESET);
    evento.dataFim.tm_mday = recebeInt(1, 31, "Dia", "1-31", config->validar_dados);
    printf("%sMês:%s ", config->cor, RESET);
    evento.dataFim.tm_mon = recebeInt(1, 12, "Mês", "1-12", config->validar_dados) - 1;
    printf("%sAno:%s ", config->cor, RESET);
    evento.dataFim.tm_year = recebeInt(1900, 2100, "Ano", "1900-2035", config->validar_dados) - 1900;

    //recebeString(evento.entradaInicio, 10, "Digite data de início (dd/mm/aaaa)", "Formato inválido", config->validar_dados);
    //recebeString(evento.entradaFim, 10, "Digite data de início (dd/mm/aaaa)", "Formato inválido", config->validar_dados);
    recebeString(evento.localEvento, 150, "Digite o local do evento", "Max. 150", config->validar_dados);
    recebeString(evento.cidade, 50, "Digite a cidade do evento", "Max. 50", config->validar_dados);
    recebeString(evento.uf, 4, "Digite o estado do evento", "Max. 4", config->validar_dados);
    evento.codigoCliente = recebeInt();
    recebeString(evento.obs, 500, "Digite as observacoes do evento", "Max. 500", config->validar_dados);
    evento.margemLucro = recebeDouble();

    TipoCliente *cliente = clienteBuscar(listaCliente, evento.codigoCliente);
    if (cliente == NULL) {
        printf("\n%s[AVISO] Cliente não encontrado!%s\n", VERMELHO, RESET);
        pausar();
        eventoInit(&evento);
        return evento;
    }
    
    // Datas
    printf("\n%s=== DATA DE INÍCIO ===%s\n", config->cor, RESET);
    printf("%sDia:%s ", config->cor, RESET);
    evento.dataInicio.tm_mday = recebeInt();
    printf("%sMês:%s ", config->cor, RESET);
    evento.dataInicio.tm_mday = recebeInt();
    printf("%sAno:%s ", config->cor, RESET);
    evento.dataInicio.tm_year = recebeInt() - 1900;
    
    printf("\n%s=== DATA DE FIM ===%s\n", config->cor, RESET);
    printf("%sDia:%s ", config->cor, RESET);
    evento.dataFim.tm_mday = recebeInt();
    printf("%sMês:%s ", config->cor, RESET);
    evento.dataFim.tm_mon = recebeInt() - 1;
    printf("%sAno:%s ", config->cor, RESET);
    evento.dataFim.tm_year = recebeInt() - 1900;
    
    // Local
    printf("\n%sLocal do Evento:%s ", config->cor, RESET);
    recebeString(evento.localEvento, 150);
    
    printf("%sCidade:%s ", config->cor, RESET);
    recebeString(evento.cidade, 50);
    
    printf("%sUF:%s ", config->cor, RESET);
    recebeString(evento.uf, 3);
    
    // Margem de lucro
    printf("\n%sMargem de Lucro (%%):%s ", config->cor, RESET);
    evento.margemLucro = recebeDouble();

    evento.status = STATUS_ORCAMENTO;
    evento.listaRecursos = NULL;
    evento.listaEquipes = NULL;
    evento.listaFornecedores = NULL;
    
    eventoRecalcularTotais(&evento);
    
    return evento;
}

// ========== MENU PRINCIPAL DE EVENTOS ==========
void menuEvento(TipoEvento* evento,ListaEvento **listaEvento, ListaCliente *listaCliente,
                ListaRecurso *listaRecurso, ListaEquipe *listaEquipe, 
                ListaFornecedor *listaFornecedor, TipoConfig *config) {
    
    int escolha = 0;
    do {
       // exibi menu do evento
       printfMenuEvento(*evento);
       escolha = recebeInt(0, 2, "Digite uma opcao", "#", config->validar_dados);

        opcao = recebeInt();
        
        switch(escolha) {
            case 1:
                menuEventoAdicionar(listaEvento, listaCliente, config);
                esperaEnter();
                break;
            case 2:
                menuEventoRemover(listaEvento, config);
                esperaEnter();
                break;
            case 3:
                menuEventoAtualizar(listaEvento, listaCliente, config);
                esperaEnter();
                break;
            case 4:
                menuEventoBuscar(*listaEvento, config);
                esperaEnter();
                break;
            case 5:
                menuEventoListar(*listaEvento, config);
                esperaEnter();
                break;
            case 6:
                menuEventoGerenciar(*listaEvento, listaRecurso, listaEquipe, listaFornecedor, config);
                esperaEnter();
                break;
            case 7:
                menuEventoMudarStatus(*listaEvento, config);
                esperaEnter();
                break;
            case 8:
                {
                    limparTela();
                    imprimirCabecalho("RELATÓRIO DO EVENTO", config);
                    printf("\n%sDigite o ID do evento:%s ", config->cor, RESET);
                    int id = recebeInt();
                    TipoEvento *evento = eventoBuscar(*listaEvento, id);
                    if (evento != NULL) {
                        menuEventoRelatorio(evento, config);
                    } else {
                        msgErro("Evento não encontrado!");
                    }
                    pausar();
                }
                break;
            case 0:
                msgInfo("Voltando...");
                break;
            default:
                msgErro("Opção inválida!");
                pausar();
        }
        
    } while(opcao != 0);
}

// ========== CRUD BÁSICO ==========
void menuEventoAdicionar(ListaEvento **listaEvento, ListaCliente *listaCliente, TipoConfig *config) {
    TipoEvento novoEvento = menuEventoRecebe(config, listaCliente);
    
    if (strlen(novoEvento.nome) > 1) {
        if (eventoAdicionar(listaEvento, novoEvento)) {
            msgSucesso("Evento adicionado com sucesso!");
        } else {
            msgErro("Erro ao adicionar evento!");
        }
    }
    pausar();
}

void menuEventoRemover(ListaEvento **listaEvento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("REMOVER EVENTO", config);
    
    printf("\n%sDigite o ID do evento a remover:%s ", config->cor, RESET);
    int id = recebeInt();
    
    if (eventoRemover(listaEvento, id)) {
        msgSucesso("Evento removido com sucesso!");
    } else {
        msgErro("Erro ao remover evento!");
    }
    pausar();
}

void menuEventoAtualizar(TipoEvento* evento, TipoConfig *config) {


    ListaRecurso *rec = evento->listaRecursos;
    ListaEquipe *eq = evento->listaEquipes;
    ListaFornecedor *forne = evento->listaFornecedores;

    TipoEvento novo = menuEventoRecebe(config);
    *evento = novo;

    evento->listaRecursos = rec;
    evento->listaEquipes = eq;
    evento->listaFornecedores = forne;
}

void menuEventoBuscar(ListaEvento *listaEvento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("BUSCAR EVENTO", config);
    
    printf("\n%sDigite o ID do evento:%s ", config->cor, RESET);
    int id = recebeInt();
    
    TipoEvento *evento = eventoBuscar(listaEvento, id);
    
    if (evento != NULL) {
        printf("\n%s=== EVENTO ENCONTRADO ===%s\n", config->cor, RESET);
        mostrarEvento(evento, config); // Você precisará implementar essa função no mostrarItem.c
    } else {
        msgErro("Evento não encontrado!");
    }
    pausar();
}

void menuEventoListar(ListaEvento *listaEvento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("LISTA DE EVENTOS", config);
    
    if (listaEvento == NULL) {
        msgInfo("Nenhum evento cadastrado.");
        pausar();
        return;
    }
    
    ListaEvento *atual = listaEvento;
    int contador = 0;

    // Listar eventos
    printf("\n===== LISTA DE EVENTOS =====\n");
    ListaEvento *atual = listaEventos;
    while(atual != NULL) {
        if(atual->evento.ativo) {
            printf("\nID: %d | %s\n", atual->evento.id, atual->evento.nome);
            printf("Status: ");
            switch(atual->evento.status) {
                case STATUS_ORCAMENTO: printf("Orçamento\n"); break;
                case STATUS_APROVADO: printf("Aprovado\n"); break;
                case STATUS_FINALIZADO: printf("Finalizado\n"); break;
                case STATUS_CANCELADO: printf("Cancelado\n"); break;
            }
            printf("Valor Final: R$ %.2f\n", atual->evento.valorFinal);
            printf("-----------------------------------\n");
        }
        atual = atual->prox;
    }
    
    if (contador == 0) {
        msgInfo("Nenhum evento ativo encontrado.");
    }
    
    pausar();
}

// ========== GERENCIAR EVENTO ==========
void menuEventoGerenciar(ListaEvento *listaEvento, ListaRecurso *listaRecurso, 
                         ListaEquipe *listaEquipe, ListaFornecedor *listaFornecedor, 
                         TipoConfig *config) {
    
    limparTela();
    imprimirCabecalho("GERENCIAR EVENTO", config);
    
    printf("\n%sDigite o ID do evento:%s ", config->cor, RESET);
    int id = recebeInt();
    
    TipoEvento *evento = eventoBuscar(listaEvento, id);
    
    if (evento == NULL) {
        msgErro("Evento não encontrado!");
        pausar();
        return;
    }
    
    int opcao;
    
    do {
        limparTela();
        imprimirCabecalho("GERENCIAR: " + evento->nome, config);
        
        printf("\n%s=== RECURSOS ===%s\n", config->cor, RESET);
        printf("%s1.%s Adicionar Recurso\n", config->cor, RESET);
        printf("%s2.%s Remover Recurso\n", config->cor, RESET);
        printf("%s3.%s Listar Recursos\n", config->cor, RESET);
        
        printf("\n%s=== EQUIPE ===%s\n", config->cor, RESET);
        printf("%s4.%s Adicionar Membro da Equipe\n", config->cor, RESET);
        printf("%s5.%s Remover Membro da Equipe\n", config->cor, RESET);
        printf("%s6.%s Listar Equipe\n", config->cor, RESET);
        
        printf("\n%s=== FORNECEDORES ===%s\n", config->cor, RESET);
        printf("%s7.%s Adicionar Fornecedor\n", config->cor, RESET);
        printf("%s8.%s Remover Fornecedor\n", config->cor, RESET);
        printf("%s9.%s Listar Fornecedores\n", config->cor, RESET);
        
        printf("\n%s0.%s Voltar\n", config->cor, RESET);
        
        printf("\n%sOpção:%s ", config->cor, RESET);
        opcao = recebeInt();
        
        switch(opcao) {
            case 1:
                menuEventoAdicionarRecurso(evento, listaRecurso, config);
                break;
            case 2:
                menuEventoRemoverRecurso(evento, config);
                break;
            case 3:
                menuEventoListarRecursos(evento, config);
                break;
            case 4:
                menuEventoAdicionarEquipe(evento, listaEquipe, config);
                break;
            case 5:
                menuEventoRemoverEquipe(evento, config);
                break;
            case 6:
                menuEventoListarEquipes(evento, config);
                break;
            case 7:
                menuEventoAdicionarFornecedor(evento, listaFornecedor, config);
                break;
            case 8:
                menuEventoRemoverFornecedor(evento, config);
                break;
            case 9:
                menuEventoListarFornecedores(evento, config);
                break;
            case 0:
                msgInfo("Voltando...");
                break;
            default:
                msgErro("Opção inválida!");
                pausar();
        }
        
    } while(opcao != 0);
}

// ========== RECURSOS DO EVENTO ==========
void menuEventoAdicionarRecurso(TipoEvento *evento, ListaRecurso *listaRecurso, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("ADICIONAR RECURSO AO EVENTO", config);
    
    printf("\n%sDigite o ID do recurso:%s ", config->cor, RESET);
    int codigoRecurso = recebeInt();
    
    printf("%sQuantidade:%s ", config->cor, RESET);
    int qtd = recebeInt();
    
    printf("%sDias do evento:%s ", config->cor, RESET);
    int dias = recebeInt();
    
    if (eventoUnirRecurso(evento, listaRecurso, codigoRecurso, qtd, dias)) {
        msgSucesso("Recurso adicionado com sucesso!");
    } else {
        msgErro("Erro ao adicionar recurso! Verifique se o recurso existe e tem estoque.");
    }
    pausar();
}

void menuEventoRemoverRecurso(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("REMOVER RECURSO DO EVENTO", config);
    
    printf("\n%sDigite o código do recurso a remover:%s ", config->cor, RESET);
    int codigo = recebeInt();
    
    if (eventoRemoverRecurso(evento, codigo)) {
        msgSucesso("Recurso removido com sucesso!");
    } else {
        msgErro("Erro ao remover recurso!");
    }
    pausar();
}

void menuEventoListarRecursos(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("RECURSOS DO EVENTO", config);
    
    if (evento->listaRecursos == NULL) {
        msgInfo("Nenhum recurso adicionado ao evento.");
        pausar();
        return;
    }
    
    ListaRecurso *atual = evento->listaRecursos;
    
    printf("\n%s%-6s %-15s %-8s %-12s%s\n", config->cor, "Código", "Qtd", "Dias", "Subtotal", RESET);
    printf("%s%s%s\n", config->cor, "---------------------------------------------", RESET);
    
    while (atual != NULL) {
        printf("%-6d %-15d %-8d R$ %.2f\n", 
               atual->item.codigoRecurso,
               atual->item.qtd,
               atual->item.diasEvento,
               atual->item.subtotal);
        atual = atual->prox;
    }
    
    printf("\n%sCusto Total em Recursos: R$ %.2f%s\n", config->cor, evento->custoTotalRecursos, RESET);
    
    pausar();
}

// ========== EQUIPE DO EVENTO ==========
void menuEventoAdicionarEquipe(TipoEvento *evento, ListaEquipe *listaEquipe, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("ADICIONAR MEMBRO DA EQUIPE", config);
    
    printf("\n%sDigite o ID do funcionário:%s ", config->cor, RESET);
    int codigoFunc = recebeInt();
    
    printf("%sValor da diária:%s R$ ", config->cor, RESET);
    double valorDiaria = recebeDouble();
    
    printf("%sNúmero de dias:%s ", config->cor, RESET);
    int numDias = recebeInt();
    
    if (eventoUnirEquipe(evento, listaEquipe, codigoFunc, valorDiaria, numDias)) {
        msgSucesso("Membro da equipe adicionado com sucesso!");
    } else {
        msgErro("Erro ao adicionar membro! Verifique se o funcionário existe.");
    }
    pausar();
}

void menuEventoRemoverEquipe(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("REMOVER MEMBRO DA EQUIPE", config);
    
    printf("\n%sDigite o código do funcionário a remover:%s ", config->cor, RESET);
    int codigo = recebeInt();
    
    if (eventoRemoverEquipe(evento, codigo)) {
        msgSucesso("Membro removido com sucesso!");
    } else {
        msgErro("Erro ao remover membro!");
    }
    pausar();
}

void menuEventoListarEquipes(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("EQUIPE DO EVENTO", config);
    
    if (evento->listaEquipes == NULL) {
        msgInfo("Nenhum membro da equipe adicionado.");
        pausar();
        return;
    }
    
    ListaEquipe *atual = evento->listaEquipes;
    
    printf("\n%s%-6s %-12s %-8s %-12s%s\n", config->cor, "Código", "Diária", "Dias", "Subtotal", RESET);
    printf("%s%s%s\n", config->cor, "---------------------------------------------", RESET);
    
    while (atual != NULL) {
        printf("%-6d R$ %-12.2f %-8d R$ %.2f\n", 
               atual->item.codigoFunc,
               atual->item.valorDiaria,
               atual->item.numDias,
               atual->item.subtotal);
        atual = atual->prox;
    }
    
    printf("\n%sCusto Total da Equipe: R$ %.2f%s\n", config->cor, evento->custoTotalEquipe, RESET);
    
    pausar();
}

// ========== FORNECEDORES DO EVENTO ==========
void menuEventoAdicionarFornecedor(TipoEvento *evento, ListaFornecedor *listaFornecedor, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("ADICIONAR FORNECEDOR", config);
    
    printf("\n%sDigite o ID do fornecedor:%s ", config->cor, RESET);
    int codigoFornecedor = recebeInt();
    
    char descricaoServico[150];
    printf("%sDescrição do serviço:%s ", config->cor, RESET);
    recebeString(descricaoServico, 150);
    
    printf("%sValor do serviço:%s R$ ", config->cor, RESET);
    double valorServico = recebeDouble();
    
    if (eventoUnirFornecedor(evento, listaFornecedor, codigoFornecedor, descricaoServico, valorServico)) {
        msgSucesso("Fornecedor adicionado com sucesso!");
    } else {
        msgErro("Erro ao adicionar fornecedor! Verifique se o fornecedor existe.");
    }
    pausar();
}

void menuEventoRemoverFornecedor(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("REMOVER FORNECEDOR", config);
    
    printf("\n%sDigite o código do fornecedor a remover:%s ", config->cor, RESET);
    int codigo = recebeInt();
    
    if (eventoRemoverFornecedor(evento, codigo)) {
        msgSucesso("Fornecedor removido com sucesso!");
    } else {
        msgErro("Erro ao remover fornecedor!");
    }
    pausar();
}

void menuEventoListarFornecedores(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("FORNECEDORES DO EVENTO", config);
    
    if (evento->listaFornecedores == NULL) {
        msgInfo("Nenhum fornecedor adicionado.");
        pausar();
        return;
    }
    
    ListaFornecedor *atual = evento->listaFornecedores;
    
    printf("\n%s%-6s %-30s %-12s%s\n", config->cor, "Código", "Descrição", "Valor", RESET);
    printf("%s%s%s\n", config->cor, "-----------------------------------------------------", RESET);
    
    while (atual != NULL) {
        printf("%-6d %-30s R$ %.2f\n", 
               atual->item.codigoFornecedor,
               atual->item.descricaoServico,
               atual->item.valorServico);
        atual = atual->prox;
    }
    
    printf("\n%sCusto Total com Fornecedores: R$ %.2f%s\n", config->cor, evento->custoTotalForn, RESET);
    
    pausar();
}

// ========== MUDAR STATUS ==========
void menuEventoMudarStatus(ListaEvento *listaEvento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("MUDAR STATUS DO EVENTO", config);
    
    printf("\n%sDigite o ID do evento:%s ", config->cor, RESET);
    int id = recebeInt();
    
    TipoEvento *evento = eventoBuscar(listaEvento, id);
    
    if (evento == NULL) {
        msgErro("Evento não encontrado!");
        pausar();
        return;
    }
    
    printf("\n%sStatus atual:%s ", config->cor, RESET);
    switch(evento->status) {
        case STATUS_ORCAMENTO:
            printf("Orçamento\n");
            break;
        case STATUS_APROVADO:
            printf("Aprovado\n");
            break;
        case STATUS_FINALIZADO:
            printf("Finalizado\n");
            break;
        case STATUS_CANCELADO:
            printf("Cancelado\n");
            break;
    }
    
    printf("\n%sNovo status:%s\n", config->cor, RESET);
    printf("%s1.%s Orçamento\n", config->cor, RESET);
    printf("%s2.%s Aprovado\n", config->cor, RESET);
    printf("%s3.%s Finalizado\n", config->cor, RESET);
    printf("%s4.%s Cancelado\n", config->cor, RESET);
    printf("\n%sOpção:%s ", config->cor, RESET);
    
    int opcao = recebeInt();
    int sucesso = 0;
    
    switch(opcao) {
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
        default:
            msgErro("Opção inválida!");
            pausar();
            return;
    }
    
    if (sucesso) {
        msgSucesso("Status alterado com sucesso!");
    } else {
        msgErro("Erro ao alterar status!");
    }
    pausar();
}

// ========== RELATÓRIO ==========
void menuEventoRelatorio(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    imprimirCabecalho("RELATÓRIO COMPLETO DO EVENTO", config);

    printf("\n%s=== INFORMAÇÕES GERAIS ===%s\n", config->cor, RESET);
    printf("ID: %d\n", evento->id);
    printf("Nome: %s\n", evento->nome);
    printf("Cliente: %d\n", evento->codigoCliente);
    printf("Data Início: %02d/%02d/%04d\n",
           evento->dataInicio.tm_mday,
           evento->dataInicio.tm_mon + 1,
           evento->dataInicio.tm_year + 1900);
    printf("Data Fim: %02d/%02d/%04d\n",
           evento->dataFim.tm_mday,
           evento->dataFim.tm_mon + 1,
           evento->dataFim.tm_year + 1900);
    printf("Local: %s - %s/%s\n", evento->localEvento, evento->cidade, evento->uf);

    printf("\n%s=== STATUS ===%s ", config->cor, RESET);
    switch(evento->status) {
        case STATUS_ORCAMENTO:
            printf("Orçamento\n");
            break;
        case STATUS_APROVADO:
            printf("Aprovado\n");
            break;
        case STATUS_FINALIZADO:
            printf("Finalizado\n");
            break;
        case STATUS_CANCELADO:
            printf("Cancelado\n");
            break;
    }

    printf("\n%s=== CUSTOS ===%s\n", config->cor, RESET);
    printf("Recursos:    R$ %.2f\n", evento->custoTotalRecursos);
    printf("Equipe:      R$ %.2f\n", evento->custoTotalEquipe);
    printf("Fornecedores: R$ %.2f\n", evento->custoTotalForn);
    printf("%s--------------------------------%s\n", config->cor, RESET);
    printf("Custo Total: R$ %.2f\n", evento->custoTotal);

    printf("\n%s=== VALORES ===%s\n", config->cor, RESET);
    printf("Margem de Lucro: %.2f%%\n", evento->margemLucro);
    printf("%sValor Final: R$ %.2f%\n", evento->valorFinal);
    }