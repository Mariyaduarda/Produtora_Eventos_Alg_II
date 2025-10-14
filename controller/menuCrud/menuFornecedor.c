#include "menuFornecedor.h"

TipoFornecedor menuFornecedorRecebe() {
    // Recebe um novo Fornecedor/Parceiro do usuario e retorna o fornecedor/parceiro preenchido
    TipoFornecedor fornecedor;
    inicializarFornecedor(&fornecedor);

    // Recebe os dados do fornecedor/parceiro
    fornecedor.id = 0; // ID sera atribuido automaticamente
    recebeString(fornecedor.nomeFantasia, 100, "Digite o Nome Fantasia","Max. 100");
    recebeString(fornecedor.razaoSocial, 100, "Digite a Razao Social","Max. 100");
    recebeCPF(fornecedor.cpf_cnpj);
    recebeString(fornecedor.endereco, 100, "Digite o Endereco","Max. 100");
    recebeTelefone(fornecedor.telefone);
    recebeString(fornecedor.tipoServico, 100, "Digite o Telefone","Max. 100");

    return fornecedor;
}

void menuFornecedorAdicionar(ListaFornecedor **listaFornecedor){
    // Guarda o novo item
    TipoFornecedor novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuFornecedorRecebe(); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemFornecedor(novo);
        
        if( printConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( adicionarFornecedor(listaFornecedor, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuFornecedorRemover(ListaFornecedor **listaFornecedor){
    int ID = recebeID(); // recebe o ID do item que vai ser removido
    
    // Busca o Item q vai ser removido
    TipoFornecedor *Fornecedor; // Para guardar resultado de busca
    Fornecedor = buscarFornecedor(*listaFornecedor, ID);
    if (Fornecedor == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Mostra o Item que vai ser removido
    
    printItemFornecedor(*Fornecedor);
    
    
    // Pede confirmacao, se tiver ok, remove o Fornecedor
    if (printConfirma()){
        removerFornecedor(listaFornecedor, ID);
        printRemoverSucesso();
    }
}

void menuFornecedorAtualizar(ListaFornecedor **listaFornecedor){
    // Declara um novo item pra receber os dados atualizados
    TipoFornecedor novoFornecedor;
    TipoFornecedor* velhoFornecedor;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID();
    velhoFornecedor = buscarFornecedor(*listaFornecedor, ID);

    // Se esse ID n existe, mostra erro
    if (velhoFornecedor == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoFornecedor = menuFornecedorRecebe();

    // ===============================
    // Mostra as mudancas

    // Printa os antigos dados
    printMensagem("Dados Antigos","=");
    
    printItemFornecedor(*velhoFornecedor);
    
    
    // Printa os novos dados
    printMensagem("Dados Novos","=");
    
    printItemFornecedor(novoFornecedor);
    
    
    // ===============================
    // Confirma se o usuario realmente quer atualizar
    if (printConfirma()){
        atualizarFornecedor(*listaFornecedor, novoFornecedor, ID);
        printAtualizarSucesso();
    }
}

void menuFornecedorBuscar(ListaFornecedor **listaFornecedor){
    TipoFornecedor *Fornecedor; // Para guardar resultado de busca
    Fornecedor = buscarFornecedor(*listaFornecedor, recebeID());
    if (Fornecedor != NULL){
        
        printItemFornecedor(*Fornecedor);
        
    }
    else printNaoEncontrado();
}

void menuFornecedorListar(ListaFornecedor *lista) {
    limparTela();

    // Lista todos os fornecedores/parceiros cadastrados
    if (lista == NULL) {
        printf("\n => Nenhum fornecedor/parceiro cadastrado.\n");
        return;
    }

    
    ListaFornecedor *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->fornecedor.ativo) printItemFornecedor(atual->fornecedor);
        atual = atual->prox;
    }
    
    printf("\n");
}

void menuFornecedor(ListaFornecedor **listaFornecedor) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Fornecedor
        printMenuFornecedor();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Fornecedor
                menuFornecedorAdicionar(listaFornecedor);
                esperaEnter();
                break;
            case 2:
                // Remover Fornecedor
                menuFornecedorRemover(listaFornecedor);
                esperaEnter();
                break;
            case 3:
                // Atualizar Fornecedor
                menuFornecedorAtualizar(listaFornecedor);
                esperaEnter();
                break;
            case 4:
                // Buscar Fornecedor
                menuFornecedorBuscar(listaFornecedor);
                esperaEnter();
                break;
            case 5:
                // Listar Fornecedors
                menuFornecedorListar(*listaFornecedor);
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