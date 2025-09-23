#include "menuCliente.h"

TipoCliente menuClienteRecebe() {
    // Recebe um novo Cliente do usuario e retorna o cliente preenchido
    TipoCliente cliente;
    inicializarCliente(&cliente);

    // Recebe os dados do cliente
    cliente.id = 0; // ID sera atribuido automaticamente
    recebeNome(cliente.nome, 100);
    recebeCPF(cliente.cpf_cnpj);
    recebeTelefone(cliente.telefone);
    recebeEmail(cliente.email, 100);

    return cliente;
}

void listarClientes(ListaCliente *lista) {
    limparTela();

    // Lista todos os clientes cadastrados
    if (lista == NULL) {
        printf("\n => Nenhum cliente cadastrado.\n");
        return;
    }

    printTabelaLinha();
    ListaCliente *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->cliente.ativo) printItemCliente(atual->cliente);
        atual = atual->prox;

        // se n for o ultimo, printa a linha horizontal p dividir
        if (atual != NULL) printTabelaLinhaInterior();
    }
    printTabelaLinha();
    printf("\n");
}

void menuCliente(ListaCliente **listaCliente) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Cliente
        printMenuCliente();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Cliente
                if ( adicionarCliente(listaCliente, menuClienteRecebe()) ) printAdicionarSucesso();
                else printAdicionarFalha();
                esperaEnter();
                break;
            case 2:
                // Remover Cliente
                if ( removerCliente(listaCliente, recebeID()) ) printRemoverSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 3:
                // Atualizar Cliente
                if ( atualizarCliente(*listaCliente, menuClienteRecebe(), recebeID()) ) printAtualizarSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 4:
                // Buscar Cliente
                TipoCliente *cliente = buscarCliente(*listaCliente, recebeID());
                if (cliente != NULL){
                    printTabelaLinha();
                    printItemCliente(*cliente);
                    printTabelaLinha();
                }
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 5:
                // Listar Clientes
                listarClientes(*listaCliente);
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