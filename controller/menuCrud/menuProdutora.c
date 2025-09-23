#include "menuProdutora.h"

TipoProdutora menuProdutoraRecebe() {
    // Recebe uma nova Produtora do usuario e retorna a produtora preenchida
    TipoProdutora produtora;
    inicializarProdutora(&produtora);

    // Recebe os dados da produtora
    produtora.id = 0; // ID sera atribuido automaticamente
    recebeNomeFantasia(produtora.nomeFantasia, 100);
    recebeRazaoSocial(produtora.razaoSocial, 100);
    recebeInscricaoEstadual(produtora.inscricaoEstadual);
    recebeCNPJ(produtora.cnpj);
    recebeEndereco(produtora.endereco, 100);
    recebeTelefone(produtora.telefone);
    recebeEmail(produtora.email, 100);
    recebeNome(produtora.nomeDoResponsavel, 50);
    recebeTelefone(produtora.telefoneDoResponsavel);
    produtora.margemDeLucro = recebeMargemDeLucro();

    return produtora;
}

void listarProdutoras(ListaProdutora *lista) {
    limparTela();

    // Lista todas as produtoras cadastradas
    if (lista == NULL) {
        printf("\n => Nenhuma produtora cadastrada.\n");
        return;
    }

    printTabelaLinha();
    ListaProdutora *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->produtora.ativo) printItemProdutora(atual->produtora);
        atual = atual->prox;

        // se n for o ultimo, printa a linha horizontal p dividir
        if (atual != NULL) printTabelaLinhaInterior();
    }
    printTabelaLinha();
    printf("\n");
}

void menuProdutora(ListaProdutora **listaProdutora) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Produtora
        printMenuProdutora();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Produtora
                if ( adicionarProdutora(listaProdutora, menuProdutoraRecebe()) ) printAdicionarSucesso();
                else printAdicionarFalha();
                esperaEnter();
                break;
            case 2:
                // Remover Produtora
                if ( removerProdutora(listaProdutora, recebeID()) ) printRemoverSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 3:
                // Atualizar Produtora
                if ( atualizarProdutora(*listaProdutora, menuProdutoraRecebe(), recebeID()) ) printAtualizarSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 4:
                // Buscar Produtora
                TipoProdutora *produtora = buscarProdutora(*listaProdutora, recebeID());
                if (produtora != NULL) {
                    printTabelaLinha();
                    printItemProdutora(*produtora);
                    printTabelaLinha();
                }
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 5:
                // Listar Produtoras
                listarProdutoras(*listaProdutora);
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