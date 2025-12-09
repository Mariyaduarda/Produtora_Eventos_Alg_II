#include "menuOperador.h"

TipoOperador menuOperadorRecebe(TipoConfig *config) {
    // Recebe um novo Operador do Sistema do usuario e retorna o operador preenchido
    TipoOperador operador;
    operadorInit(&operador);

    // Recebe os dados do operador do sistema
    operador.id = 0; // ID sera atribuido automaticamente
    recebeString(operador.nome, 100, "Digite o Nome","Max. 100", config->validar_dados);
    recebeString(operador.usuario, 100, "Digite o Nome de Usuario","Max. 100", config->validar_dados);
    recebeString(operador.senha, 100, "Digite a Senha","Max. 100", config->validar_dados);

    return operador;
}

void menuOperadorAdicionar(ListaOperador **listaOperador, TipoConfig *config){
    // Guarda o novo item
    TipoOperador novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuOperadorRecebe(config); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemOperador(novo);
        
        if( recebeConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( operadorAdicionar(listaOperador, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuOperadorRemover(ListaOperador **listaOperador, TipoConfig *config){
    int ID = recebeID(config->validar_dados); // recebe o ID do item que vai ser removido
    
    // Busca o Item q vai ser removido
    TipoOperador *Operador; // Para guardar resultado de busca
    Operador = operadorBuscar(*listaOperador, ID);
    if (Operador == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Mostra o Item que vai ser removido
    
    printItemOperador(*Operador);
    
    
    // Pede confirmacao, se tiver ok, remove o Operador
    if (recebeConfirma()){
        operadorRemover(listaOperador, ID);
        printRemoverSucesso();
    }
}

void menuOperadorAtualizar(ListaOperador **listaOperador, TipoConfig *config){
    // Declara um novo item pra receber os dados atualizados
    TipoOperador novoOperador;
    TipoOperador* velhoOperador;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID(config->validar_dados);
    velhoOperador = operadorBuscar(*listaOperador, ID);

    // Se esse ID n existe, mostra erro
    if (velhoOperador == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoOperador = menuOperadorRecebe(config);

    // ===============================
    // Mostra as mudancas

    // Printa os antigos dados
    printMensagem("Dados Antigos","=");
    
    printItemOperador(*velhoOperador);
    
    
    // Printa os novos dados
    printMensagem("Dados Novos","=");
    
    printItemOperador(novoOperador);
    
    
    // ===============================
    // Confirma se o usuario realmente quer atualizar
    if (recebeConfirma()){
        operadorAtualizar(*listaOperador, novoOperador, ID);
        printAtualizarSucesso();
    }
}

void menuOperadorBuscar(ListaOperador **listaOperador, TipoConfig *config){
    TipoOperador *Operador; // Para guardar resultado de busca
    Operador = operadorBuscar(*listaOperador, recebeID(config->validar_dados));
    if (Operador != NULL){
        
        printItemOperador(*Operador);
        
    }
    else printNaoEncontrado();
}

void menuOperadorListar(ListaOperador *lista, TipoConfig *config) {
    limparTela();

    // Lista todos os operadores do sistema cadastrados
    if (lista == NULL) {
        printMensagem("Nenhum item cadastrado","#");
        return;
    }

    
    ListaOperador *atual = lista;
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->operador.ativo) printItemOperador(atual->operador);
        atual = atual->prox;
    }
    
    // barra de baixo
    printf("\n======================================================================");
}

void menuOperador(ListaOperador **listaOperador, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Operador
        printMenuOperador();

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 5, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Adicionar Operador
                menuOperadorAdicionar(listaOperador, config);
                esperaEnter();
                break;
            case 2:
                // Remover Operador
                menuOperadorRemover(listaOperador, config);
                esperaEnter();
                break;
            case 3:
                // Atualizar Operador
                menuOperadorAtualizar(listaOperador, config);
                esperaEnter();
                break;
            case 4:
                // Buscar Operador
                menuOperadorBuscar(listaOperador, config);
                esperaEnter();
                break;
            case 5:
                // Listar Operadors
                menuOperadorListar(*listaOperador, config);
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