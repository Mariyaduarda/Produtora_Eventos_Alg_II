#include "menuOperador.h"

TipoOperador menuOperadorRecebe() {
    // Recebe um novo Operador do Sistema do usuario e retorna o operador preenchido
    TipoOperador operador;
    inicializarOperador(&operador);

    // Recebe os dados do operador do sistema
    operador.id = 0; // ID sera atribuido automaticamente
    recebeNome(operador.nome, 100);
    recebeNomeUsuario(operador.usuario, 50);
    recebeSenha(operador.senha, 50);

    return operador;
}

void listarOperador(ListaOperador *lista) {
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
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu de Operador do Sistema
        printMenuOperador();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Operador do Sistema
                adicionarOperador(listaOperador, menuOperadorRecebe());
                break;
            case 2:
                // Remover Operador do Sistema
                removerOperador(listaOperador, recebeID());
                break;
            case 3:
                // Atualizar Operador do Sistema
                atualizarOperador(*listaOperador, menuOperadorRecebe(), recebeID());
                break;
            case 4:
                // Buscar Operador do Sistema
                buscarOperador(*listaOperador, recebeID());
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
                printf("\n => Opcao invalida! Tente novamente.\n");
                esperaEnter();
        }
    }
    
}