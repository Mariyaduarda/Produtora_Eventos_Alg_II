#include "menuCliente.h"

TipoCliente menuClienteRecebe() {
    // Recebe um novo Cliente do usuario e retorna o cliente preenchido
    TipoCliente cliente;
    inicializarCliente(&cliente);

    // Recebe os dados do cliente
    cliente.id = 0; // ID sera atribuido automaticamente
    recebeString(cliente.nome, 100, "Digite o Nome","Max. 100");
    recebeString(cliente.endereco, 100, "Digite o Endereco","Max. 100");
    recebeCPF(cliente.cpf_cnpj);
    recebeTelefone(cliente.telefone);
    recebeEmail(cliente.email);
    recebeString(cliente.nomeDoContato, 100, "Digite o Nome do Contato","Max. 100");

    return cliente;
}

void menuClienteAdicionar(ListaCliente **listaCliente){
    TipoCliente novo; // Guarda o novo item
    
    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuClienteRecebe(); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printTabelaLinha();
        printItemCliente(novo);
        printTabelaLinha();
        
        if( printConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( adicionarCliente(listaCliente, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
    
    esperaEnter();
}

void menuClienteRemover(ListaCliente **listaCliente){
    int ID = recebeID(); // recebe o ID do item que vai ser removido
    
    // Busca o Item q vai ser removido
    TipoCliente *cliente; // Para guardar resultado de busca
    cliente = buscarCliente(*listaCliente, ID);
    if (cliente == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Mostra o Item que vai ser removido
    printTabelaLinha();
    printItemCliente(*cliente);
    printTabelaLinha();
    
    // Pede confirmacao, se tiver ok, remove o cliente
    if (printConfirma()){
        removerCliente(listaCliente, ID);
        printRemoverSucesso();
    }
    
    esperaEnter();
}

void menuClienteAtualizar(ListaCliente **listaCliente){
    if ( atualizarCliente(*listaCliente, menuClienteRecebe(), recebeInt(1, 1000000, "Digite o ID", "Min. 1")) ) printAtualizarSucesso();
    else printNaoEncontrado();
    esperaEnter();
    
}

void menuClienteBuscar(ListaCliente **listaCliente){
    TipoCliente *cliente; // Para guardar resultado de busca
    cliente = buscarCliente(*listaCliente, recebeInt(1, 1000000, "Digite o ID", "Min. 1"));
    if (cliente != NULL){
        printTabelaLinha();
        printItemCliente(*cliente);
        printTabelaLinha();
    }
    else printNaoEncontrado();
    esperaEnter();
}

void menuClienteListar(ListaCliente *lista) {
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
    esperaEnter();
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
                menuClienteAdicionar(listaCliente);
                break;
            case 2:
                // Remover Cliente
                menuClienteRemover(listaCliente);
                break;
            case 3:
                // Atualizar Cliente
                menuClienteAtualizar(listaCliente);
                break;
            case 4:
                // Buscar Cliente
                menuClienteBuscar(listaCliente);
                break;
            case 5:
                // Listar Clientes
                menuClienteListar(*listaCliente);
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