#include "menuEquipe.h"

TipoEquipe menuEquipeRecebe(TipoConfig *config) {
    // Recebe uma nova Equipe Interna do usuario e retorna a equipe preenchida
    TipoEquipe equipe;
    equipeInit(&equipe);

    // Recebe os dados da equipe interna
    equipe.id = 0; // ID sera atribuido automaticamente
    recebeString(equipe.nome, 100, "Digite o Nome","Max. 100", config->validar_dados);
    recebeCPF(equipe.cpf, config->validar_dados);
    recebeString(equipe.funcao, 50, "Digite a Funcao","Max. 50", config->validar_dados);
    equipe.valorDiariaHora = recebeFloat(0, 1000000, "Digite o Valor da Diaria", "Entre 0 e 1m", config->validar_dados);

    return equipe;
}

void menuEquipeAdicionar(ListaEquipe **listaEquipe, TipoConfig *config){
    // Guarda o novo item
    TipoEquipe novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuEquipeRecebe(config); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemEquipe(novo);
        
        if( recebeConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( equipeAdicionar(listaEquipe, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuEquipeRemover(ListaEquipe **listaEquipe, TipoConfig *config){
    int ID = recebeID(config->validar_dados); // recebe o ID do item que vai ser removido
    
    // Busca o Item q vai ser removido
    TipoEquipe *Equipe; // Para guardar resultado de busca
    Equipe = equipeBuscar(*listaEquipe, ID);
    if (Equipe == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Mostra o Item que vai ser removido
    
    printItemEquipe(*Equipe);
    
    // Pede confirmacao, se tiver ok, remove o Equipe
    if (recebeConfirma()){
        equipeRemover(listaEquipe, ID);
        printRemoverSucesso();
    }
}

void menuEquipeAtualizar(ListaEquipe **listaEquipe, TipoConfig *config){
    // Declara um novo item pra receber os dados atualizados
    TipoEquipe novoEquipe;
    TipoEquipe* velhoEquipe;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID(config->validar_dados);
    velhoEquipe = equipeBuscar(*listaEquipe, ID);

    // Se esse ID n existe, mostra erro
    if (velhoEquipe == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoEquipe = menuEquipeRecebe(config);

    // ===============================
    // Mostra as mudancas

    // Printa os antigos dados
    printMensagem("Dados Antigos","=");
    
    printItemEquipe(*velhoEquipe);
    
    
    // Printa os novos dados
    printMensagem("Dados Novos","=");
    
    printItemEquipe(novoEquipe);
    
    
    // ===============================
    // Confirma se o usuario realmente quer atualizar
    if (recebeConfirma()){
        equipeAtualizar(*listaEquipe, novoEquipe, ID);
        printAtualizarSucesso();
    }
}

void menuEquipeBuscar(ListaEquipe **listaEquipe, TipoConfig *config){
    TipoEquipe *Equipe; // Para guardar resultado de busca
    Equipe = equipeBuscar(*listaEquipe, recebeID(config->validar_dados));
    if (Equipe != NULL){
        
        printItemEquipe(*Equipe);
        
    }
    else printNaoEncontrado();
}

void menuEquipeListar(ListaEquipe *lista, TipoConfig *config) {
    limparTela();

    // Lista todas as equipes internas cadastradas
    if (lista == NULL) {
        printMensagem("Nenhum item cadastrado","#");
        return;
    }

    
    ListaEquipe *atual = lista; // comeca auxiliar no comeco da lista
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->equipe.ativo) printItemEquipe(atual->equipe);
        atual = atual->prox;
    }
    
    printf("\n");
}

void menuEquipe(ListaEquipe **listaEquipe, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Equipe
        printMenuEquipe();

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 5, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Adicionar Equipe
                menuEquipeAdicionar(listaEquipe, config);
                esperaEnter();
                break;
            case 2:
                // Remover Equipe
                menuEquipeRemover(listaEquipe, config);
                esperaEnter();
                break;
            case 3:
                // Atualizar Equipe
                menuEquipeAtualizar(listaEquipe, config);
                esperaEnter();
                break;
            case 4:
                // Buscar Equipe
                menuEquipeBuscar(listaEquipe, config);
                esperaEnter();
                break;
            case 5:
                // Listar Equipes
                menuEquipeListar(*listaEquipe, config);
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