#include "menuOperador.h"

TipoOperador menuOperadorRecebe() {
    // Recebe um novo Operador do Sistema do usuario e retorna o operador preenchido
    TipoOperador operador;
    operadorInit(&operador);

    // Recebe os dados do operador do sistema
    operador.id = 0; // ID sera atribuido automaticamente
    recebeString(operador.nome, 100, "Digite o Nome","Max. 100");
    recebeString(operador.usuario, 100, "Digite o Nome de Usuario","Max. 100");
    recebeString(operador.senha, 100, "Digite a Senha","Max. 100");

    return operador;
}

void menuOperadorAdicionar(ListaOperador **listaOperador){
    // Guarda o novo item
    TipoOperador novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuOperadorRecebe(); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemOperador(novo);
        
        if( printConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( operadorAdicionar(listaOperador, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuOperadorRemover(ListaOperador **listaOperador){
    int ID = recebeID(); // recebe o ID do item que vai ser removido
    
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
    if (printConfirma()){
        operadorRemover(listaOperador, ID);
        printRemoverSucesso();
    }
}

void menuOperadorAtualizar(ListaOperador **listaOperador){
    // Declara um novo item pra receber os dados atualizados
    TipoOperador novoOperador;
    TipoOperador* velhoOperador;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID();
    velhoOperador = operadorBuscar(*listaOperador, ID);

    // Se esse ID n existe, mostra erro
    if (velhoOperador == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoOperador = menuOperadorRecebe();

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
    if (printConfirma()){
        operadorAtualizar(*listaOperador, novoOperador, ID);
        printAtualizarSucesso();
    }
}

void menuOperadorBuscar(ListaOperador **listaOperador){
    TipoOperador *Operador; // Para guardar resultado de busca
    Operador = operadorBuscar(*listaOperador, recebeID());
    if (Operador != NULL){
        
        printItemOperador(*Operador);
        
    }
    else printNaoEncontrado();
}

void menuOperadorListar(ListaOperador *lista) {
    limparTela();

    // Lista todos os operadores do sistema cadastrados
    if (lista == NULL) {
        printf("\n => Nenhum operador do sistema cadastrado.\n");
        return;
    }

    
    ListaOperador *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->operador.ativo) printItemOperador(atual->operador);
        atual = atual->prox;
    }
    
    printf("\n");
}

void menuOperador(ListaOperador **listaOperador) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Operador
        printMenuOperador();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Operador
                menuOperadorAdicionar(listaOperador);
                esperaEnter();
                break;
            case 2:
                // Remover Operador
                menuOperadorRemover(listaOperador);
                esperaEnter();
                break;
            case 3:
                // Atualizar Operador
                menuOperadorAtualizar(listaOperador);
                esperaEnter();
                break;
            case 4:
                // Buscar Operador
                menuOperadorBuscar(listaOperador);
                esperaEnter();
                break;
            case 5:
                // Listar Operadors
                menuOperadorListar(*listaOperador);
                esperaEnter();
                break;
            case 0:
                // Voltar ao menu principal
                printf("\n => Voltando ao menu principal");
                break;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }while (escolha != 0);
    
}