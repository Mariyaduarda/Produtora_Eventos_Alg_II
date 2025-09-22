#include "menuFornecedor.h"

TipoFornecedor menuFornecedorRecebe() {
    // Recebe um novo Fornecedor/Parceiro do usuario e retorna o fornecedor/parceiro preenchido
    TipoFornecedor fornecedor;
    inicializarFornecedor(&fornecedor);

    // Recebe os dados do fornecedor/parceiro
    fornecedor.id = 0; // ID sera atribuido automaticamente
    recebeNomeFantasia(fornecedor.nomeFantasia, 100);
    recebeRazaoSocial(fornecedor.razaoSocial, 100);
    recebeCPF(fornecedor.cpf_cnpj);
    recebeEndereco(fornecedor.endereco, 100);
    recebeTelefone(fornecedor.telefone);
    recebeTipoServico(fornecedor.tipoServico, 100);

    return fornecedor;
}

void listarFornecedor(ListaFornecedor *lista) {
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
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu de Fornecedor/Parceiro
        printMenuFornecedor();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Fornecedor/Parceiro
                if (adicionarFornecedor(listaFornecedor, menuFornecedorRecebe())) printAdicionarSucesso();
                else printAdicionarFalha();
                esperaEnter();
                break;
            case 2:
                // Remover Fornecedor/Parceiro
                if (removerFornecedor(listaFornecedor, recebeID())) printRemoverSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 3:
                // Atualizar Fornecedor/Parceiro
                if (atualizarFornecedor(*listaFornecedor, menuFornecedorRecebe(), recebeID())) printAtualizarSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 4:
                // Buscar Fornecedor/Parceiro
                TipoFornecedor *fornecedor = buscarFornecedor(*listaFornecedor, recebeID());
                if (fornecedor != NULL) printItemFornecedor(*fornecedor);
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 5:
                // Listar Fornecedores/Parceiros
                listarFornecedor(*listaFornecedor);
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
    }
    
}