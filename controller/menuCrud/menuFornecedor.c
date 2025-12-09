#include "menuFornecedor.h"

TipoFornecedor menuFornecedorRecebe(TipoConfig *config) {
    // Recebe um novo Fornecedor/Parceiro do usuario e retorna o fornecedor/parceiro preenchido
    TipoFornecedor fornecedor;
    fornecedorInit(&fornecedor);

    // Recebe os dados do fornecedor/parceiro
    fornecedor.id = 0; // ID sera atribuido automaticamente
    recebeString(fornecedor.nomeFantasia, 100, "Digite o Nome Fantasia","Max. 100", config->validar_dados);
    recebeString(fornecedor.razaoSocial, 100, "Digite a Razao Social","Max. 100", config->validar_dados);
    recebeCPFCNPJ(fornecedor.cpf_cnpj, &fornecedor.usa_CNPJ, config->validar_dados);
    recebeString(fornecedor.endereco, 100, "Digite o Endereco","Max. 100", config->validar_dados);
    recebeTelefone(fornecedor.telefone, config->validar_dados);
    recebeString(fornecedor.tipoServico, 100, "Digite o Tipo de Servico","Max. 100", config->validar_dados);
    fornecedor.tipoValor = recebeInt(0,2,"Digite o tipo de pagamento","0:Fixo | 1:Por hora | 2:Por Dia",config->validar_dados);
    fornecedor.valor = recebeFloat(0, 1000000, "Digite o valor do pagamento", "Entre 0 e 1m", config->validar_dados);

    return fornecedor;
}

void menuFornecedorAdicionar(ListaFornecedor **listaFornecedor, TipoConfig *config){
    // Guarda o novo item
    TipoFornecedor novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuFornecedorRecebe(config); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemFornecedor(novo);
        
        if( recebeConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( fornecedorAdicionar(listaFornecedor, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuFornecedorRemover(ListaFornecedor **listaFornecedor, TipoConfig *config){
    int ID = recebeID(config->validar_dados); // recebe o ID do item que vai ser removido
    
    // Busca o Item q vai ser removido
    TipoFornecedor *Fornecedor; // Para guardar resultado de busca
    Fornecedor = fornecedorBuscar(*listaFornecedor, ID);
    if (Fornecedor == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Mostra o Item que vai ser removido
    
    printItemFornecedor(*Fornecedor);
    
    
    // Pede confirmacao, se tiver ok, remove o Fornecedor
    if (recebeConfirma()){
        fornecedorRemover(listaFornecedor, ID);
        printRemoverSucesso();
    }
}

void menuFornecedorAtualizar(ListaFornecedor **listaFornecedor, TipoConfig *config){
    // Declara um novo item pra receber os dados atualizados
    TipoFornecedor novoFornecedor;
    TipoFornecedor* velhoFornecedor;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID(config->validar_dados);
    velhoFornecedor = fornecedorBuscar(*listaFornecedor, ID);

    // Se esse ID n existe, mostra erro
    if (velhoFornecedor == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoFornecedor = menuFornecedorRecebe(config);

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
    if (recebeConfirma()){
        fornecedorAtualizar(*listaFornecedor, novoFornecedor, ID);
        printAtualizarSucesso();
    }
}

void menuFornecedorBuscar(ListaFornecedor **listaFornecedor, TipoConfig *config){
    TipoFornecedor *Fornecedor; // Para guardar resultado de busca
    Fornecedor = fornecedorBuscar(*listaFornecedor, recebeID(config->validar_dados));
    if (Fornecedor != NULL){
        
        printItemFornecedor(*Fornecedor);
        
    }
    else printNaoEncontrado();
}

void menuFornecedorListar(ListaFornecedor *lista, TipoConfig *config) {
    limparTela();

    // Lista todos os fornecedores/parceiros cadastrados
    if (lista == NULL) {
        printMensagem("Nenhum item cadastrado","#");
        return;
    }

    
    ListaFornecedor *atual = lista; // comeca auxiliar no comeco da lista
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->fornecedor.ativo) printItemFornecedor(atual->fornecedor);
        atual = atual->prox;
    }
    
    // barra de baixo
    printf("\n======================================================================");
}

void menuFornecedor(ListaFornecedor **listaFornecedor, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Fornecedor
        printMenuFornecedor();

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 5, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Adicionar Fornecedor
                menuFornecedorAdicionar(listaFornecedor, config);
                esperaEnter();
                break;
            case 2:
                // Remover Fornecedor
                menuFornecedorRemover(listaFornecedor, config);
                esperaEnter();
                break;
            case 3:
                // Atualizar Fornecedor
                menuFornecedorAtualizar(listaFornecedor, config);
                esperaEnter();
                break;
            case 4:
                // Buscar Fornecedor
                menuFornecedorBuscar(listaFornecedor, config);
                esperaEnter();
                break;
            case 5:
                // Listar Fornecedors
                menuFornecedorListar(*listaFornecedor, config);
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