#include "menuCliente.h"

TipoCliente menuClienteRecebe() {
    // Recebe um novo Cliente do usuario e retorna o cliente preenchido
    TipoCliente cliente;
    clienteInit(&cliente);

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
    // Guarda o novo item
    TipoCliente novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuClienteRecebe(); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemCliente(novo);
        
        if( printConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( clienteAdicionar(listaCliente, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuClienteRemover(ListaCliente **listaCliente){
    int ID = recebeID(); // recebe o ID do item que vai ser removido
    
    // Busca o Item q vai ser removido
    TipoCliente *cliente; // Para guardar resultado de busca
    cliente = clienteBuscar(*listaCliente, ID);
    if (cliente == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Mostra o Item que vai ser removido
    
    printItemCliente(*cliente);
    
    
    // Pede confirmacao, se tiver ok, remove o cliente
    if (printConfirma()){
        clienteRemover(listaCliente, ID);
        printRemoverSucesso();
    }
}

void menuClienteAtualizar(ListaCliente **listaCliente){
    // Declara um novo item pra receber os dados atualizados
    TipoCliente novoCliente;
    TipoCliente* velhoCliente;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID();
    velhoCliente = clienteBuscar(*listaCliente, ID);

    // Se esse ID n existe, mostra erro
    if (velhoCliente == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoCliente = menuClienteRecebe();

    // ===============================
    // Mostra as mudancas

    // Printa os antigos dados
    printMensagem("Dados Antigos","=");
    
    printItemCliente(*velhoCliente);
    
    
    // Printa os novos dados
    printMensagem("Dados Novos","=");
    
    printItemCliente(novoCliente);
    
    
    // ===============================
    // Confirma se o usuario realmente quer atualizar
    if (printConfirma()){
        clienteAtualizar(*listaCliente, novoCliente, ID);
        printAtualizarSucesso();
    }
}

void menuClienteBuscar(ListaCliente **listaCliente){
    TipoCliente *cliente; // Para guardar resultado de busca
    cliente = clienteBuscar(*listaCliente, recebeID());
    if (cliente != NULL){
        
        printItemCliente(*cliente);
        
    }
    else printNaoEncontrado();
}

void menuClienteListar(ListaCliente *lista) {
    limparTela();

    // Lista todos os clientes cadastrados
    if (lista == NULL) {
        printf("\n => Nenhum cliente cadastrado.\n");
        return;
    }

    
    ListaCliente *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->cliente.ativo) printItemCliente(atual->cliente);
        atual = atual->prox;
    }
    

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
                menuClienteAdicionar(listaCliente);
                esperaEnter();
                break;
            case 2:
                // Remover Cliente
                menuClienteRemover(listaCliente);
                esperaEnter();
                break;
            case 3:
                // Atualizar Cliente
                menuClienteAtualizar(listaCliente);
                esperaEnter();
                break;
            case 4:
                // Buscar Cliente
                menuClienteBuscar(listaCliente);
                esperaEnter();
                break;
            case 5:
                // Listar Clientes
                menuClienteListar(*listaCliente);
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