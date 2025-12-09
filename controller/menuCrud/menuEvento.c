#include "menuEvento.h"

// ========== FUNCAO PARA RECEBER DADOS DO EVENTO ==========
TipoEvento menuEventoRecebe(TipoConfig *config, ListaCliente *listaCliente) {
    // Recebe um novo Evento do usuario e retorna o evento preenchido
    TipoEvento evento;
    eventoInit(&evento);

    // Recebe os dados do evento
    evento.id = 0; // ID sera atribuido automaticamente
    // Seleciona o cliente
    // Printa a lista de clientes para ajudar na selecao
    menuClienteListar(listaCliente, config);
    evento.idCliente = recebeInt(1, 100000, "Digite o ID do Cliente associado ao Evento", "#", config->validar_dados);
    recebeString(evento.nome, 100, "Digite o Nome do Evento", "Max. 100", config->validar_dados);
    recebeString(evento.localEvento, 150, "Digite o Local do Evento", "Max. 150", config->validar_dados);
    recebeString(evento.cidade, 50, "Digite a Cidade do Evento", "Max. 50", config->validar_dados);
    recebeString(evento.uf, 4, "Digite a UF do Evento", "Max. 4", config->validar_dados);
    evento.margemLucro = recebeInt(0,100, "Digite a margem de Lucro", "Entre 0 e 100", config->validar_dados);
    
    // Recebe datas
    printMensagem("Data de Inicio do Evento", "-");
    evento.dataInicio.tm_mday = recebeInt(1, 31, "Dia", "#", config->validar_dados);
    evento.dataInicio.tm_mon  = recebeInt(1, 12, "Mes", "#", config->validar_dados);
    evento.dataInicio.tm_year = recebeInt(1900, 3000, "Ano", "#", config->validar_dados) - 1900;
    printMensagem("Data de Fim do Evento", "-");
    evento.dataFim.tm_mday = recebeInt(1, 31, "Dia", "#", config->validar_dados);
    evento.dataFim.tm_mon  = recebeInt(1, 12, "Mes", "#", config->validar_dados);
    evento.dataFim.tm_year = recebeInt(1900, 3000, "Ano", "#", config->validar_dados) - 1900;

    return evento;
}

