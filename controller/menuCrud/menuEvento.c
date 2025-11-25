#include "menuEvento.h"

// ========== FUNÇÃO PARA RECEBER DADOS DO EVENTO ==========
TipoEvento menuEventoRecebe(TipoConfig *config, ListaCliente *listaCliente) {
    // Recebe um novo Evento do usuario e retorna o evento preenchido
    TipoEvento evento;
    eventoInit(&evento);

    // Recebe os dados do evento
    evento.id = 0; // ID sera atribuido automaticamente
    recebeString(evento.nome, 100, "Digite o Nome do Evento", "Max. 100", config->validar_dados);
    evento.codigoCliente = recebeID(config->validar_dados); // ID do cliente relacionado
    recebeString(evento.localEvento, 150, "Digite o Local do Evento", "Max. 150", config->validar_dados);
    recebeString(evento.cidade, 50, "Digite a Cidade", "Max. 50", config->validar_dados);
    recebeString(evento.uf, 4, "Digite a UF", "Max. 4", config->validar_dados);
    evento.margemLucro = recebeFloat(0.0, 100.0, "Digite a Margem de Lucro (%)", "0.0 - 100.0", config->validar_dados);
    recebeString(evento.obs, 500, "Digite observacoes", "Max. 500", config->validar_dados);
    evento.status = STATUS_ORCAMENTO;

    return evento;
}

// ========== MENU PRINCIPAL DE EVENTOS ==========
void menuEvento(TipoEvento* evento,ListaEvento **listaEvento, ListaCliente *listaCliente,
                ListaRecurso *listaRecurso, ListaEquipe *listaEquipe, 
                ListaFornecedor *listaFornecedor, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Evento
        printMenuEventos();

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 5, "Digite uma opcao", "#", config->validar_dados);

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
                // Atualizar Evento
                menuEventoAtualizar(listaEvento, listaCliente, config);
                esperaEnter();
                break;
            case 4:
                // Buscar Evento
                menuEventoBuscar(listaEvento, config);
                esperaEnter();
                break;
            case 5:
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

// ========== CRUD BÁSICO ==========
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

void menuEventoBuscar(ListaEvento *listaEvento, TipoConfig *config) {
    TipoEvento *evento; // Para guardar resultado de busca
    evento = eventoBuscar(listaEvento, recebeID(config->validar_dados));
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
    
    int codigoRecurso = recebeID(config->validar_dados);
    int qtd = recebeInt(1, 1000, "Digite a quantidade", "1 - 1000", config->validar_dados);
    int diasEvento = recebeInt(1, 365, "Digite o numero de dias do evento", "1 - 365", config->validar_dados);
    
    if (eventoUnirRecurso(evento, listaRecurso, codigoRecurso, qtd, diasEvento)) {
        printAdicionarSucesso();
    } else {
        printAdicionarFalha();
    }
}

void menuEventoRemoverRecurso(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    // Implemente a logica de remocao de recurso conforme necessario
    printMensagem("Funcionalidade em desenvolvimento", "#");
}

void menuEventoListarRecursos(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Recursos do Evento", "=");
    // Implemente a listagem de recursos do evento conforme necessario
    printf("Custo Total de Recursos: R$ %.2f\n", evento->custoTotalRecursos);
}

// ========== EQUIPE DO EVENTO ==========
void menuEventoAdicionarEquipe(TipoEvento *evento, ListaEquipe *listaEquipe, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    int codigoFunc = recebeID(config->validar_dados);
    double valorDiaria = recebeFloat(0.0, 100000.0, "Digite o valor da diaria", "0.0 - 100000.0", config->validar_dados);
    int numDias = recebeInt(1, 365, "Digite o numero de dias", "1 - 365", config->validar_dados);
    
    if (eventoUnirEquipe(evento, listaEquipe, codigoFunc, valorDiaria, numDias)) {
        printAdicionarSucesso();
    } else {
        printAdicionarFalha();
    }
}

void menuEventoRemoverEquipe(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    // Implemente a logica de remocao de equipe conforme necessario
    printMensagem("Funcionalidade em desenvolvimento", "#");
}

void menuEventoListarEquipes(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Equipes do Evento", "=");
    // Implemente a listagem de equipes do evento conforme necessario
    printf("Custo Total de Equipe: R$ %.2f\n", evento->custoTotalEquipe);
}

// ========== FORNECEDORES DO EVENTO ==========
void menuEventoAdicionarFornecedor(TipoEvento *evento, ListaFornecedor *listaFornecedor, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    int codigoFornecedor = recebeID(config->validar_dados);
    char descricaoServico[500];
    recebeString(descricaoServico, 500, "Digite a descricao do servico", "Max. 500", config->validar_dados);
    double valorServico = recebeFloat(0.0, 1000000.0, "Digite o valor do servico", "0.0 - 1000000.0", config->validar_dados);
    
    if (eventoUnirFornecedor(evento, listaFornecedor, codigoFornecedor, descricaoServico, valorServico)) {
        printAdicionarSucesso();
    } else {
        printAdicionarFalha();
    }
}

void menuEventoRemoverFornecedor(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    // Implemente a logica de remocao de fornecedor conforme necessario
    printMensagem("Funcionalidade em desenvolvimento", "#");
}

void menuEventoListarFornecedores(TipoEvento *evento, TipoConfig *config) {
    if (evento == NULL) {
        printNaoEncontrado();
        return;
    }
    
    limparTela();
    printMensagem("Fornecedores do Evento", "=");
    // Implemente a listagem de fornecedores do evento conforme necessario
    printf("Custo Total de Fornecedores: R$ %.2f\n", evento->custoTotalForn);
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