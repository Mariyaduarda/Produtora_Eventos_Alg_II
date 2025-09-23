#include "menuOperador.h"

TipoOperador menuOperadorRecebe() {
    // Recebe um novo Operador do Sistema do usuario e retorna o operador preenchido
    TipoOperador operador;
    inicializarOperador(&operador);

    // Recebe os dados do operador do sistema
    operador.id = 0; // ID sera atribuido automaticamente
    recebeString(operador.nome, 100, "Digite o Nome","Max. 100");
    recebeString(operador.usuario, 100, "Digite o Nome de Usuario","Max. 100");
    recebeString(operador.senha, 100, "Digite a Senha","Max. 100");

    return operador;
}

void listarOperador(ListaOperador *lista) {
    limparTela();

    // Lista todos os operadores do sistema cadastrados
    if (lista == NULL) {
        printf("\n => Nenhum operador do sistema cadastrado.\n");
        return;
    }

    printTabelaLinha();
    ListaOperador *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->operador.ativo) printItemOperador(atual->operador);
        atual = atual->prox;

        // se n for o ultimo, printa a linha horizontal p dividir
        if (atual != NULL) printTabelaLinhaInterior();
    }
    printTabelaLinha();
    printf("\n");
}

void menuOperador(ListaOperador **listaOperador) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Operador do Sistema
        printMenuOperador();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Operador do Sistema
                if ( adicionarOperador(listaOperador, menuOperadorRecebe()) ) printAdicionarSucesso();
                else printAdicionarFalha();
                esperaEnter();
                break;
            case 2:
                // Remover Operador do Sistema
                if ( removerOperador(listaOperador, recebeID()) ) printRemoverSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 3:
                // Atualizar Operador do Sistema
                if (atualizarOperador(*listaOperador, menuOperadorRecebe(), recebeID())) printAtualizarSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 4:
                // Buscar Operador do Sistema
                TipoOperador *operador = buscarOperador(*listaOperador, recebeID());
                if (operador != NULL) {
                    printTabelaLinha();
                    printItemOperador(*operador);
                    printTabelaLinha();
                }
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 5:
                // Listar Operadores do Sistema
                listarOperador(*listaOperador);
                esperaEnter();
                break;
            case 0:
                // Voltar ao menu principal
                printf("\n => Voltando ao menu principal...\n");
                break;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }while (escolha != 0);
    
}