// ========== MENU PRINCIPAL DE EVENTOS ==========
void menuEvento(ListaEvento **listaEvento, ListaCliente **listaCliente,
                ListaRecurso **listaRecurso, ListaEquipe **listaEquipe, 
                ListaFornecedor **listaFornecedor, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        printMenuEventos(config);

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 4, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Adicionar Evento
                menuEventoAdicionar(listaEvento,*listaCliente, config);
                esperaEnter();
                break;
            case 2:
                // Remover Evento
                menuEventoRemover(listaEvento, config);
                esperaEnter();
                break;
            case 3:
                // Buscar e editar evento
                menuEventoGerenciar(*listaEvento, *listaRecurso, *listaEquipe, *listaFornecedor, *listaCliente, config);
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

    // so' pode remover se o evento estiver em orcamento ou cancelado
    if (evento->status != STATUS_ORCAMENTO && evento->status != STATUS_CANCELADO) {
        printMensagem("Apenas eventos em orcamento ou cancelados podem ser removidos", "!");
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

    // so' pode atualizar se o evento estiver em orcamento
    if (velhoEvento->status != STATUS_ORCAMENTO) {
        printMensagem("Apenas eventos em orcamento podem ser atualizados", "!");
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

    // barra de baixo
    printf("\n======================================================================");
}

//===============================================
// MENU DE GERENCIAR EVENTO COMPLETO
void menuEventoGerenciar(ListaEvento *listaEvento, ListaRecurso *listaRecurso, 
                         ListaEquipe *listaEquipe, ListaFornecedor *listaFornecedor,
                         ListaCliente *listaCliente, TipoConfig *config) 
{   // menu completo para gerenciar um evento

    int ID = recebeID(config->validar_dados); // Recebe o ID do evento
    TipoEvento *evento = eventoBuscar(listaEvento, ID);
    
    if (evento == NULL) {
        printNaoEncontrado();
        esperaEnter();
        return;
    }

    
    // Menu para gerenciar recursos, equipes e fornecedores
    int escolha = 0;
    do {
        // Printa o menu de gerenciar evento
        limparTela();
        printMenuEventoGerenciar(evento, config);
        
        escolha = recebeInt(0, 9, "Digite uma opcao", "#", config->validar_dados);
        
        switch (escolha) {
            case 1:
                menuEventoEditarDados(evento, listaCliente, config);
                break;
            case 2:
                menuEventoRecurso(listaEvento,evento,listaRecurso,config);
                break;
            case 3:
                menuEventoEquipe(listaEvento,evento,listaEquipe,config);
                break;
            case 4:
                menuEventoFornecedor(listaEvento,evento,listaFornecedor,config);
                break;
            case 5:
                menuEventoMudarStatus(evento,config);
                break;
            case 6:
                break;

        }
    } while (escolha != 0);
}

// ========== RECURSOS DO EVENTO ==========
void menuEventoRecurso(ListaEvento *listaEvento, TipoEvento *evento, ListaRecurso *listaRecurso, TipoConfig *config){
    // menu de gerenciar recursos do evento
    int escolha = 0;
    do {
        // Printa o menu de gerenciar recursos do evento
        limparTela();
        printMenuEventoGerenciarRecursos(evento, config);
        
        escolha = recebeInt(0, 3, "Digite uma opcao", "#", config->validar_dados);
        
        switch (escolha) {
            case 1:
                menuEventoRecursoAdicionar(listaEvento, evento, listaRecurso, config);
                esperaEnter();
                break;
            case 2:
                menuEventoRecursoRemover(listaRecurso, evento, config);
                esperaEnter();
                break;
            case 3:
                menuEventoRecursoListar(listaRecurso, evento, config);
                esperaEnter();
                break;
        }
    } while (escolha != 0);
}

void menuEventoRecursoAdicionar(ListaEvento *listaEvento, TipoEvento *evento, ListaRecurso *listaRecurso, TipoConfig *config) {
    // Adiciona um recurso ao evento

    //===========================================
    // so pode adicionar recurso se o evento estiver em orcamento
    if (evento->status != STATUS_ORCAMENTO) {
        printMensagem("Apenas eventos em orcamento podem ser editados", "!");
        return;
    }

    //===========================================
    // Primeiro mostra todos os recursos disponiveis
    menuRecursoListar(listaRecurso, config);

    // Depois recebe o ID do recurso q vai ser adicionado
    int idRecurso = recebeInt(0, 100000,"Digite o ID do recurso a adicionar", "#", config->validar_dados);
    TipoRecurso *recurso = recursoBuscar(listaRecurso, idRecurso);
    if (recurso == NULL) {
        printNaoEncontrado();
        return;
    }

    // Se o recurso ja' estiver no evento, apaga o antigo antes de adicionar o novo
    eventoRemoverRecurso(evento, idRecurso);

    //===========================================
    // Declara um novo item de recurso do evento
    ItemRecursoEvento novoItem;

    // Atribui os dados basicos
    novoItem.idRecurso    = idRecurso;
    novoItem.precoUnitario = recurso->valorLocacao;
    
    // Atribui os dados recebidos
    novoItem.qtdTempo   = recebeInt(1, 365, "Numero de dias de uso do recurso", "#", config->validar_dados);
    novoItem.qtd        = recebeInt(1, recurso->qtdEstoque, "Quantidade desejada deste recurso", "#", config->validar_dados);
    novoItem.precoTotal = (novoItem.qtd * novoItem.precoUnitario) * novoItem.qtdTempo;

    //===========================================
    // Verifica se o os dias estao ok
    int duracaoEvento = calculaDiferencaDias(evento->dataInicio, evento->dataFim);
    if (novoItem.qtdTempo > duracaoEvento) {
        printMensagem("Quantidade Invalida de Dias", "!");
        return;
    }

    // Verifica se a qtd esta ok
    int qtdAlocada  = recursoContarUsoPeriodo(listaEvento, idRecurso, evento->dataInicio, evento->dataFim);
    if ((qtdAlocada + novoItem.qtd) > recurso->qtdEstoque) {
        printMensagem("Nao ha estoque suficiente", "!");
        return;
    }

    //===========================================
    // Adiciona o recurso ao evento
    if ( eventoAdicionarRecurso(evento, novoItem) ) {
        printAdicionarSucesso();
    } else {
        printAdicionarFalha();
    }
}

void menuEventoRecursoRemover(ListaRecurso *listaRecurso, TipoEvento *evento, TipoConfig *config) {
    // Remove um recurso do evento

    //===========================================
    // so pode remover recurso se o evento estiver em orcamento
    if (evento->status != STATUS_ORCAMENTO) {
        printMensagem("Apenas eventos em orcamento podem ser editados", "!");
        return;
    }

    //===========================================
    // Primeiro lista os recursos do evento
    menuEventoRecursoListar(listaRecurso, evento, config);

    // Depois recebe o ID do recurso q vai ser removido
    int idRecurso = recebeInt(0, 100000,"Digite o ID do recurso a remover", "#", config->validar_dados);
    
    // Tenta remover o recurso
    int sucesso = eventoRemoverRecurso(evento, idRecurso);
    if (sucesso) {
        printRemoverSucesso();
    } else {
        printMensagem("Recurso nao encontrado no evento", "!");
    }

}

void menuEventoRecursoListar(ListaRecurso *listaRecurso, TipoEvento *evento, TipoConfig *config) {
    // Lista todos os recursos do evento
    limparTela();
    printMensagem("Recursos do Evento", "=");

    // Lista todos os recursos cadastrados no evento
    if (evento->listaRecursos == NULL) {
        printMensagem("Nenhum recurso adicionado ao evento","#");
        return;
    }
    
    printf("\n======================================================================");
    printf("\n |Nome                    |ID  |QTD.|Dias |Preco Unit. |Preco Total | " );

    ListaRecursoEvento *atual = evento->listaRecursos; // comeca auxiliar no comeco da lista
    while (atual != NULL) {
        // Pega o recurso atual
        TipoRecurso *recursoAtual = recursoBuscar(listaRecurso, atual->item.idRecurso);
        // Printa o item de recurso do evento
        printItemRecursoEvento(atual->item, *recursoAtual);
        atual = atual->prox;
    }
    printf("\n======================================================================");
}

// ========== EQUIPE DO EVENTO ==========
void menuEventoEquipe(ListaEvento *listaEvento, TipoEvento *evento, ListaEquipe *listaEquipe, TipoConfig *config){
    // menu de gerenciar equipes do evento
    int escolha = 0;
    do {
        // Printa o menu de gerenciar equipes do evento
        limparTela();
        printMenuEventoGerenciarEquipes(evento, config);
        
        escolha = recebeInt(0, 3, "Digite uma opcao", "#", config->validar_dados);
        
        switch (escolha) {
            case 1:
                menuEventoEquipeAdicionar(listaEvento, evento, listaEquipe, config);
                esperaEnter();
                break;
            case 2:
                menuEventoEquipeRemover(listaEquipe, evento, config);
                esperaEnter();
                break;
            case 3:
                menuEventoEquipeListar(listaEquipe, evento, config);
                esperaEnter();
                break;
        }
    } while (escolha != 0);
}


void menuEventoEquipeAdicionar(ListaEvento *listaEvento, TipoEvento *evento, ListaEquipe *listaEquipe, TipoConfig *config) {
    // Adiciona uma equipe ao evento

    //===========================================
    // so pode adicionar equipe se o evento estiver em orcamento
    if (evento->status != STATUS_ORCAMENTO) {
        printMensagem("Apenas eventos em orcamento podem ser editados", "!");
        return;
    }

    //===========================================
    // Primeiro mostra todos as equipes disponiveis
    menuEquipeListar(listaEquipe, config);

    // Depois recebe o ID da equipe q vai ser adicionado
    int idEquipe = recebeInt(0, 100000,"Digite o ID da equipe a adicionar", "#", config->validar_dados);
    TipoEquipe *equipe = equipeBuscar(listaEquipe, idEquipe);
    if (equipe == NULL) {
        printNaoEncontrado();
        return;
    }

    // Se a equipe ja' estiver no evento, apaga o antigo antes de adicionar o novo
    eventoRemoverEquipe(evento, idEquipe);

    //===========================================
    // Declara um novo item de equipe do evento
    ItemEquipeEvento novoItem;

    // Atribui os dados basicos
    novoItem.idEquipe    = idEquipe;
    novoItem.precoValor = equipe->valor;
    
    // Atribui os dados recebidos
    novoItem.qtdTempo   = recebeInt(1, 365, "Numero de dias de uso da equipe", "#", config->validar_dados);

    //===========================================
    // Verifica se o os dias estao ok
    int duracaoEvento = calculaDiferencaDias(evento->dataInicio, evento->dataFim);
    if (novoItem.qtdTempo > duracaoEvento) {
        printMensagem("A equipe nao pode ser usada por mais dias do que a duracao do evento", "!");
        return;
    }

    // Verifica se a equipe ja' esta alocada nesse dia
    if (equipeEstaAlocadaPeriodo(listaEvento, idEquipe, evento->dataInicio, evento->dataFim)) {
        printMensagem("A equipe ja esta alocada em outro evento nesse periodo", "!");
        return;
    }

    //===========================================
    // Adiciona a equipe ao evento
    if ( eventoAdicionarEquipe(evento, novoItem) ) {
        printAdicionarSucesso();
    } else {
        printAdicionarFalha();
    }
}

void menuEventoEquipeRemover(ListaEquipe *listaEquipe, TipoEvento *evento, TipoConfig *config) {
    // Remove uma equipe do evento

    //===========================================
    // so pode remover equipe se o evento estiver em orcamento
    if (evento->status != STATUS_ORCAMENTO) {
        printMensagem("Apenas eventos em orcamento podem ser editados", "!");
        return;
    }

    //===========================================
    // Primeiro lista os recursos do evento
    menuEventoEquipeListar(listaEquipe, evento, config);

    // Depois recebe o ID da equipe q vai ser removida
    int idEquipe = recebeInt(0, 100000,"Digite o ID da equipe a remover", "#", config->validar_dados);
    
    // Tenta remover a equipe
    int sucesso = eventoRemoverEquipe(evento, idEquipe);
    if (sucesso) {
        printRemoverSucesso();
    } else {
        printMensagem("Equipe nao encontrada no evento", "!");
    }

}

void menuEventoEquipeListar(ListaEquipe *listaEquipe, TipoEvento *evento, TipoConfig *config) {
    // Lista todos os recursos do evento
    limparTela();
    printMensagem("Recursos do Evento", "=");

    // Lista todos os recursos cadastrados no evento
    if (evento->listaRecursos == NULL) {
        printMensagem("Nenhuma equipe adicionado ao evento","#");
        return;
    }
    
    ListaEquipeEvento *atual = evento->listaEquipes; // comeca auxiliar no comeco da lista
    while (atual != NULL) {
        // Pega a equipe atual
        TipoEquipe *equipeAtual = equipeBuscar(listaEquipe, atual->item.idEquipe);
        // Printa o item de equipe do evento
        printItemEquipeEvento(atual->item, *equipeAtual);
        atual = atual->prox;
    }
    printf("\n======================================================================");
}


// ========== FORNECEDORES DO EVENTO ==========

void menuEventoFornecedor(ListaEvento *listaEvento, TipoEvento *evento, ListaFornecedor *listaFornecedor, TipoConfig *config){
    // menu de gerenciar fornecedores do evento
    int escolha = 0;
    do {
        // Printa o menu de gerenciar fornecedores do evento
        limparTela();
        printMenuEventoGerenciarFornecedores(evento, config);
        
        escolha = recebeInt(0, 3, "Digite uma opcao", "#", config->validar_dados);
        
        switch (escolha) {
            case 1:
                menuEventoFornecedorAdicionar(listaEvento, evento, listaFornecedor, config);
                esperaEnter();
                break;
            case 2:
                menuEventoFornecedorRemover(listaFornecedor, evento, config);
                esperaEnter();
                break;
            case 3:
                menuEventoFornecedorListar(listaFornecedor, evento, config);
                esperaEnter();
                break;
        }
    } while (escolha != 0);
}


void menuEventoFornecedorAdicionar(ListaEvento *listaEvento, TipoEvento *evento, ListaFornecedor *listaFornecedor, TipoConfig *config) {
    // Adiciona um fornecedor ao evento

    //===========================================
    // so pode adicionar fornecedor se o evento estiver em orcamento
    if (evento->status != STATUS_ORCAMENTO) {
        printMensagem("Apenas eventos em orcamento podem ser editados", "!");
        return;
    }

    //===========================================
    // Primeiro mostra todos os fornecedores disponiveis
    menuFornecedorListar(listaFornecedor, config);

    // Depois recebe o ID do fornecedor q vai ser adicionado
    int idFornecedor = recebeInt(0, 100000,"Digite o ID do fornecedor a adicionar", "#", config->validar_dados);
    TipoFornecedor *fornecedor = fornecedorBuscar(listaFornecedor, idFornecedor);
    if (fornecedor == NULL) {
        printNaoEncontrado();
        return;
    }

    // Se o fornecedor ja' estiver no evento, apaga o antigo antes de adicionar o novo
    eventoRemoverFornecedor(evento, idFornecedor);

    //===========================================
    // Declara um novo item de fornecedor do evento
    ItemFornecedorEvento novoItem;

    // Atribui os dados basicos
    novoItem.idFornecedor    = idFornecedor;
    novoItem.precoValor = fornecedor->valor;
    
    // Atribui os dados recebidos
    novoItem.qtdTempo   = recebeInt(1, 365, "Numero de dias de uso do fornecedor", "#", config->validar_dados);
    //===========================================
    // Verifica se o os dias estao ok
    int duracaoEvento = calculaDiferencaDias(evento->dataInicio, evento->dataFim);
    if (novoItem.qtdTempo > duracaoEvento) {
        printMensagem("O fornecedor nao pode ser usado por mais dias do que a duracao do evento", "!");
        return;
    }

    //===========================================
    // Adiciona o fornecedor ao evento
    if ( eventoAdicionarFornecedor(evento, novoItem) ) {
        printAdicionarSucesso();
    } else {
        printAdicionarFalha();
    }
}

void menuEventoFornecedorRemover(ListaFornecedor *listaFornecedor, TipoEvento *evento, TipoConfig *config) {
    // Remove um fornecedor do evento

    //===========================================
    // so pode remover fornecedor se o evento estiver em orcamento
    if (evento->status != STATUS_ORCAMENTO) {
        printMensagem("Apenas eventos em orcamento podem ser editados", "!");
        return;
    }

    //===========================================
    // Primeiro lista os recursos do evento
    menuEventoFornecedorListar(listaFornecedor, evento, config);

    // Depois recebe o ID do fornecedor que vai ser removido
    int idFornecedor = recebeInt(0, 100000,"Digite o ID do fornecedor a remover", "#", config->validar_dados);
    
    // Tenta remover o fornecedor
    int sucesso = eventoRemoverFornecedor(evento, idFornecedor);
    if (sucesso) {
        printRemoverSucesso();
    } else {
        printMensagem("Fornecedor nao encontrado no evento", "!");
    }

}

void menuEventoFornecedorListar(ListaFornecedor *listaFornecedor, TipoEvento *evento, TipoConfig *config) {
    // Lista todos os recursos do evento
    limparTela();
    printMensagem("Recursos do Evento", "=");

    // Lista todos os recursos cadastrados no evento
    if (evento->listaRecursos == NULL) {
        printMensagem("Nenhum fornecedor adicionado ao evento","#");
        return;
    }
    
    ListaFornecedorEvento *atual = evento->listaFornecedores; // comeca auxiliar no comeco da lista
    while (atual != NULL) {
        // Pega o fornecedor atual
        TipoFornecedor *fornecedorAtual = fornecedorBuscar(listaFornecedor, atual->item.idFornecedor);
        // Printa o item de fornecedor do evento
        printItemFornecedorEvento(atual->item, *fornecedorAtual);
        atual = atual->prox;
    }
    printf("\n======================================================================");
}



// ========== EDITAR DADOS BASICOS ==========
void menuEventoEditarDados(TipoEvento *evento, ListaCliente *listaCliente, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Editar Dados do Evento", "=");
    printItemEvento(*evento);
    
    
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
            eventoCalcularTotal(evento);
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

// ========== MUDAR STATUS ==========
void menuEventoMudarStatus(TipoEvento *evento, TipoConfig *config) {
    
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

// ========== RELATORIO ==========
void menuEventoRelatorio(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    //printRelatorioEvento(*evento);
}