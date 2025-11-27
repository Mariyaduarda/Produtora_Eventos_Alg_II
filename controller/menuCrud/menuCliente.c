#include "menuCliente.h"

TipoCliente menuClienteRecebe(TipoConfig *config) {
    // Recebe um novo Cliente do usuario e retorna o cliente preenchido
    TipoCliente cliente;
    clienteInit(&cliente);

    // Recebe os dados do cliente
    cliente.id = 0; // ID sera atribuido automaticamente
    recebeString(cliente.nome, 100, "Digite o Nome","Max. 100", config->validar_dados);
    recebeString(cliente.endereco, 100, "Digite o Endereco","Max. 100", config->validar_dados);
    recebeCPFCNPJ(cliente.cpf_cnpj, &cliente.usa_CNPJ, config->validar_dados);
    recebeTelefone(cliente.telefone, config->validar_dados);
    recebeEmail(cliente.email, config->validar_dados);
    recebeString(cliente.nomeDoContato, 100, "Digite o Nome do Contato","Max. 100", config->validar_dados);

    return cliente;
}

void menuClienteAdicionar(ListaCliente **listaCliente, TipoConfig *config){
    // Guarda o novo item
    TipoCliente novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuClienteRecebe(config); // Recebe os valroes do usuario

        // Mostra os dados que foram inseridos
        printItemCliente(novo);

        if( recebeConfirma() ) break;  // Pergunta o usuario se ta td certo
    }

    // Realmente adiciona na lista
    if ( clienteAdicionar(listaCliente, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuClienteRemover(ListaCliente **listaCliente, TipoConfig *config){
    int ID = recebeID(config->validar_dados); // recebe o ID do item que vai ser removido

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
    if (recebeConfirma()){
        clienteRemover(listaCliente, ID);
        printRemoverSucesso();
    }
}

void menuClienteAtualizar(ListaCliente **listaCliente, TipoConfig *config){
    // Declara um novo item pra receber os dados atualizados
    TipoCliente novoCliente;
    TipoCliente* velhoCliente;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID(config->validar_dados);
    velhoCliente = clienteBuscar(*listaCliente, ID);

    // Se esse ID n existe, mostra erro
    if (velhoCliente == NULL){
        printNaoEncontrado();
        return;
    }

    // Caso contrario, recebe os novos dados
    novoCliente = menuClienteRecebe(config);

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
    if (recebeConfirma()){
        clienteAtualizar(*listaCliente, novoCliente, ID);
        printAtualizarSucesso();
    }
}

void menuClienteBuscar(ListaCliente **listaCliente, TipoConfig *config){
    TipoCliente *cliente; // Para guardar resultado de busca
    cliente = clienteBuscar(*listaCliente, recebeID(config->validar_dados));
    if (cliente != NULL){

        printItemCliente(*cliente);

    }
    else printNaoEncontrado();
}

void menuClienteListar(ListaCliente *lista, TipoConfig *config) {
    limparTela();

    // Lista todos os clientes cadastrados
    if (lista == NULL) {
        printMensagem("Nenhum item cadastrado","#");
        return;
    }


    ListaCliente *atual = lista; // comeca auxiliar no comeco da lista
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->cliente.ativo) printItemCliente(atual->cliente);
        atual = atual->prox;
    }
    
    // barra de baixo
    printf("\n======================================================================");
}

void menuCliente(ListaCliente **listaCliente, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Cliente
        printMenuCliente();

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 5, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Adicionar Cliente
                menuClienteAdicionar(listaCliente, config);
                esperaEnter();
                break;
            case 2:
                // Remover Cliente
                menuClienteRemover(listaCliente, config);
                esperaEnter();
                break;
            case 3:
                // Atualizar Cliente
                menuClienteAtualizar(listaCliente, config);
                esperaEnter();
                break;
            case 4:
                // Buscar Cliente
                menuClienteBuscar(listaCliente, config);
                esperaEnter();
                break;
            case 5:
                // Listar Clientes
                menuClienteListar(*listaCliente, config);
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